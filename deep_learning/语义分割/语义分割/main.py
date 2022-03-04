import os
from tensorbay import GAS
from tensorbay.dataset import Data, Dataset
from tensorbay.label import InstanceMask, SemanticMask
from PIL import Image
import numpy as np
import torchvision
import matplotlib.pyplot as plt

ACCESS_KEY = "Accesskey-738bd662e2e9bb10df99591815278c7c"
gas = GAS(ACCESS_KEY)


def read_voc_images(is_train=True, index=0):
    """
    read voc image using tensorbay
    """
    dataset = Dataset("VOC2012Segmentation", gas)
    if is_train:
        segment = dataset["train"]
    else:
        segment = dataset["test"]
    """打开数据的图片和数据"""
    data = segment[index]
    feature = Image.open(data.open()).convert("RGB")
    label = Image.open(data.label.semantic_mask.open()).convert("RGB")
    """显示（plt）"""
    # visualize(feature, label)
    """ PIL Image"""
    return feature, label  


def visualize(feature, label):
    """
    visualize feature and label
    """
    fig = plt.figure() 
    """ 第一个子图"""
    ax = fig.add_subplot(121) 
    ax.imshow(feature)
    """ 第二个子图"""
    ax2 = fig.add_subplot(122)  
    ax2.imshow(label)
    plt.show()


train_feature, train_label = read_voc_images(is_train=True, index=20)
train_label = np.array(train_label)  #  (375, 500, 3)

""" 
颜色映射表
在得到彩色语义标签图后，则可以构建一个颜色表映射，列出标签中每个RGB颜色的值及其标注的类别
"""
def colormap_voc():
    """
    create a colormap
    """
    colormap = [[0, 0, 0], [128, 0, 0], [0, 128, 0], [128, 128, 0],
                    [0, 0, 128], [128, 0, 128], [0, 128, 128], [128, 128, 128],
                    [64, 0, 0], [192, 0, 0], [64, 128, 0], [192, 128, 0],
                    [64, 0, 128], [192, 0, 128], [64, 128, 128], [192, 128, 128],
                    [0, 64, 0], [128, 64, 0], [0, 192, 0], [128, 192, 0],
                    [0, 64, 128]]

    classes = ['background', 'aeroplane', 'bicycle', 'bird', 'boat',
                   'bottle', 'bus', 'car', 'cat', 'chair', 'cow',
                   'diningtable', 'dog', 'horse', 'motorbike', 'person',
                   'potted plant', 'sheep', 'sofa', 'train', 'tv/monitor']

    return colormap, classes
"""
Label与Onehot转换
根据映射表，实现语义标签图与Onehot编码的相互转换:
"""
def label_to_onehot(label, colormap):
    """
    Converts a segmentation label (H, W, C) to (H, W, K) where the last dim is a one
    hot encoding vector, C is usually 1 or 3, and K is the number of class.
    """
    semantic_map = []
    for colour in colormap:
        """
        np.equal():
        输入两个形状相同的数组（或两个数），逐个比较数组中元素是否相等，返回布尔值数组（或一个布尔值）。
        若输入为一个数和一个数组，则将数组中每个元素与这个数进行比较，返回布尔值数组
        """
        equality = np.equal(label, colour)
        class_map = np.all(equality, axis=-1)
        semantic_map.append(class_map)
    semantic_map = np.stack(semantic_map, axis=-1).astype(np.float32)
    return semantic_map


def onehot_to_label(semantic_map, colormap):
    """
    Converts a mask (H, W, K) to (H, W, C)
    """
    x = np.argmax(semantic_map, axis=-1)
    colour_codes = np.array(colormap)
    label = np.uint8(colour_codes[x.astype(np.uint8)])
    return label


colormap, classes = colormap_voc()
"""mask_to_onehot"""
semantic_map = label_to_onehot(train_label, colormap)  
"""[H, W, K] = [375, 500, 21] 包括背景共21个类别"""
print(semantic_map.shape)  

label = onehot_to_label(semantic_map, colormap)
print(label.shape) # [H, W, K] = [375, 500, 3]

"""
Onehot与Mask转换
同样，借助映射表，实现单通道掩膜Mask与Onehot编码的相互转换
"""
def onehot2mask(semantic_map):
    """
    Converts a mask (K, H, W) to (H,W)
    """
    _mask = np.argmax(semantic_map, axis=0).astype(np.uint8)
    return _mask


def mask2onehot(mask, num_classes):
    """
    Converts a segmentation mask (H,W) to (K,H,W) where the last dim is a one
    hot encoding vector

    """
    semantic_map = [mask == i for i in range(num_classes)]
    return np.array(semantic_map).astype(np.uint8)


mask = onehot2mask(semantic_map.transpose(2, 0, 1))
"""[ 0  1 15] 索引相对应的是背景、飞机、人"""
print(np.unique(mask)) 
"""(375, 500)"""
print(mask.shape) 

semantic_map = mask2onehot(mask, len(colormap))
"""(21, 375, 500)"""
print(semantic_map.shape) 
