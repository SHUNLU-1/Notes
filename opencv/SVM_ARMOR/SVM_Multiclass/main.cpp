#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/cvconfig.h>
#include <stdio.h>
#include <sys/io.h>  //查找文件相关函数库(主要是一些缓冲区相关读写文件的库)
#include <time.h>

using namespace std;
using namespace cv;
using namespace ml;

//其余装甲有
//工程&基地为负样本

int main()
{
//	Mat src = imread("/home/cheng/code/SVM/SVM_ARMOR/1/3/3_00002.jpg");
//	resize(src, src, Size(48, 48));
//	medianBlur(src, src, 3);
//	cvtColor(src, src, COLOR_BGR2GRAY);
//	cv::threshold(src, src, 3, 255, THRESH_BINARY);
//	cv::equalizeHist(src, src);
//	resize(src,src,Size(256,256));
//	imshow("DemoImage",src);
    ifstream hero;
    ifstream engineeringTwo;
    ifstream infantryThree;
    ifstream infantryFour;
    ifstream infantryFive;

  	ifstream Negative;  ///<负样本  -- 基地
    ifstream testFile;  ///<测试
    ifstream errorFile;

    ///<正常机器人
    // 1
    hero.open("/home/cheng/code/SVM/SVM_ARMOR/1/1.txt");
    // 2
    engineeringTwo.open("/home/cheng/code/SVM/SVM_ARMOR/1/2.txt");
    // 3
    infantryThree.open("/home/cheng/code/SVM/SVM_ARMOR/1/3.txt");
    // 4
    infantryFour.open("/home/cheng/code/SVM/SVM_ARMOR/1/4.txt");
    // 5
    infantryFive.open("/home/cheng/code/SVM/SVM_ARMOR/1/5.txt");
    //负样本
    Negative.open("/home/cheng/code/SVM/SVM_ARMOR/1/neg.txt");
    //测试数据
    testFile.open("/home/cheng/code/SVM/SVM_ARMOR/1/text.txt");

    if (!hero)
    {
        cout << "hero imglist reading failed..." << endl;
    }
    if (!engineeringTwo)
    {
        cout << "engineeringTwo imglist reading failed..." << endl;
    }
    if (!infantryThree)
    {
        cout << "infantryThree imglist reading failed..." << endl;
    }
    if (!infantryFour)
    {
        cout << "infantryFour imglist reading failed..." << endl;
    }
    if (!infantryFive)
    {
        cout << "infantryFive imglist reading failed..." << endl;
    }
    ///< neg & test
    if (!Negative)
    {
        cout << "Negative imglist reading failed..." << endl;
    }
    if (!testFile)
    {
        cout << "Test imglist reading failed..." << endl;
    }

    //存储样本
    string          filename;
    vector<cv::Mat> hero_samples;
    vector<cv::Mat> engineering_samples;
    vector<cv::Mat> infantryThree_samples;
    vector<cv::Mat> infantryFour_samples;
    vector<cv::Mat> infantryFive_samples;
    //基地
    vector<cv::Mat> Negative_samples;
    //测试数据集
    vector<cv::Mat> Test_samples;

    /************************************************************************************/
    std::cout << "---开始获取图像---" << endl;
    while (getline(testFile, filename))
    {
        Mat src = imread(filename);
        resize(src, src, Size(48, 48));
        medianBlur(src, src, 3);
        cvtColor(src, src, COLOR_BGR2GRAY);
        cv::threshold(src, src, 3, 255, THRESH_BINARY);
        cv::equalizeHist(src, src);
        Test_samples.push_back(src);
    }
    while (getline(engineeringTwo, filename))
    {
        Mat src = imread(filename);
        resize(src, src, Size(48, 48));
        medianBlur(src, src, 3);
        cvtColor(src, src, COLOR_BGR2GRAY);
        cv::threshold(src, src, 3, 255, THRESH_BINARY);
        cv::equalizeHist(src, src);
        engineering_samples.push_back(src);
    }

    while (getline(hero, filename))
    {
        Mat src = imread(filename);
        resize(src, src, Size(48, 48));
        medianBlur(src, src, 3);
        cvtColor(src, src, COLOR_BGR2GRAY);
        cv::threshold(src, src, 3, 255, THRESH_BINARY);
        cv::equalizeHist(src, src);
        hero_samples.push_back(src);
    }
    //负样本 --基地
    while (getline(Negative, filename))
    {
        Mat src = imread(filename);
        resize(src, src, Size(48, 48));
        medianBlur(src, src, 3);
        cvtColor(src, src, COLOR_BGR2GRAY);
        cv::threshold(src, src, 3, 255, THRESH_BINARY);
        cv::equalizeHist(src, src);
        Negative_samples.push_back(src);
    }
    //步兵三号机器人
    while (getline(infantryThree, filename))
    {
        Mat src = imread(filename);
        resize(src, src, Size(48, 48));
        medianBlur(src, src, 3);
        cvtColor(src, src, COLOR_BGR2GRAY);
        cv::threshold(src, src, 3, 255, THRESH_BINARY);
        cv::equalizeHist(src, src);
        infantryThree_samples.push_back(src);
    }
    //步兵四号机器人
    while (getline(infantryFour, filename))
    {
        Mat src = imread(filename);
        resize(src, src, Size(48, 48));
        medianBlur(src, src, 3);
        cvtColor(src, src, COLOR_BGR2GRAY);
        cv::threshold(src, src, 3, 255, THRESH_BINARY);
        cv::equalizeHist(src, src);
        infantryFour_samples.push_back(src);
    }
    //步兵五号机器人
    while (getline(infantryFive, filename))
    {
        Mat src = imread(filename);
        resize(src, src, Size(48, 48));
        medianBlur(src, src, 3);
        cvtColor(src, src, COLOR_BGR2GRAY);
        cv::threshold(src, src, 3, 255, THRESH_BINARY);
        cv::equalizeHist(src, src);
        infantryFive_samples.push_back(src);
    }
    cout << "获取图像成功" << endl;

    /************************************************************************************/
    cout<<"---开始获取HOG特征---"<<endl;
    cv::HOGDescriptor  hogDesc(cv::Size(48, 48), cv::Size(8, 8), cv::Size(4, 4), cv::Size(4, 4), 9);
    std::vector<float> descriptors;
    hogDesc.compute(hero_samples[0], descriptors);

    std::cout << "sample size:" << hero_samples[0].rows << "x" << hero_samples[0].cols << std::endl;
    std::cout << "HOG descriptor size:" << descriptors.size() << std::endl;

    int featureSize = descriptors.size();

    int numberOfSamples = hero_samples.size() + engineering_samples.size() + infantryThree_samples.size() + infantryFour_samples.size() + infantryFive_samples.size() + Negative_samples.size();

    cv::Mat samples(numberOfSamples, featureSize, CV_32FC1);

    for (int i = 0; i < featureSize; i++)
        samples.ptr<float>(0)[i] = descriptors[i];

    //英雄
    int count_sample_1 = 0;
    for (int j = 0; j < hero_samples.size(); j++)
    {
        hogDesc.compute(hero_samples[j], descriptors);
        for (int i = 0; i < featureSize; i++)
        {
            samples.ptr<float>(j)[i] = descriptors[i];
        }
    }
    count_sample_1 = hero_samples.size();  // 0~1

    //工程
    for (int j = 0; j < engineering_samples.size(); j++)
    {
        hogDesc.compute(engineering_samples[j], descriptors);
        for (int i = 0; i < featureSize; i++)
        {
            samples.ptr<float>(j + count_sample_1)[i] = descriptors[i];
        }
    }
    int count_sample_2 = 0;
    count_sample_2     = count_sample_1 + engineering_samples.size();

    //三号步兵
    for (int j = 0; j < infantryThree_samples.size(); j++)
    {
        hogDesc.compute(infantryThree_samples[j], descriptors);
        for (int i = 0; i < featureSize; i++)
        {
            samples.ptr<float>(j + count_sample_2)[i] = descriptors[i];
        }
    }
    int count_sample_3 = 0;
    count_sample_3     = count_sample_2 + infantryThree_samples.size();

    //四号步兵
    for (int j = 0; j < infantryFour_samples.size(); j++)
    {
        hogDesc.compute(infantryFour_samples[j], descriptors);
        for (int i = 0; i < featureSize; i++)
        {
            samples.ptr<float>(j + count_sample_3)[i] = descriptors[i];
        }
    }
    int count_sample_4 = 0;
    count_sample_4     = count_sample_3 + infantryFour_samples.size();

    //五号步兵
    for (int j = 0; j < infantryFive_samples.size(); j++)
    {
        hogDesc.compute(infantryFive_samples[j], descriptors);
        for (int i = 0; i < featureSize; i++)
        {
            samples.ptr<float>(j + count_sample_4)[i] = descriptors[i];
        }
    }
    int count_sample_5 = 0;
    count_sample_5     = count_sample_4 + infantryFive_samples.size();

    //基地-负样本
    std::cout << "Start acquiring negative sample image features..." << endl;
    for (int j = 0; j < Negative_samples.size(); j++)
    {
        hogDesc.compute(Negative_samples[j], descriptors);
        for (int i = 0; i < featureSize; i++)
        {
            samples.ptr<float>(j + count_sample_5)[i] = descriptors[i];
        }
    }
    cout << "----获取图像特征完毕----" << endl;
    /************************************************************************************/
    cout<<"---开始设置标签---"<<endl;
    /**
     * @brief 设置标签、标签和图片采集相对应
     */
    cv::Mat labels(numberOfSamples, 1, CV_32S);
    labels.rowRange(0, hero_samples.size())          = 1.0;   ///<英雄
    labels.rowRange(count_sample_1, count_sample_2)  = 2.0;   ///<工程
    labels.rowRange(count_sample_2, count_sample_3)  = 3.0;   ///<步兵三号
    labels.rowRange(count_sample_3, count_sample_4)  = 4.0;   ///<步兵四号
    labels.rowRange(count_sample_4, count_sample_5)  = 5.0;   ///<步兵五号
    labels.rowRange(count_sample_5, numberOfSamples) = -1.0;  ///<负样本

    std::cout << "Start training the SVM classifier" << std::endl;
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    cout<<"---设置标签完毕---"<<endl;
    /************************************************************************************/
    cout<<"----开始训练----"<<endl;

    /**
     * @brief 设置SVM参数、SVM训练核之类的
     */
    svm->setDegree(0);  //适用与多项式核函数
    svm->setCoef0(0);   // POLY/ SIGMOID）的参数coef0
    svm->setGamma(1);   //内核函数（POLY/ RBF/ SIGMOID）的参数
    //--设置为1适用与高斯函数
    /**
     * @brief 以下为不同svm训练类型相关参数定义声明** *
     */
    svm->setNu(0);
    svm->setP(0);
    svm->setType(SVM::C_SVC);  ///< SVC用于分类
    svm->setC(1);              ///<权重

    svm->setKernel(SVM::LINEAR);  ///<利用核函数为线性内核，训练最快。

    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 1000, 1e-10));
    Ptr<TrainData> trainingData = TrainData::create(samples, ROW_SAMPLE, labels);
    svm->train(trainingData, ml::ROW_SAMPLE);

    svm->save("/home/cheng/code/SVM/XML/SVM_HOG_MNIST_MAIN02.xml");
    std::cout << "----训练完毕----" << std::endl;
    /************************************************************************************/
    cout<<"----开始测试----"<<endl;
    cv::Mat            queries(1, featureSize, CV_32FC1);
    std::vector<float> descriptors1;
    Mat                testimage = imread("/home/cheng/code/SVM/SVM_ARMOR/1/text/0_0.jpg", cv::IMREAD_GRAYSCALE);
    hogDesc.compute(testimage, descriptors1);
    int featureSize1 = descriptors1.size();
    for (int i = 0; i < Test_samples.size(); i++)
    {
        Mat temp = Test_samples[i];

        hogDesc.compute(temp, descriptors1);
        for (int i = 0; i < featureSize1; i++)
            queries.ptr<float>(0)[i] = descriptors1[i];

        cv::Mat predictions;

        svm->predict(queries, predictions);

        std::cout << "装甲种类是：" << predictions.at<float>(0) << std::endl;
    }
	waitKey(0);
}
