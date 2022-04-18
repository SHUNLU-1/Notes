# GoogLeNet 

## Incepetion V1
#### 1.naive版本的Inception网络
Inception架构的主要思想是找出如何用密集成分来近似最优的局部稀疏结。
![](https://pic4.zhimg.com/80/v2-14937e5345d444264f0791954b8a5373_720w.jpg)

对上图做以下说明：

+ 采用不同大小的卷积核意味着不同大小的感受野，最后拼接意味着不同尺度特征的融合；
+ 之所以卷积核大小采用1*1、3*3和5*5，主要是为了方便对齐。设定卷积步长stride=1之后，只要分别设定padding =0、1、2，采用same卷积可以得到相同维度的特征，然后这些特征直接拼接在一起；
+ 文章说很多地方都表明pooling挺有效，所以Inception里面也嵌入了pooling。
+ 网络越到后面特征越抽象，且每个特征涉及的感受野也更大，随着层数的增加，3x3和5x5卷积的比例也要增加。

naive版本的Inception网络的缺陷：计算成本。使用5x5的卷积核仍然会带来巨大的计算量，约需要1.2亿次的计算量。

![](https://pic4.zhimg.com/80/v2-31d5a665c3031eed9a609a28a957f7af_720w.jpg)

#### 2.Inception V1网络

为减少计算成本，采用1x1卷积核来进行降维。 示意图如下：
![](https://pic3.zhimg.com/80/v2-80abf83b95c8246675697e5e65b0b66a_720w.jpg)

在3x3和5x5的过滤器前面，max pooling后分别加上了1x1的卷积核，最后将它们全部以通道/厚度为轴拼接起来，最终输出大小为28*28*256，卷积的参数数量比原来减少了4倍，得到最终版本的Inception模块：
![](https://pic1.zhimg.com/80/v2-d664caacc21eec3c9d4e9d863ba807e8_720w.jpg)

#### 3.googLeNet——Inception V1结构
![](https://pic1.zhimg.com/80/v2-dce01356bfb0289ad1e45c5d0894e900_720w.jpg)

对上图做如下说明：
+ 显然GoogLeNet采用了Inception模块化（9个）的结构，共22层，方便增添和修改；
+ 网络最后采用了average pooling来代替全连接层，想法来自NIN,参数量仅为AlexNet的1/12,性能优于AlexNet，事实证明可以将TOP1 accuracy提高0.6%。但是，实际在最后还是加了一个全连接层，主要是为了方便finetune；
+ 虽然移除了全连接，但是网络中依然使用了Dropout ;
+ 为了避免梯度消失，网络额外增加了2个辅助的softmax用于向前传导梯度。文章中说这两个辅助的分类器的loss应该加一个衰减系数，但看caffe中的model也没有加任何衰减。此外，实际测试的时候，这两个额外的softmax会被去掉。


## Inception V2结构
#### 1.网络优化
使用vgg网络思想,可以用2个连续的3x3卷积层(stride=1)组成的小网络来代替单个的5x5卷积层，这便是Inception V2结构，保持感受野范围的同时又减少了参数量
![](https://pic4.zhimg.com/80/v2-80d4a8d1e204c9478369c9661cc02c47_720w.jpg)
![](https://pic4.zhimg.com/80/v2-7463a5487e7c2ddec0fea2f8799ecfe7_720w.jpg)
#### 2.引入BN层
![](https://pic3.zhimg.com/80/v2-5ee13db1ea2a96c78cbd08f6d15ae9c6_720w.jpg)
![](https://pic2.zhimg.com/80/v2-c3ba2fe75a9050ba8ce9a5a2100f4705_720w.jpg)

## Inception V3结构 
#### 1.网络优化
文章考虑了nx1卷积核，如下图所示的取代3x3卷积：于是，任意nxn的卷积都可以通过1xn卷积后接nx1卷积来替代。实际上，作者发现在网络的前期使用这种分解效果并不好，还有在中度大小的feature map上使用效果才会更好，对于mxm大小的feature map,建议m在12到20之间。用nx1卷积来代替大卷积核，这里设定n=7来应对17x17大小的feature map。该结构被正式用GoogLeNet V2中。
![](https://pic3.zhimg.com/80/v2-ff009d361db8ccf8cb09be280c6da1f6_720w.jpg)

![](https://img-blog.csdn.net/20180118154002880?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbG92ZWxpdXp6/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)
![](https://img-blog.csdn.net/20180118153838739?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbG92ZWxpdXp6/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![](https://img-blog.csdn.net/20180123155323780?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbG92ZWxpdXp6/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

## Inception V4结构 
#### 结合了残差神经网络ResNet
![](https://img-blog.csdn.net/20180123155046399?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbG92ZWxpdXp6/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

[googlenet paper](https://arxiv.org/pdf/1409.4842.pdf)