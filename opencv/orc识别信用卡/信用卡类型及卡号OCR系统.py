# 信用卡类型及卡号OCR系统
# USAGE
# python ocr_template_match.py --reference images/ocr_a_reference.png --image images/credit_card_05.png

import argparse

import cv2
import imutils
import numpy as np

# 导入必要的包
from imutils import contours

# 构建命令行参数及解析
# --image 必须 要进行OCR的输入图像
# --reference 必须 参考OCR-A图像
# ap = argparse.ArgumentParser()
# ap.add_argument("-i", "--image", required=True, help="path to input image")
# ap.add_argument("-r", "--reference", required=True, help="path to reference OCR-A image")
# args = vars(ap.parse_args())


# 定义一个字典（映射信用卡第一位数字和信用卡类型的编号）
FIRST_NUMBER = {
    "3": "American Express",
    "4": "Visa",
    "5": "MasterCard",
    "6": "Discover Card",
}

# 从磁盘加载参考OCR-A图像，转换为灰度图，阈值化图像以显示为白色前景和黑色背景
# 并反转图像
# and invert it, such that the digits appear as *white* on a *black*
# ref_origin = cv2.imread(args["reference"])
ref_origin = cv2.imread("3.png")
cv2.imshow("ref_origin", ref_origin)
ref = ref_origin.copy()
ref = cv2.cvtColor(ref, cv2.COLOR_BGR2GRAY) 
cv2.imshow("ref_gray", ref)
ref = cv2.threshold(ref, 155, 255, cv2.THRESH_BINARY)[1]
cv2.imshow("ref_threshhold", ref)
cv2.waitKey(0)

# 寻找OCR-A图像中的轮廓（数字的外轮廓线）
# 并从左到右排序轮廓，初始化一个字典来存储数字ROI
refCnts = cv2.findContours(ref.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
print("findContours: ", len(refCnts))
refCnts = imutils.grab_contours(refCnts)
refCnts = contours.sort_contours(refCnts, method="left-to-right")[0]
digits = {}

# 遍历OCR-A轮廓
for (i, c) in enumerate(refCnts):
    # 计算数字的边界框，提取它，缩放到固定的大小
    (x, y, w, h) = cv2.boundingRect(c)
    cv2.rectangle(ref_origin, (x, y), (x + w, y + h), (0, 255, 0), 2)
    roi = ref[y : y + h, x : x + w]
    roi = cv2.resize(roi, (57, 88))

    # 更新数字字典，数字匹配ROI
    digits[i] = roi
cv2.imshow("ref and digits", ref_origin)
cv2.waitKey(0)

# 初始化矩形和方形结构内核
# 在图像上滑动它来进行（卷积）操作，如模糊、锐化、边缘检测或其他图像处理操作。
# 使用矩形函数作为Top-hat形态学运算符，使用方形函数作为闭合运算。
rectKernel = cv2.getStructuringElement(cv2.MORPH_RECT, (9, 3))
sqKernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))

# 准备进行OCR的输入图像
# 加载输入图像，保持纵横比缩放图像宽度为300，转换为灰度图
# origin = cv2.imread(args["image"])
origin = cv2.imread("3.png")

origin = imutils.resize(origin, width=300)
image = origin.copy()
cv2.imshow("origin", origin)
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
cv2.imshow("gray", gray)

# 执行形态学操作
# 应用tophat（白帽）形态学操作以在暗的背景中提取出亮的区域（信用卡上的数字卡号）
# Top hat操作在深色背景（即信用卡号）下显示浅色区域
tophat = cv2.morphologyEx(gray, cv2.MORPH_TOPHAT, rectKernel)
cv2.imshow("tophat", tophat)

# 计算Scharr梯度，计算梯度值
# 在白色礼帽上，计算x方向的Scharr梯度，然后缩放到范围[0, 255]
gradX = cv2.Sobel(tophat, ddepth=cv2.CV_32F, dx=1, dy=0, ksize=-1)
gradX = np.absolute(gradX)
(minVal, maxVal) = (np.min(gradX), np.max(gradX))
# 最小/最大归一化, 由float转换gradX到uint8范围[0-255]
gradX = 255 * ((gradX - minVal) / (maxVal - minVal))
gradX = gradX.astype("uint8")
cv2.imshow("gradient", gradX)

