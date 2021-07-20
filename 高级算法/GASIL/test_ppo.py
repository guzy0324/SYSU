from ppo import *
from eval_policy import *
import gym


with open('log_ppo.txt') as f:
    lines = [float(line[25:]) for line in f.readlines() if line.startswith('Average Episodic Return:')]

conf = {'env': 'BipedalWalker-v3', 'seed': 0}
model = PPO(conf)
model.actor.load_state_dict(torch.load('models_gasil/actor' + str(max(range(10, len(lines), 10), key=lambda i: lines[i]))))
eval_policy(model.actor, model.envs[0], True)
