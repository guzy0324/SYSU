import numpy as np
import torch
import torch.nn as nn
from tqdm import tqdm
from torch.optim import Adam
from queue import PriorityQueue
import math

from good_trajectory import GoodTrajectory
from mlp_discriminator import Discriminator
from ppo import PPO


class GASIL(PPO):
    def __init__(self, conf=dict()):
        super(GASIL, self).__init__(conf)

        # ALG STEP 1
        # Initialize discriminator network
        self.D = Discriminator(self.obs_dim + self.act_dim).to(self.device)

        if self.model_names is not None:
            self.D.load_state_dict(torch.load(self.model_names[2]))

        # Initialize discriminator optimizer
        self.D_optim = Adam(self.D.parameters(), lr=self.lr)

        # Initialize discriminator criterion
        self.D_criterion = nn.BCELoss()

        # Initialize good trajectory buffer B
        self.B = PriorityQueue()

    def learn(self):
        pbar = tqdm(total=self.total_timesteps)
        pbar.update(self.t_so_far)
        while self.t_so_far < self.total_timesteps: # ALG STEP 2
            # ALG STEP 3
            self.rollout()

            # Calculate how many timesteps we collected this batch
            delta_t = np.sum(self.batch_lens)
            self.t_so_far += delta_t

            # Increment the number of iterations
            self.i_so_far += 1

            # Update the discriminator \phi via gradient ascent with:
            for _ in range(self.n_updates_of_D_per_iteration):
                g_o = self.D(torch.cat([self.batch_obs, self.batch_acts], 1))
                e_o = self.D(torch.cat([self.batch_E_obs, self.batch_E_acts], 1))
                self.D_optim.zero_grad()
                discrim_loss = self.D_criterion(g_o, torch.ones((self.batch_obs.shape[0], 1), device=self.device)) + \
                    self.D_criterion(e_o, torch.zeros((self.batch_E_obs.shape[0], 1), device=self.device))
                discrim_loss.backward()
                self.D_optim.step()
            print('\ndiscrim_loss:\t', float(discrim_loss.detach()))

            pbar.update(delta_t)
            self.ppo_update()

            # Print a summary of our training so far
            self._log_summary()

            # Save our model if it's time
            if self.i_so_far % self.save_freq == 0:
                torch.save(self.actor.state_dict(), './models_gasil/actor' + str(self.i_so_far))
                torch.save(self.critic.state_dict(), './models_gasil/critic' + str(self.i_so_far))
                torch.save(self.D.state_dict(), './models_gasil/D' + str(self.i_so_far))

    def rollout(self):
        # Batch data
        self.batch_obs = [] # batch observations
        self.batch_acts = [] # batch actions
        self.batch_log_probs = [] # log probs of each action
        self.batch_rews = [] # batch rewards
        batch_rtgs_actual = [] # batch rewards-to-go
        self.batch_rtgs = [] # batch modified rewards-to-go
        self.batch_lens = [] # episodic lengths in batch

        self.actor = self.actor.to(torch.device('cpu'))
        self.D = self.D.to(torch.device('cpu'))
        self.cov_mat = self.cov_mat.to(torch.device('cpu'))

        # Number of timestpes run so far this batch
        t = 0
        while t < self.timesteps_per_batch:
            # Rewards this episode
            ep_rews = []
            ep_obs = []
            ep_acts = []
            obs = self.envs[0].reset()
            done = False
            for ep_t in range(self.max_timesteps_per_episode):
                # Increment timesteps ran this batch so far
                t += 1
                # Collect observation
                ep_obs.append(obs)
                action, log_prob = self.get_action(obs)
                obs, rew, done, _ = self.envs[0].step(action)

                # Collect reward, action, and log prob
                ep_rews.append(rew)
                ep_acts.append(action)
                self.batch_log_probs.append(log_prob)

                if done:
                    break

            # Collect episodic length and rewards
            self.batch_lens.append(ep_t + 1) # plus 1 because timestep starts at 0

            ep_obs = torch.tensor(ep_obs, dtype=torch.float)
            ep_acts = torch.tensor(ep_acts, dtype=torch.float)
            self.batch_rews.append(ep_rews)
            self.batch_obs.append(ep_obs)
            self.batch_acts.append(ep_acts)

            # ALG STEP #4
            ep_rtgs_actual = self.compute_rtgs(np.array(ep_rews))
            batch_rtgs_actual.extend(ep_rtgs_actual)

            # Modified reward function
            ep_rtgs = self.compute_rtgs(np.array(ep_rews) - self.alpha_func(self.i_so_far) * self.D(torch.cat([ep_obs, ep_acts], 1)).detach().squeeze(1).numpy())
            self.batch_rtgs.extend(ep_rtgs)

            # Update good trajectory buffer B using \Tau_\pi
            self.B.put(GoodTrajectory(ep_obs, ep_acts, np.mean(ep_rtgs_actual)))
            if self.B.qsize() > self.K:
                self.B.get()

        print('\nalpha:\t', self.alpha_func(self.i_so_far))
        self.actor = self.actor.to(self.device)
        self.D = self.D.to(self.device)
        self.cov_mat = self.cov_mat.to(self.device)

        # Reshape data as tensors in the shape specified before returning
        self.batch_obs = torch.cat(self.batch_obs).to(self.device)
        self.batch_acts = torch.cat(self.batch_acts).to(self.device)
        self.batch_log_probs = torch.tensor(self.batch_log_probs, dtype=torch.float, device=self.device)
        self.batch_rtgs = torch.tensor(self.batch_rtgs, dtype=torch.float, device=self.device)

        # Update good trajectory buffer B using \Tau_\pi
        worst = self.B.get()
        batch_rtgs_mean = np.mean(batch_rtgs_actual)
        while worst.R <= batch_rtgs_mean:
            worst = self.B.get()
        self.B.put(worst)

        # Sample good trajectories \Tau_E ~ B
        B = [self.B.get() for _ in range(self.B.qsize())]
        print('\nB_len_max_min:\t', len(B), max([b.R for b in B]), min([b.R for b in B]))
        batch_E = np.random.choice(B, size=len(self.batch_lens), replace=True)
        for E in B:
            self.B.put(E)

        # Reshape data as tensors in the shape specified before returning
        self.batch_E_obs = list()
        self.batch_E_acts = list()
        for E in batch_E:
            self.batch_E_obs.append(E.obs)
            self.batch_E_acts.append(E.acts)
        self.batch_E_obs = torch.cat(self.batch_E_obs).to(self.device)
        self.batch_E_acts = torch.cat(self.batch_E_acts).to(self.device)
    
    def _init_hyperparameters(self, conf):
        # Default values for hyperparameters, will need to change later.
        super(GASIL, self)._init_hyperparameters(conf)

        if 'n_updates_of_D_per_iteration' in conf: # number of updates of discriminator per iteration
            self.n_updates_of_D_per_iteration = conf['n_updates_of_D_per_iteration']
        else:
            self.n_updates_of_D_per_iteration = 20
        if 'K' in conf: # size of good trajectory buffer B
            self.K = conf['K']
        else:
            self.K = 10
        if 'alpha_func' in conf: # alpha func
            self.alpha_func = conf['alpha_func']
        else:
            self.alpha_func = lambda i: math.exp(min(i, 1000) - 1000)
        if 'log_name' in conf:
            self.log_name = conf['log_name']
        else:
            self.log_name = 'log_gasil.txt'
