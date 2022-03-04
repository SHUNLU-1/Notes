# yolov5-dnn-cpp-py
yolov5s,yolov5l,yolov5m,yolov5x的onnx文件在百度云盘下载，
链接：https://pan.baidu.com/s/1AvosqSfTfWk1i6c0ggxDAQ?pwd=wsh1 
提取码：wsh1

python版本的主程序是main_yolov5.py，C++版本的主程序是main_yolo.cpp

运行整套程序只需要安装opencv库(4.0以上版本的)，彻底摆脱对深度学习框架的依赖

这4个pth文件是从https://github.com/ultralytics/yolov5  的pth文件里抽取出参数，保存到顺序字典OrderedDict里，最后生成新的pth文件
在convert-onnx文件夹里，我把4种yolov5的网络结构全都定义在.py文件里，这样便于读者直观的了解网络结构以及层与层的连接关系。
下载完成pth文件后，运行convert_onnx.py就可以生成.onnx文件，这个程序需要依赖pytorch1.7.0框架，如果pytorch版本低了，程序运行会报错。
因为在yolov5里有新的激活函数，旧版本pytorch可能不支持的

