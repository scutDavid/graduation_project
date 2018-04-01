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

int main()
{
    VideoCapture c("/home/wwh/视频/2.mp4");//(int)c.get(CV_CAP_PROP_FOURCC)
    
    if(!c.isOpened())
    {
       printf("open failed\n") ;
    }
    int frame_start=22;
    c.set( CV_CAP_PROP_POS_FRAMES,frame_start);
    int frameHeight  =c.get(CV_CAP_PROP_FRAME_HEIGHT);//帧高度  
    int frameWidth   =c.get(CV_CAP_PROP_FRAME_WIDTH);//帧宽度  
    int fps          =c.get(CV_CAP_PROP_FPS);//帧率  
    int numFrames    =c.get(CV_CAP_PROP_FRAME_COUNT);//帧数  
    int frame_end=numFrames;
    double rate=c.get(CV_CAP_PROP_FPS);
    bool stop=false;
    clock_t start ,end ;
    Mat frame,ROI;
    int delay=1000/rate;
    int currentFrame=frame_start;
    Point center;
    printf("height:%d width:%d frame_count:%d  fps:%d\n",frameHeight,frameWidth,numFrames,fps);
    
    VideoWriter writer("VideoTest.avi", CV_FOURCC('M','J','P','G'), fps, Size(208, 360));
    
    while(currentFrame<frame_end)
    {
        vector<Rect> found;
        HOGDescriptor defaultHOG;
//         c.read(frame);
        start=clock();
        c>>frame;
//         frame=frame.t();
//         cvtColor(frame, frame, COLOR_BGR2GRAY);
        start=clock();
        ROI=frame(Range(0,frame.rows),Range(50,160));
        Point srt1=Point(50,0);
        Point end1=Point(50,frame.rows);
        Point srt2=Point(150,0);
        Point end2=Point(150,frame.rows);
        defaultHOG.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
        defaultHOG.detectMultiScale(ROI,found,0,Size(24, 24),Size(32, 32),1.05,2,0);
        for (int i=0;i<found.size();i++)
        {
            Rect r=found[i];
            rectangle(ROI,r.tl(),r.br(),Scalar(0,0,255),3);
            center.x=r.x;
            center.y=r.y;
            circle(ROI,center,8,Scalar(0,255,0));
            printf("%d\tposition:%d %d \n",i,r.x,r.y);
        }
        end=clock();
        double duration =(double)(end-start)/CLOCKS_PER_SEC;
        printf("%f\n",duration);
        cv::line(frame, srt1, end1, cv::Scalar(0, 255, 255),3);
        cv::line(frame, srt2, end2, cv::Scalar(0, 255, 255),3);
        writer<<frame;
        imshow("Extracted frame",frame);
        if (waitKey(delay)==27)
        {
            cout << "按下ESC键" << endl;
            break;
        }
//         int key=waitKey(delay);
//         if((char)key==27||currentFrame>frame_end)
//         {
//             stop=true;
//         }
//         if(key>=0)
//         {
//             waitKey(0);
//         }
        currentFrame++;
            
    }
    printf("currentframe:%dplay done\n",currentFrame);
    c.release();
    waitKey(0);
    return 0;
}
