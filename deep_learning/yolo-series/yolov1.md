# YOLO V1算法
## 一、物体检测算法概述
物体检测（object detection）是计算机视觉中一个重要的分支，其大致功能是在一张图片中，用最小矩形框框出目标物体位置，并进行分类。

#### 物体检测的两个步骤可以概括为：

步骤一：检测目标位置（生成矩形框）

步骤二：对目标物体进行分类

#### 目标检测算法目前主要分为两种，two-stage和one-stage

+ two-stage: 基于Region Proposal的R-CNN系列算法(R-CNN, Fast R-CNN, Faster R-CNN)，需要先使用启发式方法（selective search）或者CNN网络（RPN）产生Region Proposal，然后再在Region Proposal上做分类与回归，检测准确度高，但是速度慢

![](https://img-blog.csdnimg.cn/2019011500233090.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2dhb3l1MTI1MzQwMTU2Mw==,size_16,color_FFFFFF,t_70)
![](https://img-blog.csdnimg.cn/20191117212416386.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2dhb3l1MTI1MzQwMTU2Mw==,size_16,color_FFFFFF,t_70)

+ one-stage：代表是YOLO, SSD，其主要思路是均匀地在图片的不同位置进行密集抽样，抽样时可以采用不同尺度和长宽比，然后利用CNN提取特征后直接进行分类与回归，整个过程只需要一步，其仅仅使用一个CNN网络直接预测不同目标的类别与位置，算法是速度快，但是准确性要低一些，均匀的密集采样的一个重要缺点是训练比较困难，这主要是因为正样本与负样本（背景）极其不均衡[（Focal Loss的理解）](https://zhuanlan.zhihu.com/p/80692105)，导致模型准确度稍低

![](https://img-blog.csdnimg.cn/20191117151315370.png)
![](https://img-blog.csdnimg.cn/20191117212234851.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2dhb3l1MTI1MzQwMTU2Mw==,size_16,color_FFFFFF,t_70)


## 二、yolo算法思想

[yolov1-论文地址](https://arxiv.org/pdf/1506.02640.pdf)
### 2.1 网络设计：
![](https://pic2.zhimg.com/80/v2-970ca183f3f0c76591c82ca910d2bc5d_1440w.jpg)

<img src=https://pic4.zhimg.com/80/v2-de260ef28cebab6ee76c5c799163429b_1440w.jpg alt="Pulpit rock" width="800" height="1000">

输入图像大小为448 * 448，经过若干个卷积层与池化层，变为7* 7* 1024张量（图一中倒数第三个立方体），最后经过两层全连接层，输出张量维度为7* 7 * 30，这就是Yolo v1的整个神经网络结构，和一般的卷积物体分类网络没有太多区别，最大的不同就是：分类网络最后的全连接层，一般连接于一个一维向量，向量的不同位代表不同类别，而这里的输出向量是一个三维的张量（7*7*30）。上图中Yolo的backbone网络结构，受启发于GoogLeNet，也是v2、v3中Darknet的先锋。本质上来说没有什么特别，没有使用BN层，用了一层Dropout。除了最后一层的输出使用了线性激活函数，其他层全部使用Leaky Relu激活函数。




[代码参考-1](https://github.com/gliese581gg/YOLO_tensorflow)
[代码参考-2](https://github.com/hizhangp/yolo_tensorflow)
