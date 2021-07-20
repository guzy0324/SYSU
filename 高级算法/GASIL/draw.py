import matplotlib.pyplot as plt
with open('log_ppo.txt') as f:
    plt.plot([float(line[25:]) for line in f.readlines() if line.startswith('Average Episodic Return:')])
with open('log_gasil.txt') as f:
    plt.plot([float(line[25:]) for line in f.readlines() if line.startswith('Average Episodic Return:')])
plt.xlabel('Iteration')
plt.ylabel('Average Episodic Return')
plt.legend(['ppo', 'gasil'])
plt.show()
