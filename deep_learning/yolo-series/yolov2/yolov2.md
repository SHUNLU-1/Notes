# YOLO V2算法
##  1. 网络结构

为了进一步提升速度，YOLO2提出了Darknet-19（有19个卷积层和5个MaxPooling层）网络结构。DarkNet-19比VGG-16小一些，精度不弱于VGG-16，但浮点运算量减少到约1/5，以保证更快的运算速度。具体结构如下图所示。
由图中可以看出，相比于v1版本的基础网络，DarkNet进行了一下几点改进：
+ 使用了BN层。
+ 添加了passthrough层。
+ 用连续的3×3卷积代替了v1版本中的7×7卷积，这样既减少了计算量，又增加了网络深度，此外，DarkNet去掉了全连接层和Dropout层。
+ 由于YOLOv2在每一个区域预5个边框，每个边框有25个预测值，因此最后输出的特征图通道数为125。其中，一个边框的25个预测值分别是20个类别预测，4个位置预测及1个置信度预测值。这里和v1有很大区别，v1是一个区域内的边框共享类别预测，而这里则是相互独立的类别预测值（即解决YOLOv1中每个cell只能预测一个物体的缺点）。

![](https://img-blog.csdnimg.cn/20210302005123928.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1JvYWRkZA==,size_16,color_FFFFFF,t_70#pic_center)

在上图中可以看到蓝色框中在经过pass through layer之后特征图大小变为13×13×256，为什么和前面提到的passthrough层抽取前面层的每个2×2的局部区域，然后将其转化为channel维度，对于26×26×512的特征图，经passthrough层处理之后就变成了13×13×2048的新特征图不一样呢。因为在前面提到的是作者在论文中写的，而作者给的代码中在pass thought layer之前先将特征图（26×26×512）经过1×1卷积之后变为（26×26×64），再做运算。这样可以很大程度上减少运算量.

## 2. 改进策略

#### 2.1. Batch Normalization（加入BN层）
Batch Normalization有助于解决反向传播过程中的梯度消失和梯度爆炸问题，降低对一些超参数（比如学习率、网络参数的大小范围、激活函数的选择）的敏感性，可以提升模型收敛速度，而且可以起到一定正则化效果，降低模型的过拟合。在YOLOv2中，每个卷积层后面都添加了Batch Normalization层，并且不再使用droput。使用Batch Normalization后。

– YOLOv2的mAP提升了2.4%。

#### 2.2. High Resolution Classifier（使用高分辨率图像微调分类模型）
图像分类的训练样本很多，而标注了边框的用于训练对象检测的样本相比而言就比较少了，因为标注边框的人工成本比较高。所以对象检测模型通常都先用图像分类样本训练卷积层，提取图像特征。但这引出的另一个问题是，图像分类样本的分辨率不是很高。所以YOLO v1使用ImageNet的图像分类样本采用 224*224 作为输入，来训练CNN卷积层。然后在训练对象检测时，检测用的图像样本采用更高分辨率的 448×448 的图像作为输入。但这样切换对模型性能有一定影响。
所以YOLO2在采用 224×224 图像进行分类模型预训练后，再采用 448×448 的高分辨率样本对分类模型进行微调（10个epoch），使网络特征逐渐适应 448×448 的分辨率。然后再使用 448×448 的检测样本进行训练，缓解了分辨率突然切换造成的影响。

– mAP提升了3.7。

#### 2.3. Convolutional With Anchor Boxes（采用先验框）
在YOLOv1中，输入图片最终被划分为7×7网格，每个单元格预测2个边界框。YOLOv1中包含全连接层，从而能直接预测bounding boxes的坐标值，其中边界框的宽与高是相对整张图片大小的。（Faster R-CNN的方法只用卷积层与Region Proposal Network来预测Anchor Box的偏移量与置信度，而不是直接预测坐标值）。由于各个图片中存在不同尺度和长宽比（scales and ratios）的物体，YOLOv1在训练过程中学习适应不同物体的形状是比较困难的，这也导致YOLOv1在精确定位方面表现较差。作者发现通过预测偏移量而不是坐标值能够简化问题，让网络学习起来更容易。
借鉴Faster R-CNN的做法，YOLOv2移除了YOLOv1中的全连接层而采用了卷积核anchor boxes来预测边界框。通过在每个cell预先设定一组不同大小和宽高比的边框，来覆盖整个图像的不同位置和多种尺度。同时为了使检测实用的特征图分辨率更高，去掉了网络中的一个pooling层。并且网络输入图像尺寸变为416×416，而不是原来的448×448。
由于图片中的物体都倾向于出在这里插入图片描述
现在图片的中心位置，特别是那种比较大的物体，所以有一个单独位于物体中心的位置用于预测这些物体。YOLO的卷积层采用32这个值来下采样图像，所以网络输入为416×416，输出为13×13的feature map。使用Anchor Box会让精确度稍微下降，但用了它能使YOLO能预测出13×13×9=1521个框。因此相对于YOLO
v181%的召回率，YOLOv2的召回率大幅度提升到88%。

– mAP下降0.2%，recall大幅度提升到88%。意味着模型有更多的提升空间。

#### 2.4. Dimension Clusters（聚类提取先验框）
在Faster R-CNN和SSD中，先验框的维度（长和宽）都是手动设定的，带有一定的主观性。如果选取的先验框维度比较合适，那么模型更容易学习，从而做出更好的预测。因此，YOLOv2采用k-means聚类方法对训练集中的边界框做了聚类分析，以寻找尽可能匹配样本的边框尺寸。
聚类算法最重要的是选择如何计算两个边框之间的“距离”，对于常用的欧式距离，大边框会产生更大的误差。而且设置先验框的主要目的是为了使得预测框与ground truth的IOU更好，所以聚类分析时选用box与聚类中心box之间的IOU值作为距离指标：
![](https://img-blog.csdnimg.cn/20210301233746867.png#pic_center)
centroid是聚类时被选作中心的边框，box就是其它边框，d就是两者间的“距离”。IOU越大，“距离”越近。YOLO2给出的聚类分析结果如下图所示：
![](https://img-blog.csdnimg.cn/20210301233722170.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1JvYWRkZA==,size_16,color_FFFFFF,t_70#pic_center)
上图左边是选择不同的聚类k值情况下，得到的k个centroid边框，计算样本中标注的边框与各centroid的Avg IOU。显然，边框数k越多，Avg IOU越大。YOLO2选择k=5作为边框数量与IOU的折中。对比手工选择的先验框，使用5个聚类框即可达到61 Avg IOU，相当于9个手工设置的先验框60.9 Avg IOU。
上图右边显示了5种聚类得到的先验框，VOC和COCO数据集略有差异，不过都有较多的瘦高形边框。
#### 2.5. Direct location prediction（约束预测边框的位置）
![](https://img-blog.csdnimg.cn/20210301234958264.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1JvYWRkZA==,size_16,color_FFFFFF,t_70#pic_center)