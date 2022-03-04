#include "yolo.h"

YOLO::YOLO(Net_config config)
{
	cout << "Net use " << config.netname << endl;
	this->confThreshold = config.confThreshold;
	this->nmsThreshold = config.nmsThreshold;
	this->inpWidth = config.inpWidth;
	this->inpHeight = config.inpHeight;
	strcpy(this->netname, config.netname.c_str());
	// ofstream         //文件写操作 内存写入存储设备
	// ifstream         //文件读操作，存储设备读区到内存中
	// fstream          //读写操作，对打开的文件可进行读写操作
	ifstream ifs(config.classesFile.c_str());
	string line;
	/// 从输入流读入的字符串存放在这个字符串中
	while (getline(ifs, line))
		this->classes.push_back(line);
	/// 读取darknet网络模型(cfg,model)
	this->net = readNetFromDarknet(config.modelConfiguration, config.modelWeights);
	// cpu
	// this->net.setPreferableBackend(DNN_BACKEND_OPENCV);
	// this->net.setPreferableTarget(DNN_TARGET_CPU);
	// gpu
	this->net.setPreferableBackend(DNN_BACKEND_CUDA);
	this->net.setPreferableTarget(DNN_TARGET_CUDA);
	// this->net.setPreferableTarget(DNN_TARGET_CUDA_FP16);
}
/// 使用非极大值抑制去除低置信度的边界框
void YOLO::postprocess(Mat &frame, const vector<Mat> &outs) // Remove the bounding boxes with low confidence using non-maxima suppression
{
	vector<int> classIds;
	vector<float> confidences;
	vector<Rect> boxes;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		// 扫描网络输出的所有边界框，只保留
		// 具有高置信度分数的那些。 将框的类标签指定为框得分最高的类。
		// Scan through all the bounding boxes output from the network and keep only the
		// ones with high confidence scores. Assign the box's class label as the class
		// with the highest score for the box.
		float *data = (float *)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			/// Get the value and location of the maximum score
			/// minMaxLoc(src, minVal, maxVal, minLoc, maxLoc, mask)
			/// 在一个数组中找到全局最小值和全局最大值
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			if (confidence > this->confThreshold)
			{
				int centerX = (int)(data[0] * frame.cols);
				int centerY = (int)(data[1] * frame.rows);
				int width = (int)(data[2] * frame.cols);
				int height = (int)(data[3] * frame.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(Rect(left, top, width, height));
			}
		}
	}

	// Perform non maximum suppression to eliminate redundant overlapping boxes with
	// lower confidences
	// 执行非最大抑制以消除冗余重叠框
	// 降低置信度
	vector<int> indices;
	NMSBoxes(boxes, confidences, this->confThreshold, this->nmsThreshold, indices);
	for (size_t i = 0; i < indices.size(); ++i)
	{
		int idx = indices[i];
		Rect box = boxes[idx];
		this->drawPred(classIds[idx], confidences[idx], box.x, box.y,
					   box.x + box.width, box.y + box.height, frame);
	}
}

void YOLO::drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat &frame) // Draw the predicted bounding box
{
	//Draw a rectangle displaying the bounding box
	rectangle(frame, Point(left, top), Point(right, bottom), Scalar(0, 0, 255), 3);

	//Get the label for the class name and its confidence
	string label = format("%.2f", conf);
	if (!this->classes.empty())
	{
		/// CV_Assert计算表达式是否真假
		CV_Assert(classId < (int)this->classes.size());
		label = this->classes[classId] + ":" + label;
	}

	//Display the label at the top of the bounding box
	int baseLine;
	Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
	top = max(top, labelSize.height);
	//rectangle(frame, Point(left, top - int(1.5 * labelSize.height)), Point(left + int(1.5 * labelSize.width), top + baseLine), Scalar(0, 255, 0), FILLED);
	putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 255, 0), 1);
}

void YOLO::detect(Mat &frame)
{
	float start = getTickCount();

	Mat blob;
	///  1.减均值（Mean subtraction）
	///  2.按比例缩放（Scaling by some factor）
	///  函数返回的blob是我们输入图像进行随意从中心裁剪，减均值、缩放和通道交换的结果
	dnn::blobFromImage(frame, blob, 1 / 255.0, Size(this->inpWidth, this->inpHeight), Scalar(0, 0, 0), true, false);
	///  output(n,c,h,w) = scalefactor × (blob(n,c,h,w) - mean_c)
	this->net.setInput(blob);

	vector<Mat> outs;

	this->net.forward(outs, this->net.getUnconnectedOutLayersNames());
	this->postprocess(frame, outs);
	float end = getTickCount();
	vector<double> layersTimes;
	double freq = getTickFrequency() / 1000;
	double t = net.getPerfProfile(layersTimes) / freq;
	string label = format("%s Inference time : %.2f ms", this->netname, t);
	putText(frame, label, Point(0, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
	//imwrite(format("%s_out.jpg", this->netname), frame);

	double costtime = (end - start) / getTickFrequency();
	std::cout << "costtime---net=" << costtime << endl;
}

int main()
{
	//	int count = cuda::getCudaEnabledDeviceCount();
	//	printf("GPU Device Count : %d \n", count);

    YOLO yolo_model(yolo_nets[1]);
	VideoCapture capture;
	Mat frame;

    frame = capture.open("/home/ubuntu/vscode/yolov34-cpp-opencv-dnn/1.avi");
    if (!capture.isOpened())
    {
        printf("can not open ...\n");
        return -1;
    }
    while (capture.read(frame))
    {

         cv::resize(frame, frame, Size(640, 480));
        float start = getTickCount();
        // cv::cuda::GpuMat d_result1, d_img1, d_img2;

        // d_img1.upload(frame);

        yolo_model.detect(frame);
        float end = getTickCount();

        static const string kWinName = "Deep learning object detection in OpenCV";
        namedWindow(kWinName, WINDOW_NORMAL);
        imshow(kWinName, frame);
        waitKey(1);
//		double costtime = (end - start) / getTickFrequency();
//		std::cout << "costtime=" << costtime << endl;
    }
    capture.release();

//     float start = getTickCount();

//     string imgpath = "/home/ubuntu/vscode/yolov34-cpp-opencv-dnn/2.jpg";
//     Mat srcimg = imread("/home/ubuntu/vscode/yolov34-cpp-opencv-dnn/9.jpg");
//     cv::resize(srcimg, srcimg, Size(600, 600));
//     yolo_model.detect(srcimg);

//     static const string kWinName = "Deep learning object detection in OpenCV";
//     namedWindow(kWinName, WINDOW_NORMAL);
//     imshow(kWinName, srcimg);

//     float end = getTickCount();

//     waitKey(0);
//     destroyAllWindows();
//     double costtime = (end - start) / getTickFrequency();
//     std::cout << "costtime=" << costtime << endl;
	return 0;
}
