#include <ros/ros.h>
#include <iostream>
#include <cv_bridge/cv_bridge.h>
#include<image_transport/image_transport.h>
#include <stdio.h>
#include<opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <time.h> 
using namespace std;
using namespace cv;
// 打开一张图并显示
int main(int argc, char *argv[])
{
    clock_t start ,end ;
    ros::init(argc,argv,"image_pub");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub=it.advertise("camera/image",1);
    printf("begin\n");
//     cv::Mat image = imread("/home/wwh/kdev_ros/src/sec/src/1.png", CV_LOAD_IMAGE_COLOR );
//     cv::Mat templateImage = imread("/home/wwh/kdev_ros/src/sec/src/template.png", CV_LOAD_IMAGE_COLOR);
//     cv::Point center=cv::Point2f(templateImage.rows/2,templateImage.cols/2);
//     Mat rotate_model = getRotationMatrix2D(center,(double) 30, (double)1);  
//     Mat img_rotate;  
//     warpAffine(templateImage, img_rotate, rotate_model, Size(templateImage.rows, templateImage.cols));
//     
//     cv::imshow("rotate",img_rotate);
/*    
    int result_cols =  image.cols - templateImage.cols + 1;
    int result_rows = image.rows - templateImage.rows + 1;

    cv::Mat result = cv::Mat( result_cols, result_rows, CV_32FC1 ); //匹配结果图像, 类型 32F, 大小 (W-w+1)-(H-h+1) 
    start=clock();
    cv::matchTemplate(image, templateImage, result, CV_TM_SQDIFF_NORMED);//这里注意匹配结果图像与原图像之间的大小关系，他们之间差了一个模板大小

    double minVal=0, maxVal=0;
    cv::Point minLoc, maxLoc, matchLoc;
    cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    matchLoc = minLoc;
    end=clock();
    double duration =(double)(end-start)/CLOCKS_PER_SEC;
    printf("%f\n",duration);
    printf("%d %d\n",matchLoc.x,matchLoc.y);*/
    
//     int result_cols =  image.cols - img_rotate.cols + 1;
//     int result_rows = image.rows - img_rotate.rows + 1;
// 
//     cv::Mat result = cv::Mat( result_cols, result_rows, CV_32FC1 ); //匹配结果图像, 类型 32F, 大小 (W-w+1)-(H-h+1) 
//     start=clock();
//     cv::matchTemplate(image, img_rotate, result, CV_TM_CCOEFF_NORMED);//这里注意匹配结果图像与原图像之间的大小关系，他们之间差了一个模板大小

//     double minVal=0, maxVal=0;
//     cv::Point minLoc, maxLoc, matchLoc;
//     cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
//     matchLoc = maxLoc;
//     end=clock();
//     double duration =(double)(end-start)/CLOCKS_PER_SEC;
//     printf("%f\n",duration);
//     printf("%d %d\n",matchLoc.x,matchLoc.y);
//      
//     cv::rectangle( image, cv::Rect(matchLoc, cv::Size(img_rotate.cols, img_rotate.rows)), Scalar(0, 0, 255), 2, 8, 0 );
//     circle( image,matchLoc,8,Scalar(0,255,0));//on the left top,not the rectangle center
//     imshow("image", image);
//     printf("end\n");
//     waitKey(0) ;
//     return 0;
    
    cv::Mat image = imread("/home/wwh/kdev_ros/src/sec/src/p1.png", CV_LOAD_IMAGE_GRAYSCALE );
//     printf("col:%d\trow:%d",image.cols,image.rows);
    
//     Mat gx,gy;
//     Sobel(image,gx,CV_32F,1,0,1);
//     Sobel(image,gy,CV_32F,0,1,1);
//     imshow("gx",gx);
//     imshow("gy",gy);
    vector<Rect> found;
    HOGDescriptor defaultHOG;
    defaultHOG.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    defaultHOG.detectMultiScale(image,found,0,Size(16, 16),Size(32, 32),1.05,2,0);
    for (int i=0;i<found.size();i++)
    {
        Rect r=found[i];
        rectangle(image,r.tl(),r.br(),Scalar(0,0,255),3);
    }
    cv::imshow("detect",image);


//     sensor_msgs::ImagePtr msg= cv_bridge ::CvImage(std_msgs::Header(),"mono8",image).toImageMsg();
//     ros::Rate r(5);
//     while(nh.ok())
//     {
//         pub.publish(msg);
//         ros::spinOnce();
//         printf("send done\n");
//         r.sleep();
//     }
//     return 0;
    waitKey(0);
    return 0;
}
