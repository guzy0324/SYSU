import numpy as np
import time
import torch
import torch.nn as nn
from tqdm import tqdm
from torch.distributions import MultivariateNormal
from torch.optim import Adam
import threading
import math
import gym

from mlp_policy import Policy
from mlp_critic import Value


class PPO:
    def __init__(self, conf=dict()):
        # Initialize hyperparameters
        self._init_hyperparameters(conf)

        # ALG STEP 1
        # Initialize actor and critic networks
        self.actor = Policy(self.obs_dim, self.act_dim).to(self.device)
        self.critic = Value(self.obs_dim).to(self.device)

        if self.model_names is not None:
            self.actor.load_state_dict(torch.load(self.model_names[0]))
            self.critic.load_state_dict(torch.load(self.model_names[1]))

        # Initialize actor optimizer
        self.actor_optim = Adam(self.actor.parameters(), lr=self.lr)
        # Initialize critic optimizer
        self.critic_optim = Adam(self.critic.parameters(), lr=self.lr)

        # Initialize critic criterion
        self.critic_criterion = nn.MSELoss().to(self.device)

        # Create our variable for the matrix.
        # Note that I chose 0.5 for stdev arbitrarily.
        self.cov_var = torch.full(size=(self.act_dim,), fill_value=0.5, device=self.device)

        # Create the covariance matrix
        self.cov_mat = torch.diag(self.cov_var).to(self.device)

        # This logger will help us with printing out summaries of each iteration
        self.time = time.time_ns()

    def learn(self):
        pbar = tqdm(total=self.total_timesteps)
        while self.t_so_far < self.total_timesteps: # ALG STEP 2
            # ALG STEP 3
            self.rollout()

            # Calculate how many timesteps we collected this batch
            delta_t = np.sum(self.batch_lens)
            self.t_so_far += delta_t
            pbar.update(delta_t)

            # Increment the number of iterations
            self.i_so_far += 1

            self.ppo_update()

            # Print a summary of our training so far
            self._log_summary()

            # Save our model if it's time
            if self.i_so_far % self.save_freq == 0:
                torch.save(self.actor.state_dict(), './models_ppo/actor' + str(self.i_so_far))
                torch.save(self.critic.state_dict(), './models_ppo/critic' + str(self.i_so_far))

    def ppo_update(self):
        # Calculate V_{phi, k}
        V, _ = self.evaluate()

        # ALG STEP 5
        # Calculate advantage
        A_k = self.batch_rtgs - V.detach()

        # Normalize advantages
        A_k = (A_k - A_k.mean()) / (A_k.std() + 1e-10)

        # ALG STEP 6 & 7
        self.actor_losses = [] # losses of actor network in current iteration
        for _ in range(self.n_updates_per_iteration):
            # Calculate pi_theta(s_t | s_t)
            V, curr_log_probs = self.evaluate()

            # Calculate ratios
            ratios = torch.exp(curr_log_probs - self.batch_log_probs)

            # Calculate surrogate losses
            surr1 = ratios * A_k
            surr2 = torch.clamp(ratios, 1 - self.clip, 1 + self.clip) * A_k
            # Calculate actor loss
            actor_loss = -((torch.min(surr1, surr2) - self.Lambda * ratios * curr_log_probs).mean())

            # Calculate gradients and perform backward propagation for actor network
            self.actor_optim.zero_grad()
            actor_loss.backward(retain_graph=True)
            self.actor_optim.step()

            # Calculate critic loss
            critic_loss = self.critic_criterion(V, self.batch_rtgs)

            # Calculate gradients and perform backward propagation for critic network
            self.critic_optim.zero_grad()
            critic_loss.backward()
            self.critic_optim.step()

            # Log actor loss
            self.actor_losses.append(actor_loss.detach().to(torch.device('cpu')))

    def evaluate(self):
        # Query critic network for a value V for each obs in batch_obs
        V = self.critic(self.batch_obs).squeeze()

        # Calculate the log probabilities of batch actions using most recent actor network.
        # This segment of code is similar to that in get_action()
        mean = self.actor(self.batch_obs)
        dist = MultivariateNormal(mean, self.cov_mat)
        log_probs = dist.log_prob(self.batch_acts)

        # Return predicted values V and log probs log_probs
        return V, log_probs

    def rollout(self):
        # Batch data
        self.batch_obs = [dict()] # batch observations
        self.batch_acts = [dict()] # batch actions
        self.batch_log_probs = [dict()] # log probs of each action
        self.batch_rews = [dict()] # batch rewards
        self.batch_rtgs = [dict()] # batch rewards-to-go
        self.batch_lens = [dict()] # episodic lengths in batch

        self.actor = self.actor.to(torch.device('cpu'))
        self.cov_mat = torch.diag(self.cov_var).to(torch.device('cpu'))

        thread_batch_size = int(math.ceil(self.timesteps_per_batch / self.max_num_threads))
        workers = []
        # Number of timestpes run so far this batch
        t = 0
        for pid in range(1, self.max_num_threads):
            workers.append(threading.Thread(target=self.env_thread, args=(pid, thread_batch_size)))
            t += thread_batch_size
            workers[-1].start()
        self.env_thread(0, self.timesteps_per_batch - t)
        for worker in workers:
            worker.join()

        List_list = [self.batch_obs, self.batch_acts, self.batch_log_probs, self.batch_rews, self.batch_rtgs, self.batch_lens]
        pid = 0
        while pid < 6:
            workers = []
            first_pid = pid
            for pid in range(first_pid + 1, min(6, first_pid + self.max_num_threads)):
                workers.append(threading.Thread(target=self.extend_thread, args=(List_list[pid],)))
                workers[-1].start()
            pid += 1
            self.extend_thread(List_list[first_pid])
            for worker in workers:
                worker.join()

        self.actor = self.actor.to(self.device)
        self.cov_mat = torch.diag(self.cov_var).to(self.device)

        # Reshape data as tensors in the shape specified before returning
        self.batch_obs = torch.tensor(self.batch_obs, dtype=torch.float, device=self.device)
        self.batch_acts = torch.tensor(self.batch_acts, dtype=torch.float, device=self.device)
        self.batch_log_probs = torch.tensor(self.batch_log_probs, dtype=torch.float, device=self.device)
        self.batch_rtgs = torch.tensor(self.batch_rtgs, dtype=torch.float, device=self.device)

    def env_thread(self, pid, timesteps_per_batch):
        # Batch data
        batch_obs_thread = [] # batch observations
        batch_acts_thread = [] # batch actions
        batch_log_probs_thread = [] # log probs of each action
        batch_rews_thread = [] # batch rewards
        batch_rtgs_thread = [] # batch rewards-to-go
        batch_lens_thread = [] # episodic lengths in batch

        # Number of timestpes run so far this batch
        t = 0
        while t < timesteps_per_batch:
            # Rewards this episode
            ep_rews = []
            obs = self.envs[pid].reset()
            done = False
            for ep_t in range(self.max_timesteps_per_episode):
                # Collect observation
                batch_obs_thread.append(obs)
                action, log_prob = self.get_action(obs)
                obs, rew, done, _ = self.envs[pid].step(action)

                # Collect reward, action, and log prob
                ep_rews.append(rew)
                batch_acts_thread.append(action)
                batch_log_probs_thread.append(log_prob)

                if done:
                    break

            # Increment timesteps ran this batch so far
            t += ep_t + 1

            # Collect episodic length and rewards
            batch_lens_thread.append(ep_t + 1) # plus 1 because timestep starts at 0
            batch_rews_thread.append(ep_rews)

            # ALG STEP #4
            batch_rtgs_thread.extend(self.compute_rtgs(ep_rews))

        self.batch_obs[0][pid] = batch_obs_thread
        self.batch_acts[0][pid] = batch_acts_thread
        self.batch_log_probs[0][pid] = batch_log_probs_thread
        self.batch_rews[0][pid] = batch_rews_thread
        self.batch_rtgs[0][pid] = batch_rtgs_thread
        self.batch_lens[0][pid] = batch_lens_thread

    def get_action(self, obs):
        # Query the actor network for a mean action.
        # Same thing as calling self.actor.forward(obs)
        mean = self.actor(torch.tensor(obs, dtype=torch.float))
        # Create our Multivariate Normal Distribution
        dist = MultivariateNormal(mean, self.cov_mat)
        # Sample an action from the distribution and get its log prob
        action = dist.sample()
        log_prob = dist.log_prob(action)
        # Return the sampled action and the log prob of that action
        # Note that I'm calling detach() since the action and log_prob  
        # are tensors with computation graphs, so I want to get rid
        # of the graph and just convert the action to numpy array.
        # log prob as tensor is fine. Our computation graph will
        # start later down the line.
        return action.detach().numpy(), log_prob.detach()

    def compute_rtgs(self, ep_rews):
        # The rewards-to-go (rtg) per episode to return.
        # The shape will be (num timesteps per episode)
        ep_rtgs = []
        discounted_reward = 0 # The discounted reward so far
        for rew in reversed(ep_rews):
            discounted_reward = rew + discounted_reward * self.gamma
            ep_rtgs.append(discounted_reward)
        return list(reversed(ep_rtgs))

    def extend_thread(self, List):
        Dict = List.pop()
        for pid in range(self.max_num_threads):
            List.extend(Dict[pid])

    def _init_hyperparameters(self, conf):
        # Default values for hyperparameters, will need to change later.
        if 'timesteps_per_batch' in conf: # timesteps per batch
            self.timesteps_per_batch = conf['timesteps_per_batch']
        else:
            self.timesteps_per_batch = 2048
        if 'max_timesteps_per_episode' in conf: # timesteps per episode
            self.max_timesteps_per_episode = conf['max_timesteps_per_episode']
        else:
            self.max_timesteps_per_episode = 256
        if 'gamma' in conf: # discount factor
            self.gamma = conf['gamma']
        else:
            self.gamma = 0.99
        if 'n_updates_per_iteration' in conf: # number of epochs per iteration
            self.n_updates_per_iteration = conf['n_updates_per_iteration']
        else:
            self.n_updates_per_iteration = 10
        if 'clip' in conf: # clip threshold as recommended by the paper
            self.clip = conf['clip']
        else:
            self.clip = 0.2
        if 'lr' in conf: # learning rate of optimizers
            self.lr = conf['lr']
        else:
            self.lr = 3e-4
        if 'save_freq' in conf:
            self.save_freq = conf['save_freq']
        else:
            self.save_freq = 10
        if 'lammbda' in conf:
            self.Lambda = conf['lambda']
        else:
            self.Lambda = 0.001
        if 'max_num_threads' in conf:
            self.max_num_threads = conf['max_num_threads']
        else:
            self.max_num_threads = 1
        if 'env' in conf:
            env_name = conf['env']
        else:
            env_name = 'Pendulum-v0'
        self.envs = [gym.make(env_name) for _ in range(self.max_num_threads)]
        # Extract environment information
        self.obs_dim = self.envs[0].observation_space.shape[0]
        self.act_dim = self.envs[0].action_space.shape[0]
        if 'device' in conf:
            self.device = torch.device(conf['device'])
        else:
            self.device = torch.device('cpu')
        if 'total_timesteps' in conf:
            self.total_timesteps = conf['total_timesteps']
        else:
            self.total_timesteps = 200000000
        if 'seed' in conf:
            torch.manual_seed(conf['seed'])
            torch.cuda.manual_seed(conf['seed'])
            torch.cuda.manual_seed_all(conf['seed'])
            np.random.seed(conf['seed'])
            torch.backends.cudnn.deterministic=True
            for i, env in enumerate(self.envs):
                env.seed(conf['seed'] + i)
        if 'log_name' in conf:
            self.log_name = conf['log_name']
        else:
            self.log_name = 'log_ppo.txt'
        if 'model_names' in conf:
            self.model_names = conf['model_names']
        else:
            self.model_names = None
        if 't_so_far' in conf:
            self.t_so_far = conf['t_so_far']
        else:
            self.t_so_far = 0
        if 'i_so_far' in conf:
            self.i_so_far = conf['i_so_far']
        else:
            self.i_so_far = 0

    def _log_summary(self):
            """
                    Print to stdout what we've logged so far in the most recent batch.
                    Parameters:
                            None
                    Return:
                            None
            """
            # Calculate logging values. I use a few python shortcuts to calculate each value
            # without explaining since it's not too important to PPO; feel free to look it over,
            # and if you have any questions you can email me (look at bottom of README)
            last_time = self.time
            self.time = time.time_ns()
            delta_t = (self.time - last_time) / 1e9
            delta_t = str(round(delta_t, 2))

            avg_ep_lens = np.mean(self.batch_lens)
            avg_ep_rews = np.mean([np.sum(ep_rews) for ep_rews in self.batch_rews])
            avg_actor_loss = np.mean([losses.to(torch.device('cpu')).float().mean() for losses in self.actor_losses])

            # Round decimal places for more aesthetic logging messages
            avg_ep_lens = str(round(avg_ep_lens, 2))
            avg_ep_rews = str(round(avg_ep_rews, 2))
            avg_actor_loss = str(round(avg_actor_loss, 5))

            # Print logging statements
            with open(self.log_name, 'a') as f:
                f.write(f"-------------------- Iteration #{self.i_so_far} --------------------\n")
                f.write(f"Average Episodic Length: {avg_ep_lens}\n")
                f.write(f"Average Episodic Return: {avg_ep_rews}\n")
                f.write(f"Average Loss: {avg_actor_loss}\n")
                f.write(f"Timesteps So Far: {self.t_so_far}\n")
                f.write(f"Iteration took: {delta_t} secs\n")
                f.write(f"------------------------------------------------------\n")
            print(f"-------------------- Iteration #{self.i_so_far} --------------------\n")
            print(f"Average Episodic Length: {avg_ep_lens}\n")
            print(f"Average Episodic Return: {avg_ep_rews}\n")
            print(f"Average Loss: {avg_actor_loss}\n")
            print(f"Timesteps So Far: {self.t_so_far}\n")
            print(f"Iteration took: {delta_t} secs\n")
            print(f"------------------------------------------------------\n")
