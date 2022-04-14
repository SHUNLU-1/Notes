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

<img src=https://pic4.zhimg.com/80/v2-de260ef28cebab6ee76c5c799163429b_1440w.jpg alt="Pulpit rock" width="800" height="800">

输入图像大小为448 * 448，经过若干个卷积层与池化层，变为7* 7* 1024张量（图一中倒数第三个立方体），最后经过两层全连接层，输出张量维度为7* 7 * 30，这就是Yolo v1的整个神经网络结构，和一般的卷积物体分类网络没有太多区别，最大的不同就是：分类网络最后的全连接层，一般连接于一个一维向量，向量的不同位代表不同类别，而这里的输出向量是一个三维的张量（7*7*30）。上图中Yolo的backbone网络结构，受启发于GoogLeNet，也是v2、v3中Darknet的先锋。本质上来说没有什么特别，没有使用BN层，用了一层Dropout。除了最后一层的输出使用了线性激活函数，其他层全部使用Leaky Relu激活函数。

![](https://pic2.zhimg.com/80/v2-f515b73effc632b1cad3a59586592fd5_1440w.jpg)

+ YOLO的CNN网络将输入的图片分割成 s*s 网格，每个单元格负责去检测那些中心点落在该格子内的目标，如图所示，**可以看到狗这个目标的中心落在左下角一个单元格内，那么该单元格负责预测这个狗**(这个实际是在训练阶段，用来计算 loss用的，在测试阶段，没有这个概念)
+ 每个单元格会预测B个边界框（bounding box）以及边界框的置信度（confidence score）
> 所谓置信度其实包含两个方面，一是这个边界框含有目标的可能性大小，二是这个边界框的准确度，置信度可以定义为 ![](https://www.zhihu.com/equation?tex=Pr%28object%29%2AIoU%5Cfrac%7Btruth%7D%7Bpred%7D)
前者记为Pr(object)，当该边界框是背景时（即不包含目标）为0，当该边界框包含目标时为1.后者边界框的准确度用预测框和实际框的IoU来表示 ![](https://www.zhihu.com/equation?tex=IoU%5Cfrac%7Btruth%7D%7Bpred%7D)

+ 边界框的大小和位置用4个数值来表示，(x, y, w, h)，其中 (x,y) 是边界框的中心坐标，而 w 和 h 是边界框的宽与高，还有一点要注意，中心坐标的预测值 (x,y) 是相对于每个单元格左上角坐标点的偏移值，并且单位是相对于单元格大小的，单元格的坐标定义如图所示。而边界框的 w 和 h 预测值是相对于整个图片的宽与高的比例，这样理论上4个元素的大小应该在 [0,1] 范围。这样，每个边界框的预测值实际上包含5个元素：(x, y, w, h, c)，其中前4个表征边界框的大小与位置，而最后一个值是置信度

+ 分类问题，对于每一个单元格其还要给出预测出 C 个类别概率值，该单元格负责预测的边界框其目标属于各个类别的概率。这些概率值其实是在各个边界框置信度下的条件概率，即![](https://www.zhihu.com/equation?tex=Pr%28class_%7Bi%7D%7Cobject%29)。YOlO v1算法中，一个单元只预测一组类别概率值，这是v1算法的一个缺点，在后来的改进版本中，YOLO 9000是把类别概率预测值与边界框是绑定在一起的。

+ 我们可以计算出各个边界框类别置信度（class-specific confidence scores）:![](https://www.zhihu.com/equation?tex=Pr%28class_%7Bi%7D%7Cobject%29%2APr%28object%29%2A%5Ctext%7BIOU%7D%5E%7Btruth%7D_%7Bpred%7D%3DPr%28class_%7Bi%7D%29%2A%5Ctext%7BIOU%7D%5E%7Btruth%7D_%7Bpred%7D)。

+ 边界框类别置信度表征的是该边界框中目标属于各个类别的可能性大小以及边界框匹配目标的好坏。后面会说，一般会根据类别置信度来过滤网络的预测框

### 2.2 训练损失函数分析

**YOLO算法将目标检测看成回归问题，所以采用的是均方差损失函数，包括区分定位误差和分类误差**

+ 对于定位误差，即边界框坐标预测误差，包括(x，y，w，h)采用较大的权重5，对于较小的边界框，坐标误差应该要比较大的边界框要更敏感。为了保证这一点，将网络的边界框的宽与高预测改为对其平方根的预测
+ 对于分类误差，区分包含目与不包含目标的边界框的置信度，包含目标的权重值为1，其它权重值均设为0.5


首先区分定位误差和分类误差。对于定位误差，即边界框坐标预测误差，采用较大的权重![](https://www.zhihu.com/equation?tex=%5Clambda+_%7Bcoord%7D%3D5)  。然后其区分不包含目标的边界框与含有目标的边界框的置信度，对于前者，采用较小的权重值![](https://www.zhihu.com/equation?tex=%5Clambda+_%7Bnoobj%7D%3D0.5)。其它权重值均设为1。然后采用均方误差，其同等对待大小不同的边界框，但是实际上较小的边界框的坐标误差应该要比较大的边界框要更敏感。为了保证这一点，将网络的边界框的宽与高预测改为对其平方根的预测，即预测值变为![](https://www.zhihu.com/equation?tex=%28x%2Cy%2C%5Csqrt%7Bw%7D%2C+%5Csqrt%7Bh%7D%29)。

另外一点时，由于每个单元格预测多个边界框。但是其对应类别只有一个。那么在训练时，如果该单元格内确实存在目标，那么只选择与ground truth的IOU最大的那个边界框来负责预测该目标，而其它边界框认为不存在目标。这样设置的一个结果将会使一个单元格对应的边界框更加专业化，其可以分别适用不同大小，不同高宽比的目标，从而提升模型性能。大家可能会想如果一个单元格内存在多个目标怎么办，其实这时候Yolo算法就只能选择其中一个来训练，这也是Yolo算法的缺点之一。要注意的一点时，对于不存在对应目标的边界框，其误差项就是只有置信度，坐标项误差是没法计算的。而只有当一个单元格内确实存在目标时，才计算分类误差项，否则该项也是无法计算的。

综上讨论，最终的损失函数计算如下：

![](https://pic2.zhimg.com/80/v2-ede1de8301255063e04ec529224a9865_1440w.jpg)

其中第一项是边界框中心坐标的误差项， ![](https://www.zhihu.com/equation?tex=1%5E%7Bobj%7D_%7Bij%7D) 指的是第 i 个单元格存在目标，且该单元格中的第 j 个边界框负责预测该目标。第二项是边界框的高与宽的误差项。第三项是包含目标的边界框的置信度误差项。第四项是不包含目标的边界框的置信度误差项。而最后一项是包含目标的单元格的分类误差项， ![](https://www.zhihu.com/equation?tex=1%5E%7Bobj%7D_%7Bi%7D) 指的是第 i 个单元格存在目标。这里特别说一下置信度的target值 ![](https://www.zhihu.com/equation?tex=C_i) ，如果是不存在目标，此时由于 ![](https://www.zhihu.com/equation?tex=Pr%28object%29%3D0)，那么  ![](https://www.zhihu.com/equation?tex=C_i%3D0)。如果存在目标，![](https://www.zhihu.com/equation?tex=Pr%28object%29%3D1) ，此时需要确定 ![](https://www.zhihu.com/equation?tex=%5Ctext%7BIOU%7D%5E%7Btruth%7D_%7Bpred%7D)，当然你希望最好的话，可以将IOU取1，这样 ![](https://www.zhihu.com/equation?tex=C_i%3D1) ，但是在YOLO实现中，使用了一个控制参数rescore（默认为1），当其为1时，IOU不是设置为1，而就是计算truth和pred之间的真实IOU。不过很多复现YOLO的项目还是取 ![](https://www.zhihu.com/equation?tex=C_i%3D1)，这个差异应该不会太影响结果吧。

### 2.3 YOLO有两个缺点：
+ 一个缺点在于定位不准确，
+ 另一个缺点在于和基于region proposal的方法相比召回率较低



**tips**
(1)  during train: 每个单元格使用 2 个边界框。但是在一个单元格中，我们只能预测一个对象。为什么我们使用两个边界框？ 
> 当他们训练网络时，他们选择了哪个预测器（从某个网格单元中的 B 个框中读取一个框）来惩罚。他们通过具有基本事实的最高 IoU 选择一个预测器。引自论文：“我们指定一个预测器“负责”预测一个对象，根据该预测与基本事实的当前 IOU 最高。因此，假设在预测过程中，第一个框的 IoU 为 0.3，第二个框的 IoU 为 0.7，我们选择第二个框来负责预测该对象，我们将仅从该框累积损失。因此，例如，在训练期间，网络自然会学习使用第一个预测器预测高框（人）和使用第二个预测器（汽车）预测宽框。所以使用多个框的原因是能够预测具有不同纵横比的框。

(2) predict: bounding box=7 * 7 * 2 = 98



[blog 参考](https://zhuanlan.zhihu.com/p/32525231)
[代码参考-1](https://github.com/gliese581gg/YOLO_tensorflow)
[代码参考-2](https://github.com/hizhangp/yolo_tensorflow)
[代码参考-3](https://github.com/TD-4/yolov1)
[代码参考-4](https://github.com/abeardear/pytorch-YOLO-v1)
