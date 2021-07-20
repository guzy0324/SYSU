考虑到是最后一次作业，临近期末，本次实验会相对简单许多。
pdf上是要求学生参考cs231n实现CNN，你们可以自己实现，也可以借用cs231n的代码，cs231n已经实现好了CNN和FC，你们可以直接调用
所以最简单的方法是直接利用cs231n的代码进行搭建：
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

然后你们把这段代码给调通就好了，这是cs231n课程作业，上网可以找到很多的教程。

如果自己想重新写一份，那也是可以的。