#include "ros/ros.h"
#include<iostream>
#include<stdlib.h>
int main(int argc,char** argv)
{
  ros::init(argc, argv, "test");
  ros::NodeHandle n;
  ros::Rate loop_rate(1);
  
  while(ros::ok()){
    printf("ok\n");
  ros::spinOnce();
  loop_rate.sleep();
  }
  
 }