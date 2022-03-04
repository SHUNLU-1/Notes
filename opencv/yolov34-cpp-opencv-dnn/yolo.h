#include <fstream>
#include <sstream>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/cuda.hpp>

using namespace cv;
using namespace dnn;
using namespace std;

struct Net_config
{
	float confThreshold; // Confidence threshold(置信度)
	float nmsThreshold;	 // Non-maximum suppression threshold(非最大抑制阈值)
	int inpWidth;		 // Width of network's input image(网络输入图像的宽度)
	int inpHeight;		 // Height of network's input image(网络输入图像的高度)
	string classesFile;         // 类名
	string modelConfiguration;	// 配置文件cfg
	string modelWeights;		// 模型权重
	string netname;				// 定义网络名	
};
Net_config yolo_nets[4] = {
	{0.5, 0.4, 416, 416, "coco.names", "yolov3/yolov3.cfg", "yolov3/yolov3.weights", "yolov3"},
	{0.5, 0.4, 608, 608, "yolo-fastest/download/coco.names", "/home/ubuntu/vscode/yolov34-cpp-opencv-dnn/yolov4/yolov4_custom_train.cfg", "/home/ubuntu/vscode/yolov34-cpp-opencv-dnn/yolov4/yolov4_7800.weights", "yolov4"},
	{0.5, 0.4, 320, 320, "yolo-fastest/download/coco.names", "yolo-fastest/download/yolov4-tiny.cfg", "yolo-fastest/yolov4-tiny_final.weights", "yolo-fastest"},
	{0.5, 0.4, 320, 320, "coco.names", "yolobile/csdarknet53s-panet-spp.cfg", "yolobile/yolobile.weights", "yolobile"}};
class YOLO
{
public:
	YOLO(Net_config config);
	void detect(Mat &frame);

private:
	float confThreshold;
	float nmsThreshold;
	int inpWidth;
	int inpHeight;
	char netname[20];
	vector<string> classes;
	Net net;
	void postprocess(Mat &frame, const vector<Mat> &outs);
	void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat &frame);
};
