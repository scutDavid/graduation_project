cmake_minimum_required(VERSION 2.8.3)
project(sec)


set( CMAKE_CXX_FLAGS "-std=c++11" )
# set(OpenCV_DIR /usr/local/share/OpenCV)
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation sensor_msgs cv_bridge image_transport)
find_package(OpenCV 3 REQUIRED )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES first_pkg
  CATKIN_DEPENDS roscpp rospy std_msgs
 CATKIN_DEPENDS message_runtime 
)


include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(sec src/sec.cpp)
target_link_libraries(sec ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_executable(open_video src/open_video.cpp)
target_link_libraries(open_video ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_executable(SVM_test src/SVM_test.cpp)
target_link_libraries(SVM_test ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
