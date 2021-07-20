学习资源
函数库

1、RL-Glue：提供了一个能将强化学习代理、环境和实验程序连接起来的标准界面，且可进行跨语言编程。

地址：http://glue.rl-community.org/wiki/Main_Page

2、Gym：由OpenAI开发，是一个用于开发强化学习算法和性能对比的工具包，它可以训练代理学习很多任务，包括步行和玩乒乓球游戏等。

地址：https://gym.openai.com/

3、RL4J：是集成在deeplearning4j库下的一个强化学习框架，已获得Apache 2.0开源许可。

地址：https://github.com/deeplearning4j/rl4j

4、TensorForce：一个用于强化学习的TensorFlow库。

地址：https://github.com/reinforceio/tensorforce

论文集

1、用通用强化学习算法自我对弈来掌握国际象棋和将棋

题目：Mastering Chess and Shogi by Self-Play with a General Reinforcement Learning Algorithm

地址：https://arxiv.org/abs/1712.01815

这篇文章有13位作者，提出了AlphaZero方法。在这篇论文中，作者将先前的AlphaGo Zero方法推广到一个单一的AlphaZero算法，它可以在多个具有挑战性的领域实现超越人类的性能，同样利用的是“白板”强化学习（“白板”指的是所有知识均由感官和经验得来，即从零开始的学习）。从随机下棋开始，除了游戏规则外，没有输入任何领域知识，AlphaZero在24小时内实现了在国际象棋、将棋和围棋上超越人类水平的表现，并且在这三种棋上都以令人信服的成绩击败了当前的世界冠军程序。

2、深化强化学习综述

题目：Deep Reinforcement Learning: An Overview

地址：https://arxiv.org/abs/1701.07274

这篇论文概述了深度强化学习中一些最新精彩工作，主要说明了六个核心要素、六个重要机制和十二个有关应用。文章中先介绍了机器学习、深度学习和强化学习的背景，接着讨论了强化学习的核心要素，包括DQN网络、策略、奖励、模型、规划和搜索。

3、用深度强化学习玩Atari游戏

题目：Playing Atari with Deep Reinforcement Learning

地址：https://arxiv.org/abs/1312.5602

这是DeepMind公司2014年的NIPS论文。这篇论文提出了一种深度学习方法，利用强化学习的方法，直接从高维的感知输入中学习控制策略。该模型是一个卷积神经网络，利用Q-learning的变体来进行训练，输入是原始像素，输出是预测未来奖励的价值函数。此方法被应用到Atari 2600游戏中，不需要调整结构和学习算法，在测试的七个游戏中6个超过了以往方法并且有3个超过人类水平。

4、用深度强化学习实现人类水平的控制

题目：Human-Level Control Through Deep Reinforcement Learning

地址：https://web.stanford.edu/class/psych209/Readings/MnihEtAlHassibis15NatureControlDeepRL.pdf

这是DeepMind公司2015年的Nature论文。强化学习理论根植于关于动物行为的心理学和神经科学，它可以很好地解释代理如何优化他们对环境的控制。为了在真实复杂的物理世界中成功地使用强化学习算法，代理必须面对这个困难任务：利用高维的传感器输入数据，推导出环境的有效表征，并把先前经验泛化到新的未知环境中。

讲座教程

1、强化学习（Georgia Tech, CS 8803）

地址：https://www.udacity.com/course/reinforcement-learning—ud600

官网介绍：如果你对机器学习感兴趣并且希望从理论角度来学习，你应该选择这门课程。本课程通过介绍经典论文和最新工作，带大家从计算机科学角度去探索自动决策的魅力。本课程会针对单代理和多代理规划以及从经验中学习近乎最佳决策这两个问题，来研究相应的高效算法。课程结束后，你将具备复现强化学习中已发表论文的能力。

2、强化学习（Stanford, CS234）

地址：http://web.stanford.edu/class/cs234/index.html

官网介绍：要实现真正的人工智能，系统要能自主学习并做出正确的决定。强化学习是一种这样的强大范式，它可应用到很多任务中，包括机器人学、游戏博弈、消费者建模和医疗服务。本课程详细地介绍了强化学习的有关知识，你通过学习能了解当前面临问题和主要方法，也包括如何进行泛化和搜索。

3、深度强化学习（Berkeley, CS 294, Fall 2017）

地址：http://rll.berkeley.edu/deeprlcourse/

官网介绍：本课程需要一定的基础知识，包括强化学习、数值优化和机器学习。我们鼓励对以下概念不熟悉的学习提前阅读下方提供的参考资料。课堂上开始前会简单回顾下这些内容。

4、用Python玩转深度强化学习（Udemy高级教程）

地址：https://www.udemy.com/deep-reinforcement-learning-in-python/

官网介绍：本课程主要介绍有关深度学习和神经网络在强化学习中的应用。本课程需要一定的基础知识（包括强化学习基础、马尔可夫决策、动态编程、蒙特卡洛搜索和时序差分学习），以及深度学习基础编程。

最后，原文地址在此：https://blog.algorithmia.com/introduction-to-reinforcement-learning/