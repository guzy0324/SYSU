from ppo import *


conf = {'env': 'BipedalWalker-v3', 'device': 'cuda', 'seed': 0}
model = PPO(conf)
model.learn()
