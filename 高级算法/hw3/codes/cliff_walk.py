import random
import numpy
from matplotlib import pyplot
class cliff_walk: 
    def __init__(self):
        self.height = 4
        self.width = 12
        self.gridworld = ((0, 0, 0, 0), 
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (1, 0, 0, 0),
                        (0, 0, 0, 0))
        self.rewards = (-1, -100)
        self.start = (0, 0)
        self.goal = (11, 0)
        self.current = self.start
        self.actions = ((0, 1), (1, 0),
                        (0, -1), (-1, 0))
        self.score = 0
        self.path = dict()
    def restart(self):
        self.current = self.start
        self.score = 0
        self.path = dict()
    def is_legal(self, state):
        if 0 <= state[0] < self.width\
        and 0 <= state[1] < self.height:
            return True
        return False
    def state_next(self, action):
        return (self.current[0] + action[0],
                self.current[1] + action[1])
    def get_actions(self):
        if self.is_goal():
            return ['.']
        actions_legal = list()
        for action in self.actions:
            if self.is_legal(self.state_next(action)):
                actions_legal.append(action)
        return actions_legal
    def take_action(self, action):
        self.path[self.get_current()] = action
        R = self.get_reward(action)
        state_new = self.state_next(action)
        if self.is_legal(state_new):
            self.current = state_new
            self.score += R
            return self.current
        return None
    def get_reward(self, action):
        state_new = self.state_next(action)
        if self.is_legal(state_new):
            return self.rewards[
                self.gridworld[state_new[0]][state_new[1]]]
        return None
    def is_goal(self):
        return self.current == self.goal
    def get_goal(self):
        return self.goal
    def get_current(self):
        return self.current
    def get_score(self):
        return self.score
    def print_path(self):
        print(list(self.path))
        for y in range(self.height - 1, -1, -1):
            for x in range(self.width):
                if (x, y) == self.start:
                    print('S', end = ' ')
                elif (x, y) == self.goal:
                    print('G', end = ' ')
                elif self.path.get((x, y)) == None:
                    print(self.gridworld[x][y], end = ' ')
                elif self.path[(x, y)] == (0, 1):
                    print('↑', end = ' ')
                elif self.path[(x, y)] == (1, 0):
                    print('→', end = ' ')
                elif self.path[(x, y)] == (0, -1):
                    print('↓', end = ' ')
                elif self.path[(x, y)] == (-1, 0):
                    print('←', end = ' ')
            print()

def greedy(actions, Q_state):
    best_action = None
    max_Q = None
    for action in actions:
        if Q_state.get(action) == None:
            Q_state[action] = 0
        if best_action == None or Q_state[action] > max_Q:
            best_action = action
            max_Q = Q_state[action]
    return best_action

def epsilon_greedy(actions, Q_state, epsilon):
    if random.random() <= epsilon:
        action = random.choice(actions)
        if Q_state.get(action) == None:
            Q_state[action] = 0
        return action
    return greedy(actions, Q_state)

def sarsa(puzzle_class, num_episodes, alpha, gamma, epsilon):
    puzzle = puzzle_class()
    Q = dict()
    scores = numpy.empty((num_episodes, 1))
    for i in range(num_episodes):
        state = puzzle.get_current()
        if Q.get(state) == None:
            Q[state] = dict()
        action = \
            epsilon_greedy(puzzle.get_actions(), Q[state], epsilon)
        while not puzzle.is_goal():
            R = puzzle.get_reward(action)
            puzzle.take_action(action)
            state_new = puzzle.get_current()
            if Q.get(state_new) == None:
                Q[state_new] = dict()
            action_new = epsilon_greedy(puzzle.get_actions(),
                                        Q[state_new], epsilon)
            Q[state][action] = Q[state][action]\
                + alpha * (R + gamma * Q[state_new][action_new]
                           - Q[state][action])
            state = state_new
            action = action_new
        scores[i] = puzzle.get_score()
        if i == num_episodes - 1:
            puzzle.print_path()
        else:
            puzzle.restart()
    return scores

def q_learning(puzzle_class, num_episodes, alpha, gamma, epsilon):
    puzzle = puzzle_class()
    Q = dict()
    scores = numpy.empty((num_episodes, 1))
    for i in range(num_episodes):
        while not puzzle.is_goal():
            state = puzzle.get_current()
            if Q.get(state) == None:
                Q[state] = dict()
            action =\
                epsilon_greedy(puzzle.get_actions(), Q[state], epsilon)
            R = puzzle.get_reward(action)
            puzzle.take_action(action)
            state_new = puzzle.get_current()
            if Q.get(state_new) == None:
                Q[state_new] = dict()
            action_new = greedy(puzzle.get_actions(), Q[state_new])
            Q[state][action] = Q[state][action]\
                + alpha * (R + gamma * Q[state_new][action_new]
                           - Q[state][action])
            state = state_new
        scores[i] = puzzle.get_score()
        if i == num_episodes - 1:
            puzzle.print_path()
        else:
            puzzle.restart()
    return scores

num_episodes = 500
range_num_episodes = range(num_episodes)
alpha = 0.5
gamma = 1
epsilon = 0.001
run_times = 20
avg_sarsa_scores = numpy.zeros((num_episodes, 1))
avg_q_learning_scores = numpy.zeros((num_episodes, 1))
for i in range(run_times):
    print('Sarsa')
    avg_sarsa_scores +=\
        sarsa(cliff_walk, num_episodes, alpha, gamma, epsilon)
    print('Q-Learning')
    avg_q_learning_scores +=\
        q_learning(cliff_walk, num_episodes, alpha, gamma, epsilon)
avg_sarsa_scores /= run_times
avg_q_learning_scores /= run_times
pyplot.plot(range_num_episodes, avg_sarsa_scores)
pyplot.plot(range_num_episodes, avg_q_learning_scores)
pyplot.xlabel('Episode')
pyplot.ylabel('Average score of' + str(run_times) + 'times running')
pyplot.legend(['Sarsa', 'Q-Learning'])
pyplot.ylim(-100, 0)
pyplot.show()
