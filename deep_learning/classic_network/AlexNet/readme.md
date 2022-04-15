# AlexNet 论文详解

### 网络结构
![](https://pic1.zhimg.com/80/v2-0244c74e98bb2a74142b7dac73a67ae0_1440w.jpg)
![](https://pic2.zhimg.com/80/v2-2fb10ed809b6585aef49d16c0db607d9_1440w.jpg)

### 本文的主要内容有：

+ **使用 ReLU 激活函数加速收敛**
在此之前，激活函数主要使用的是 ![](https://www.zhihu.com/equation?tex=f%28x%29+%3D+tanh%28x%29) 以及 ![](https://www.zhihu.com/equation?tex=f%28x%29+%3D+%5Cfrac%7B1%7D%7B1+%2B+%28e%5E%7B-x%7D%29%5E%7B-1%7D%7D) ，但是这些都是饱和激活函数，输入值处于饱和区时，其梯度几乎为 0，因此收敛极慢！
针对这一问题，我们使用线性整流单元 (Rectified Linear Units，ReLU) 作为激活函数，即： ![](https://www.zhihu.com/equation?tex=f%28x%29+%3D+max%280%2C+x%29) 。其不存在饱和区，导数始终为 1，梯度更大，计算量也更少，因此收敛更快。

+ **使用 GPU 并行，加速训练。也为之后的分组卷积（group convolution）理论奠定基础。**

+ **提出局部响应归一化（Local Response Normalization, LRN）增加泛化特性 (虽然被后人证明无效 )**

局部响应归一化 (Local Response Normalization) 的核心思想就是利用近邻数据进行归一化，其公式如下所示：![](https://www.zhihu.com/equation?tex=b_%7Bx%2C+y%7D%5E%7Bi%7D%3Da_%7Bx%2C+y%7D%5E%7Bi%7D+%2F%5Cleft%28k%2B%5Calpha+%5Csum_%7Bj%3D%5Cmax+%280%2C+i-n+%2F+2%29%7D%5E%7B%5Cmin+%28N-1%2C+i%2Bn+%2F+2%29%7D%5Cleft%28a_%7Bx%2C+y%7D%5E%7Bj%7D%5Cright%29%5E%7B2%7D%5Cright%29%5E%7B%5Cbeta%7D)
+ **使用交叠池化 (Overlapping Pooling) 防止过拟合**
在一般池化中，池化窗口 z 与滑动步长 s 相等。而交叠池化指的就是 s<z 的池化，此时相邻的滑窗之间会有重叠。在本文实现中，我们使用  ![](https://www.zhihu.com/equation?tex=z+%3D+3%2C+s+%3D+2)

+ **提出Dropout，数据增强等手段防止过拟合**

结合不同模型的预测值，是一种减小测试误差的不错的方式，但是其代价极其昂贵。因此，使用 dropout 技术，以 0.5 的概率，将每个隐藏神经元的值设定为 0。被 dropout 的神经元将不参与前向和反向传播。

在训练阶段的每次前向传播中，都会重新进行 dropout。因此，每次有新的输入时，模型会被随机采样成不同的架构，但是所有的架构共享权值。该技术可以减少神经元之间的相互依赖性。因此，模型被强制学习更加稳健的特征。

在测试期间，我们使用所有的神经元，只不过将其输出值乘以 0.5，以保证总的等效输出值不变。我们在网络的的前两层全连接层之间使用 dropout。

如果不使用 dropout ，模型可能会过拟合，但是使用 dropout，模型训练将需要近两倍的迭代次数。

dropout 图示如下所示：
![](https://pic2.zhimg.com/80/v2-bf38220f13f3e492d47445cce6cc6b05_1440w.jpg)

### 训练细节

我们使用随机梯度下降来训练模型，batch size = 128，动量系数为 0.9，权值衰减系数为 0.0005。我们发现，这种小的权值衰减对于模型的学习很重要。换言之，权值衰减不仅仅是一个正则器，其同时降低了训练误差。

权值 w 的更新规则如下：
![](https://www.zhihu.com/equation?tex=%5Cbegin%7Baligned%7D+v_%7Bi%2B1%7D+%26+%3A%3D0.9+%5Ccdot+v_%7Bi%7D-0.0005+%5Ccdot+%5Cepsilon+%5Ccdot+w_%7Bi%7D-%5Cepsilon+%5Ccdot%5Cleft%5Clangle%5Cleft.%5Cfrac%7B%5Cpartial+L%7D%7B%5Cpartial+w%7D%5Cright%7C%7Bw%7Bi%7D%7D%5Cright%5Crangle_%7BD_i%7D+%5C%5C+w_%7Bi%2B1%7D+%26+%3A%3Dw_%7Bi%7D%2Bv_%7Bi%2B1%7D+%5Cend%7Baligned%7D+)
其中，i 为迭代索引，v 表示动量值， ![](https://www.zhihu.com/equation?tex=%5Cepsilon) 表示学习速率， ![](https://www.zhihu.com/equation?tex=%5Cleft%5Clangle%5Cleft.%5Cfrac%7B%5Cpartial+L%7D%7B%5Cpartial+w%7D%5Cright%7C%7Bw%7Bi%7D%7D%5Cright%5Crangle_%7BD_%7Bi%7D%7D) 表示第 i 个 batch $D_i$ 中，目标函数对 $w_i$ 的梯度的均值。

我们初始化每一层的权值为 0 均值，标准差为 0.01 的高斯分布。我们初始化第 2，4，5 层卷积层，以及全连接隐藏层的偏置为 1。这种初始化通过给 ReLU 输出正值，加速了网络早期的训练。我们初始化剩余层的偏置为 0。





[blog reference](https://zhuanlan.zhihu.com/p/69273192)

[demo reference](https://github.com/kratzert/finetune_alexnet_with_tensorflow)

[AlexNet-pytorch 源码](https://github.com/pytorch/vision/blob/main/torchvision/models/alexnet.py)