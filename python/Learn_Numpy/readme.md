# 一、数组

## 1.创建数组
### 1.1.np.array() 直接创建：

![](https://pic1.zhimg.com/80/v2-90de7812f9fc3169cffb7e39d4c3cfd8_1440w.jpg)

### 1.2.使用 np.ones()、np.zeros() 等方法：

![](https://pic4.zhimg.com/80/v2-6e73db4bcf9e406d110da4f2827200ab_1440w.jpg)

## 2.数组运算
### 2.1.加减乘除

![](https://pic3.zhimg.com/80/v2-ae2106c929707e5613c6d8b8bb7aab16_1440w.png)

![](https://pic3.zhimg.com/80/v2-651679ca10deeda9810c5a59de52bac6_1440w.jpg)

（注意这里的data和ones不是上面的data，ones）

![](https://pic2.zhimg.com/80/v2-c2b47f98a0c1ae65eedd798bb222758d_1440w.png)

### 2.2.数组乘以数值

![](https://pic4.zhimg.com/80/v2-e461f0c4e4a66622b487b71f22e3eb7b_1440w.png)

## 3.数组索引

![](https://pic1.zhimg.com/80/v2-6ab0797b53e61645a9564376ae9f3d0c_1440w.jpg)

## 4.数组聚合

![](https://pic2.zhimg.com/80/v2-6e8ef73d761be46fdf60aefcf3953821_1440w.jpg)

# 二、矩阵
## 1.创建矩阵
### 1.1.直接创建：

![](https://pic4.zhimg.com/80/v2-58fe9b45561eed23069a721ec516279b_1440w.jpg)

### 1.2.使用 np.ones()、np.zeros() 等方法：

![](https://pic3.zhimg.com/80/v2-63b85180f9ac32626669e0cd662f5d92_1440w.jpg)

## 2.矩阵运算

![](https://pic3.zhimg.com/80/v2-651679ca10deeda9810c5a59de52bac6_1440w.jpg)

![](https://pic2.zhimg.com/80/v2-b1a31f23c0cab9570a3f7b0d2af42031_1440w.jpg)

## 3.矩阵点积
#### 矩阵点积跟线性代数基本一样，有些抽象，借助示意图能很好理解：

![](https://pic1.zhimg.com/80/v2-c3f791e0c27505216111dfe9d3f51c74_1440w.jpg)

#### 进一步拆分解释：

![](https://pic2.zhimg.com/80/v2-ffeacb71407ec517f64294c30a962159_1440w.jpg)

## 4.矩阵索引

![](https://pic3.zhimg.com/80/v2-45f4ce6a4ffd5f8af7ab6c7ba717720e_1440w.jpg)

## 5.矩阵聚合
### 5.1 求最值

![](https://pic2.zhimg.com/80/v2-fa64dda84ef6ac60c277446e5dea8029_1440w.jpg)

### 5.2 按行 / 列聚合

![](https://pic2.zhimg.com/80/v2-e5dbfb6c39c9065351628b8e9f22ba35_1440w.jpg)

## 6.矩阵转置

![](https://pic4.zhimg.com/80/v2-689c92bca6be7d624a473b41fa0fec9b_1440w.jpg)

## 7.矩阵重塑

#### reshape() 用法：

![](https://pic4.zhimg.com/80/v2-676cd66b7083e7507ebec3b69c0b8d3f_1440w.jpg)

## 8.高维数组
#### Numpy 不仅可以处理上述的一维数组和二维矩阵，还可以处理任意 N 维的数组，方法也大同小异。

### 8.1 创建多维数组

![](https://pic4.zhimg.com/80/v2-00e2ef23fefed05864e66318b6c5d107_1440w.jpg)

![](https://pic2.zhimg.com/80/v2-e5bb94c075e23e20e58cea9e2df47cf1_1440w.jpg)

## 9.计算均方误差 MSE：

![](https://pic4.zhimg.com/80/v2-70d84cd6b6975b2757e5e164249b0cdb_1440w.jpg)

### 可以看到有减法、平方、求和等运算：

![](https://pic1.zhimg.com/80/v2-e52fd0fc193ad26494ee9ce35559753c_1440w.jpg)

### 分别假设相应的预测值和真实值：

![](https://pic1.zhimg.com/80/v2-0462ab48e91ca9081cc652fce298de6c_1440w.jpg)

![](https://pic1.zhimg.com/80/v2-fb39528fcfd3447639f203df41949b00_1440w.jpg)

![](https://pic1.zhimg.com/80/v2-a2ed39331e8841397d4908fc2157a46c_1440w.jpg)

![](https://pic1.zhimg.com/80/v2-56048efa2b5f2a10832388b69c050ebc_1440w.jpg)




