# 使用矩形框应用闭合操作以帮助闭合信用卡数字之间的小的缝隙
# 应用Otsu's阈值方法二值化图像
gradX = cv2.morphologyEx(gradX, cv2.MORPH_CLOSE, rectKernel)
cv2.imshow("morphologyEx", gradX)
thresh = cv2.threshold(gradX, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
cv2.imshow("thresh1", thresh)

# 在二值化图像上，应用二次闭合操作
# 再一次方形框形态学操作，帮助闭合信用卡数字区域之间的缝隙
thresh = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, sqKernel)
cv2.imshow("thresh2", thresh)
# 阈值图像中查找轮廓，然后初始化数字位置列表
cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
cnts = imutils.grab_contours(cnts)
locs = []

# 遍历轮廓
for (i, c) in enumerate(cnts):
    # 计算轮廓的边界框，并计算纵横比
    (x, y, w, h) = cv2.boundingRect(c)
    ar = w / float(h)

    # 由于信用卡有固定的4组4数字，可以根据纵横比来寻找潜在的轮廓
    if ar > 2.5 and ar < 4.0:
        # 轮廓可以在最小/最大宽度上进一步修剪
        if (w > 40 and w < 55) and (h > 10 and h < 20):
            # 添加数字组轮廓的编辑框轮廓到位置list
            locs.append((x, y, w, h))
            cv2.rectangle(origin, (x, y), (x + w, y + h), (255, 0, 0), -1)

cv2.imshow("contours filter", origin)
# 突出显示信用卡上四组四位数字（总共十六位）。
# 从左到右排序轮廓，并初始化list来存储信用卡数字列表
locs = sorted(locs, key=lambda x: x[0])
output = []

# 遍历四组四位数字
for (i, (gX, gY, gW, gH)) in enumerate(locs):
    # 初始化存放每组数字的list
    groupOutput = []

    # 提取每组4位数字的灰度图ROI
    # 应用阈值方法从背景信用卡中分割数字
    group = gray[gY - 5 : gY + gH + 5, gX - 5 : gX + gW + 5]
    group = cv2.threshold(group, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]

    # 检测组中每个单独数字的轮廓
    # 从左到右排序轮廓
    digitCnts = cv2.findContours(
        group.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
    )
    digitCnts = imutils.grab_contours(digitCnts)
    digitCnts = contours.sort_contours(digitCnts, method="left-to-right")[0]

    # 遍历数字轮廓
    for c in digitCnts:
        # 计算每个单独数字的边界框
        # 提取数字，缩放以拥有和参考OCR-A字体模板图像相同的大小
        (x, y, w, h) = cv2.boundingRect(c)
        roi = group[y : y + h, x : x + w]
        roi = cv2.resize(roi, (57, 88))

        # 初始化模板匹配分数list
        scores = []

        # 遍历参考数字名和数字ROI
        for (digit, digitROI) in digits.items():
            # 应用基于相关性的模板匹配，计算分数，更新分数list
            # apply correlation-based template matching, take the
            # score, and update the scores list
            result = cv2.matchTemplate(roi, digitROI, cv2.TM_CCOEFF)
            (_, score, _, _) = cv2.minMaxLoc(result)
            scores.append(score)

        # 数字ROI的分类将取 模板匹配分数中分数最大的参考数字
        # the classification for the digit ROI will be the reference
        # digit name with the *largest* template matching score
        groupOutput.append(str(np.argmax(scores)))

    # 围绕每组画一个矩形，并以红色文本标识图像上的信用卡号
    # 绘制每组的数字识别分类结果
    cv2.rectangle(image, (gX - 5, gY - 5), (gX + gW + 5, gY + gH + 5), (0, 0, 255), 2)
    cv2.putText(
        image,
        "".join(groupOutput),
        (gX, gY - 15),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.65,
        (0, 0, 255),
        2,
    )

    # 更新输出数字分组列表
    # Pythonic的方法是使用extend函数，它将iterable对象的每个元素（本例中为列表）追加到列表的末尾
    output.extend(groupOutput)
cv2.waitKey(0)
# 显示检测到的信用卡类型和卡号到屏幕上
print("Credit Card Type: {}".format(FIRST_NUMBER[output[0]]))
print("Credit Card #: {}".format("".join(output)))
cv2.imshow("Image", image)

