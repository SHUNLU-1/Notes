#include <stdio.h>
#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/cvconfig.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <sys/io.h>                     //查找文件相关函数库(主要是一些缓冲区相关读写文件的库)
#include <fstream>

using namespace std;
using namespace cv;
using namespace ml;

int main()
{

    ifstream infile_positive;
    ifstream infile_negative;
    ifstream infile_test;

   infile_positive.open("/home/ubuntu/code/SVM_ARMOR/pictures/1.txt");
   infile_negative.open("/home/ubuntu/code/SVM_ARMOR/pictures/2.txt");
   infile_test.open("/home/ubuntu/code/SVM_ARMOR/pictures/3.txt");

    if (!infile_positive)
        {
            cout << "Positive imglist reading failed..." << endl;
        }
    if (!infile_negative)
        {
            cout << "Negative imglist reading failed..." << endl;
        }
    if (!infile_test)
        {
            cout << "Test imglist reading failed..." << endl;
        }

    string filename;
    vector<cv::Mat>positivesamples;
    vector<cv::Mat>negativesamples;
    vector<cv::Mat>testsamples;

    std::cout << "Start capturing pictures..." << endl;

/****
* **获取文件夹中的图片并将其放入到数组中** *
****/
    while (getline(infile_positive,filename))
    {
         Mat src = imread(filename);
         resize(src,src,Size(48,48));
         positivesamples.push_back(src);
    }

    ////***展示训练集中单张图片（可更改）***
//  Mat imageshow=positivesamples[2];
//  resize(imageshow,imageshow,Size(300,300));
//  imshow(" positivesamples", imageshow);
//  waitKey(0);

    while (getline(infile_negative,filename))
    {
         Mat src = imread(filename);
         resize(src,src,Size(48,48));
         negativesamples.push_back(src);
    }

    while (getline(infile_test,filename))
    {
         Mat src = imread(filename);
         resize(src,src,Size(48,48));
         testsamples.push_back(src);
    }

/***
 * **获取图片特征** *
 ***/
    std::cout << "Start capturing positive sample image features..." << endl;

    cv::HOGDescriptor hogDesc(cv::Size(48, 48), cv::Size(16, 16), cv::Size(8, 8), cv::Size(8, 8), 9);

//    cv::HOGDescriptor hogDesc(cv::Size(48,48),cv::Size(8,8),cv::Size(4,4),cv::Size(4,4),9);
    std::vector<float> descriptors;
    hogDesc.compute(positivesamples[0],descriptors);

    std::cout <<"Positive sample size:"<<positivesamples[0].rows<<"x"<<positivesamples[0].cols<<std::endl;
    std::cout <<"HOG descriptor size:"<<descriptors.size()<<std::endl;

    int featureSize =descriptors.size();
    int numberOfSamples=positivesamples.size()+negativesamples.size();

    cv::Mat samples(numberOfSamples,featureSize,CV_32FC1);

    for(int i=0;i<featureSize;i++)
        samples.ptr<float>(0)[i]=descriptors[i];

    for(int j=0;j<positivesamples.size();j++)
    {
        hogDesc.compute(positivesamples[j],descriptors);
        for(int i=0;i<featureSize;i++)
        {samples.ptr<float>(j)[i]=descriptors[i];}
    }

    std::cout << "Start acquiring negative sample image features..." << endl;

    for(int j=0;j<negativesamples.size();j++)
    {
        hogDesc.compute(negativesamples[j],descriptors);
        for(int i=0;i<featureSize;i++)
        samples.ptr<float>(j+positivesamples.size())[i]=descriptors[i];
    }

/***
 * **设置标签（采用的是将标签与图片相对应的方法）** *
 * **也可采用特征与标签相对应的方法（可自行更改）** *
 ***/
    cv::Mat labels(numberOfSamples,1,CV_32S);
    labels.rowRange(0,positivesamples.size())=1.0;
    labels.rowRange(positivesamples.size(),numberOfSamples)=-1.0;


    std::cout << "Start training the SVM classifier" << std::endl;
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();

/****
 * **以下为不同内核函数相关参数定义声明（可作一次性声明）也可不作声明也即使用默认值** *
 * **采用不同的内核函数所生成的文件大小也不同** *
****/
    svm->setDegree(0);    //内核函数（POLY）的参数degree
    svm->setCoef0(0);     //POLY/ SIGMOID）的参数coef0
    svm->setGamma(0);     //内核函数（POLY/ RBF/ SIGMOID）的参数

/****
 * **以下为不同svm训练类型相关参数定义声明** *
****/
    svm->setNu(0);
    svm->setP(0);
    svm->setType(SVM::C_SVC); //选取C类支撑向量分类机（n类分组 （n≥2））
    svm->setC(1);             //权重

    svm->setKernel(SVM::LINEAR); //利用核函数为线性内核，训练最快。
//  svm->setKernel(cv::ml::SVM::RBF); //利用高斯核函数,较慢但准确性高

    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 1000, 1e-6));
    Ptr<TrainData>trainingData = TrainData::create(samples, ROW_SAMPLE,labels);
    svm->train(trainingData,ml::ROW_SAMPLE);

    svm->save("/home/ubuntu/code/SVM_ARMOR/svm.xml");
    std::cout << "Complete the training" << std::endl;

    //测试
    std::cout << "Star test" << std::endl;

    cv::Mat queries(1, featureSize, CV_32FC1);

////测试单张图片
//    Mat testimage=imread("/home/nuc/SVM_Pictures/negative/1_19.jpg",cv::IMREAD_GRAYSCALE);
//    resize(testimage,testimage,cv::Size(48, 48));
//    hogDesc.compute(testimage, descriptors);
//    for (int i = 0; i < featureSize; i++)
//        queries.ptr<float>(0)[i] = descriptors[i];

//    cv::Mat predictions;

//    // Test the classifier with the last two pos and neg samples
//    svm->predict(queries, predictions);

//    std::cout << "query: " << ": " << ((predictions.at<float>(0) < 0.0) ? "Negative" : "Positive") << std::endl;

    ////测试图片集
    std::vector<float> descriptors1;
//    Mat testimage=imread("/home/ubuntu/code/Training1/negative_samples/1_19.jpg",cv::IMREAD_GRAYSCALE);
//    hogDesc.compute(testimage,descriptors1);
//    for (int i = 0; i < testsamples.size(); i++)
//        {
//            Mat temp = testsamples[i];
//            hogDesc.compute(temp, descriptors1);

//            int featureSize1=descriptors1.size();
//            for (int i = 0; i < featureSize1; i++)
//                 queries.ptr<float>(0)[i] = descriptors1[i];

//            cv::Mat predictions;

//            svm->predict(queries, predictions);

//            std::cout << "query: " <<i<< ": " << ((predictions.at<float>(0) < 0.0) ? "Negative" : "Positive") << std::endl;
//        }
}
