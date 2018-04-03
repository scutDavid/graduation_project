#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/ml.hpp"

//using namespace cv;
//using namespace cv::ml;

int main(int argc, char** argv)
{
    // visual representation
    int width = 512;
    int height = 512;
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);

    // training data
    int labels[4] = { 1, -1, -1, -1 };
    float trainingData[4][2] = { { 501, 10 }, { 255, 10 }, { 501, 255 }, { 10, 501 } };
    cv::Mat trainingDataMat(4, 2, CV_32FC1, trainingData);
    cv::Mat labelsMat(4, 1, CV_32SC1, labels);

    // initial SVM
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::Types::C_SVC);
    svm->setKernel(cv::ml::SVM::KernelTypes::LINEAR);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));

    // train operation
    svm->train(trainingDataMat, cv::ml::SampleTypes::ROW_SAMPLE, labelsMat);

    // prediction
    cv::Vec3b green(0, 255, 0);
    cv::Vec3b blue(255, 0, 0);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            cv::Mat sampleMat = (cv::Mat_<float>(1, 2) << j, i);
            float respose = svm->predict(sampleMat);
            if (respose == 1)
                image.at<cv::Vec3b>(i, j) = green;
            else if (respose == -1)
                image.at<cv::Vec3b>(i, j) = blue;
        }
    }

    int thickness = -1;
    int lineType = cv::LineTypes::LINE_8;

    cv::circle(image, cv::Point(501, 10), 5, cv::Scalar(0, 0, 0), thickness, lineType);
    cv::circle(image, cv::Point(255, 10), 5, cv::Scalar(255, 255, 255), thickness, lineType);
    cv::circle(image, cv::Point(501, 255), 5, cv::Scalar(255, 255, 255), thickness, lineType);
    cv::circle(image, cv::Point(10, 501), 5, cv::Scalar(255, 255, 255), thickness, lineType);

    thickness = 2;
    lineType = cv::LineTypes::LINE_8;

    cv::Mat sv = svm->getSupportVectors();
    for (int i = 0; i < sv.rows; i++)
    {
        const float* v = sv.ptr<float>(i);
        cv::circle(image, cv::Point((int)v[0], (int)v[1]), 6, cv::Scalar(128, 128, 128), thickness, lineType);
    }


    cv::imshow("SVM Simple Example", image);


    cv::waitKey(0);
    return 0;
}
