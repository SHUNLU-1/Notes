#include "include.h"



/**
 * @brief 识别数字
 * @param [in] KeyPoints 标识四个点
 * @param [in] Inputimg 原始图像
 */
int calFighur(Mat Inputimg)
{
    Mat dst_perspective;
    // 对进行分析的图像进行处理、显化数字特征
    resize(Inputimg, Inputimg, Size(48, 48));

    cv::cvtColor(Inputimg, dst_perspective, COLOR_BGR2GRAY);
    cv::threshold(dst_perspective, dst_perspective, 0, 255, /*THRESH_BINARY | */ THRESH_OTSU);
    cv::equalizeHist(dst_perspective, dst_perspective);
    cv::imshow("dst_perspective", dst_perspective);
    std::vector<float> descriptors;
    _hog.compute(dst_perspective, descriptors, cv::Size(8, 8));
    int DescriptorDim    = descriptors.size();
    Mat sampleFeatureMat = cv::Mat::zeros(1, DescriptorDim, CV_32FC1);
    for (int i = 0; i < DescriptorDim; i++)
    {
        sampleFeatureMat.at<float>(0, i) = descriptors[i];
    }
    return int(_svm->predict(sampleFeatureMat));
}

int dnn_1()
{

    String   modelConfiguration = "yolo.cfg";
    String   modelBinary        = "yolo.weights";
    dnn::Net net                = readNetFromDarknet(modelConfiguration, modelBinary);

    if (net.empty())
    {
        printf("Could not load net...\n");
        return -1;
    }

    // 类别信息
    vector<string> classNamesVec;
    ifstream       classNamesFile("coco.names");
    if (classNamesFile.is_open())
    {
        string className = "";
        while (std::getline(classNamesFile, className))
            classNamesVec.push_back(className);
    }

    // 加载图像
    Mat frame     = imread("2.jpg");
    Mat inputBlob = blobFromImage(frame, 1 / 255.F, Size(416, 416), Scalar(), true, false);
    net.setInput(inputBlob, "data");

    // 检测
    Mat            detectionMat = net.forward("detection_out");
    vector<double> layersTimings;
    double         freq = getTickFrequency() / 1000;
    double         time = net.getPerfProfile(layersTimings) / freq;
    ostringstream  ss;
    ss << "detection time: " << time << " ms";
    putText(frame, ss.str(), Point(20, 20), 0, 0.5, Scalar(0, 0, 255));

    // 输出结果
    float confidenceThreshold = 0.2;
    for (int i = 0; i < detectionMat.rows; i++)
    {
        const int probability_index = 5;
        const int probability_size  = detectionMat.cols - probability_index;
        float*    prob_array_ptr    = &detectionMat.at<float>(i, probability_index);
        size_t    objectClass       = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
        float     confidence        = detectionMat.at<float>(i, ( int )objectClass + probability_index);
        cout << " confidence : " << confidence << endl;
        if (confidence > confidenceThreshold)
        {
            float x           = detectionMat.at<float>(i, 0);
            float y           = detectionMat.at<float>(i, 1);
            float width       = detectionMat.at<float>(i, 2);
            float height      = detectionMat.at<float>(i, 3);
            int   xLeftBottom = static_cast<int>((x - width / 2) * frame.cols);
            int   yLeftBottom = static_cast<int>((y - height / 2) * frame.rows);
            int   xRightTop   = static_cast<int>((x + width / 2) * frame.cols);
            int   yRightTop   = static_cast<int>((y + height / 2) * frame.rows);
            Rect  object(xLeftBottom, yLeftBottom, xRightTop - xLeftBottom, yRightTop - yLeftBottom);
            rectangle(frame, object, Scalar(0, 0, 255), 2, 8);
            if (objectClass < classNamesVec.size())
            {
                ss.str("");
                ss << confidence;
                String conf(ss.str());
                String label     = String(classNamesVec[objectClass]) + ": " + conf;
                int    baseLine  = 0;
                Size   labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                //                rectangle(frame, Rect(Point(xLeftBottom, yLeftBottom), Size(labelSize.width, labelSize.height + baseLine)), Scalar(255, 255, 255), CV_FILLED);
                putText(frame, label, Point(xLeftBottom, yLeftBottom + labelSize.height), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
            }
        }
    }
    imshow("YOLO-Detections", frame);
    waitKey(0);

    return 0;
}
