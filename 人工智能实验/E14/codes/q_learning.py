import random
from tqdm import tqdm


class Game(object):
    def __init__(self):
        self.__edges = ((4, ),
                    (3, 5),
                    (3, ),
                    (1, 2, 4),
                    (0, 3, 5),
                    (1, 4, 5))
        self.__goal = 5

    def list_states(self):
        return range(len(self.__edges))

    def start(self, state=None):
        if state is None:
            self.__current = random.randint(0, 4)
        elif state >= len(self.__edges):
            return None
        else:
            self.__current = state
        return self.__current

    def current_state(self):
        return self.__current

    def list_actions(self):
        return range(len(self.__edges[self.__current]))

    def next_state(self, action):
        if action >= len(self.__edges[self.__current]):
            return None
        return self.__edges[self.__current][action]

    def reward(self, action):
        next_state = self.next_state(action)
        if next_state is None:
            return None
        if next_state == self.__goal:
            return 100
        return 0

    def run(self, action):
        next_state = self.next_state(action)
        if next_state is None:
            return None
        self.__current = next_state
        if next_state == self.__goal:
            return 100
        return 0

    def reach_goal(self):
        return self.__current == self.__goal


def greedy(actions, Q_state):
    return max(actions, key=lambda k: Q_state[k])

def epsilon_greedy(actions, Q_state, epsilon):
    if epsilon < 0 or epsilon > 1:
        return None
    if random.random() < epsilon:
        return random.choice(actions)
    return greedy(actions, Q_state)

Q = dict()
def q_learning(num_episodes, epsilon, alpha, gamma, game):
    global Q
    for episode in tqdm(range(num_episodes)):
        game.start()
        while not game.reach_goal():
            actions = game.list_actions()
            state = game.current_state()
            if state not in Q:
                Q[state] = {a: 0 for a in actions}
            action = epsilon_greedy(actions, Q[state], epsilon)
            reward = game.run(action)
            actions = game.list_actions()
            next_state = game.current_state()
            if next_state not in Q:
                Q[next_state] = {a: 0 for a in actions}
            Q[state][action] += alpha * (reward + gamma * Q[next_state][greedy(actions, Q[next_state])] - Q[state][action])


if __name__ == '__main__':
    random.seed(0)
    game = Game()
    q_learning(500, 0.01, 0.5, 1, game)
    print(Q)
    for start in game.list_states():
        game.start(start)
        while not game.reach_goal():
            actions = game.list_actions()
            state = game.current_state()
            if state not in Q:
                Q[state] = {a: 0 for a in actions}
            print(state, end='->')
            action = greedy(actions, Q[state])
            reward = game.run(action)
        print(game.current_state())
