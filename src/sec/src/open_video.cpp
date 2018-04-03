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
    clock_t start1,end1,start2,end2 ;
    Mat frame,ROI;
    int delay=1000/rate;
    int currentFrame=frame_start;
    Point center;
    printf("height:%d width:%d frame_count:%d  fps:%d\n",frameHeight,frameWidth,numFrames,fps);
    
//     VideoWriter writer("VideoTest.avi", CV_FOURCC('M','J','P','G'), fps, Size(208, 360));
    
    while(currentFrame<frame_end)
    {
        vector<Rect> found1, found_filtered1,found2, found_filtered2;
        HOGDescriptor defaultHOG;
        c>>frame;
//         frame=frame.t();
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        ROI=frame(Range(0,frame.rows),Range(50,160));
        Point srt1=Point(50,0);
        Point endP1=Point(50,frame.rows);
        Point srt2=Point(150,0);
        Point endP2=Point(150,frame.rows);
        
        start1=clock();
        defaultHOG.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
        defaultHOG.detectMultiScale(ROI,found1,0,Size(8, 8),Size(0, 0),1.05,2,0);//you need to know what the parameters mean
        end1=clock();
        
//         start2=clock();
//         CascadeClassifier cascade;
//         cascade.load("/home/wwh/opencv-3.4.1/data/hogcascades/hogcascade_pedestrians.xml");
//         cascade.detectMultiScale(ROI,found2,1.1, 3, 0, Size(8,8), Size(64,64));
//         end2=clock();
        
        for(int i=0; i < found1.size(); i++)  
        {  
            Rect r = found1[i];  
            int j=0;  
            for(; j < found1.size(); j++)  
                if(j != i && (r & found1[j]) == r)  
                    break;  
            if( j == found1.size())  
                found_filtered1.push_back(r);  
        }  
        for(int i=0; i<found_filtered1.size(); i++)  
        {  
            Rect r = found_filtered1[i];  
            r.x += cvRound(r.width*0.1);  
            r.width = cvRound(r.width*0.8);  
            r.y += cvRound(r.height*0.07);  
            r.height = cvRound(r.height*0.8);  
            rectangle(ROI, r.tl(), r.br(), Scalar(0,0,255), 3); 
            printf("%d\tposition_hog:%d %d \n",i,r.x,r.y);
        } 
        /*for(int i=0; i < found2.size(); i++)  
        {  
            Rect r = found2[i];  
            int j=0;  
            for(; j < found2.size(); j++)  
                if(j != i && (r & found2[j]) == r)  
                    break;  
            if( j == found2.size())  
                found_filtered2.push_back(r);  
        }  
 
        for(int i=0; i<found_filtered2.size(); i++)  
        {  
            Rect r = found_filtered2[i];  
            r.x += cvRound(r.width*0.1);  
            r.width = cvRound(r.width*0.8);  
            r.y += cvRound(r.height*0.07);  
            r.height = cvRound(r.height*0.8);  
            rectangle(ROI, r.tl(), r.br(), Scalar(0,255,0), 3);
            printf("%d\tposition_cas:%d %d \n",i,r.x,r.y);
        }*/  

        /*
         * (8,8) (8,8)   0.1s; excellent
         * (8,8) (4,4)   0.05s excellent
         * (8,8) (0,0)   0.03s excellent
         * (8,8) (16,16) 0.047s excellent
         */
        /*
         for (int i=0;i<found.size();i++)
        {
            Rect r=found[i];
            rectangle(ROI,r.tl(),r.br(),Scalar(0,0,255),3);
            center.x=r.x;
            center.y=r.y;
            circle(ROI,center,8,Scalar(0,255,0));
            printf("%d\tposition:%d %d \n",i,r.x,r.y);
        }*/
//         for (int i=0;i<found.size();i++)
//         {
//             Rect r=found[i];
//             int j=0;
//             for(;j<found.size();j++)
//             {
//                 if(j!=i&&(r&found[j])==r)
//                     break;
//             }
//             if(j==found.size()){
//                 foundrect.push_back(r);
//             }
//             
//         }
//         for(int i=0;i<foundrect.size();i++){
//             Rect r=foundrect[i];
//             rectangle(frame,r.tl(),r.br(),Scalar(0,0,255),3);
//             center.x=r.x;
//             center.y=r.y;
//             circle(frame,center,8,Scalar(0,255,0));
//             printf("%d\tposition:%d %d \n",i,r.x,r.y);
//         }
//         end=clock();
        double duration1 =(double)(end1-start1)/CLOCKS_PER_SEC;
        double duration2 =(double)(end2-start2)/CLOCKS_PER_SEC;
        printf("hog:%f cas :%f\n",duration1,duration2);
        cv::line(frame, srt1, endP1, cv::Scalar(0, 255, 255),3);
        cv::line(frame, srt2, endP2, cv::Scalar(0, 255, 255),3);
//         writer<<frame;
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
