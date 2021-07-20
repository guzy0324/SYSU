from gasil import *


conf = {'env': 'BipedalWalker-v3', 'device': 'cuda', 'seed': 0}
model = GASIL(conf)
model.learn()
