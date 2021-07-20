from cs231n.data_utils import get_CIFAR10_data
from cs231n.classifiers.cnn import ThreeLayerConvNet
from cs231n.solver import Solver
from matplotlib import pyplot
if __name__ == '__main__':
    solver=Solver(ThreeLayerConvNet(), get_CIFAR10_data())
    solver.train()
    pyplot.plot(solver.loss_history)
    pyplot.xlabel("Iteration")
    pyplot.ylabel("Loss")
    pyplot.show()
