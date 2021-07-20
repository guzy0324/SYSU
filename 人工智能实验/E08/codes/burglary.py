from pomegranate import *
B = DiscreteDistribution({True: 0.001, False: 0.999})
E = DiscreteDistribution({True: 0.002, False: 0.998})
A = ConditionalProbabilityTable(
    [[True, True, True, 0.95],
     [True, True, False, 0.05],
     [True, False, True, 0.94],
     [True, False, False, 0.06],
     [False, True, True, 0.29],
     [False, True, False, 0.71],
     [False, False, True, 0.001],
     [False, False, False, 0.999]],
    [B, E])
J = ConditionalProbabilityTable(
    [[True, True, 0.9],
     [True, False, 0.1],
     [False, True, 0.05],
     [False, False, 0.95]],
    [A])
M = ConditionalProbabilityTable(
    [[True, True, 0.7],
     [True, False, 0.3],
     [False, True, 0.01],
     [False, False, 0.99]],
    [A])
s0 = State(B, name='B')
s1 = State(E, name='E')
s2 = State(A, name='A')
s3 = State(J, name='J')
s4 = State(M, name='M')
model = BayesianNetwork('Burglary')
model.add_states(s0, s1, s2, s3, s4)
model.add_transition(s0, s2)
model.add_transition(s1, s2)
model.add_transition(s2, s3)
model.add_transition(s2, s4)
model.bake()
PA1 = model.predict_proba({})[2].parameters[0][True]
PJ1M0 = model.predict_proba({'M': False})[
    3].parameters[0][True] * model.predict_proba({})[4].parameters[0][False]
PA1_J1M0 = model.predict_proba({'J': True, 'M': False})[2].parameters[0][True]
PB1_A1 = model.predict_proba({'A': True})[0].parameters[0][True]
PB1_J1M0 = model.predict_proba({'J': True, 'M': False})[0].parameters[0][True]
PJ1M0_B0 = (1 - PB1_J1M0) * PJ1M0 / \
    model.predict_proba({})[0].parameters[0][False]
print(PA1)
print(PJ1M0)
print(PA1_J1M0)
print(PB1_A1)
print(PB1_J1M0)
print(PJ1M0_B0)
