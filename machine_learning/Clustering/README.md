# 一、什么是聚类
###  1、聚类的定义
**聚类(Clustering)**  是按照某个特定标准(如距离)把一个数据集分割成不同的类或簇，使得同一个簇内的数据对象的相似性尽可能大，同时不在同一个簇中的数据对象的差异性也尽可能地大。也即聚类后同一类的数据尽可能聚集到一起，不同类数据尽量分离。
###  2、聚类的过程
 > 1. 数据准备：特征标准化和降维
 >2. 特征选择：从最初的特征中选择最有效的特征，并将其存储在向量中
 >3. 特征提取：通过对选择的特征进行转换形成新的突出特征
 >4.  聚类：基于某种距离函数进行相似度度量，获取簇
 >5. 聚类结果评估：分析聚类结果，如距离误差和(SSE)等
###  3、常用的距离度量
![](https://img-blog.csdnimg.cn/52183f9a53d14a69a626e4eac7bca441.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6aG66LevMTI=,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)
# 二、几种常用的聚类算法
###   1、K-means
#####  算法思想
直观了解 **K-means算法** 有许多有趣的例子，其中有一个最著名的解释，即 **牧师—村民模型**：                                               

>有四个牧师去郊区布道，一开始牧师们随意选了几个布道点，并且把这几个布道点的情况公告给了郊区所有的村民，于是每个村民到离自己家最近的布道点去听课。听课之后，大家觉得距离太远了，于是每个牧师统计了一下自己的课上所有的村民的地址，搬到了所有地址的中心地带，并且在海报上更新了自己的布道点的位置。牧师每一次移动不可能离所有人都更近，有的人发现A牧师移动以后自己还不如去B牧师处听课更近，于是每个村民又去了离自己最近的布道点…… 就这样，牧师每个礼拜更新自己的位置，村民根据自己的情况选择布道点，最终稳定了下来。

##### **算法过程：**
![在这里插入图片描述](https://img-blog.csdnimg.cn/eaafed83da5b4357988a191c09d2a690.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6aG66LevMTI=,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)

![](https://img-blog.csdnimg.cn/a8839fe9385044d784c760c1aa3f3d24.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6aG66LevMTI=,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)
公式推倒 详见周志华机器学习
#####  k值选取与调优
K-means 算法具有很多优点，例如：聚类效果良好，局部最优在很多情况能够满足需求；在处理大数据集时，可以保证较好的伸缩性；算法复杂度低；当簇近似高斯分布的时候，效果优良。但是K-Means主要有两个最重大的缺陷——都和初始值有关：

>K 是事先给定的，这个 K 值的选定是非常难以估计的。很多时候，事先并不知道给定的数据集应该分成多少个类别才最合适。
K-Means算法需要用初始随机种子点来计算，这个随机种子点太重要，不同的随机种子点会有得到完全不同的结果。

K 值的选取对 K-means 影响很大，这也是 K-means 最大的缺点，常见的选取 K 值的方法有：手肘法、Gap statistic 方法。
如果我们拿到的样本，客观存在J个“自然小类”，这些真实存在的小类是隐藏于数据中的。三维以下的数据我们还能画图肉眼分辨一下J的大概数目，更高维的就不能直观地看到了，我们只能从一个比较小的K，譬如K=2开始尝试，去逼近这个真实值$J$。

>当K小于样本真实簇数J时，K每增大一个单位，就会大幅增加每个簇的聚合程度，这时距离和的下降幅度会很大；
当K接近J时，再增加K所得到的聚合程度回报会迅速变小，距离和的下降幅度也会减小；
随着K的继续增大，距离和的变化会趋于平缓。
![k值调优](https://img-blog.csdnimg.cn/dae162731fb54e16a40a7f290173a6df.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA6aG66LevMTI=,size_20,color_FFFFFF,t_70,g_se,x_16#pic_center)
