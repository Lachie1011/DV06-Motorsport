// Libraries and modules included:m
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

// Namespaces: 
using namespace cv;
using namespace std;

// A counter
int cntr = 0; 

// Image call back method; 
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
  	
  	// Getting the image: 
  	Mat image =  cv_bridge::toCvShare(msg, "bgr8")->image;

  	// Path: 
  	std::string path = "/home/lachie1011/yolov5/data/images" + std::to_string(++cntr) + ".jpg";

  	// Viewing the image: 
    cv::imshow("view", image);

    // Saving the image to a folder: 
    cv::imwrite(path ,image); 

    // Waiting 10 seconds: 
    cv::waitKey(10);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }

  ROS_INFO("I recieved an image");

}


// Main method: 
int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("view");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub = it.subscribe("fsds/camera/cam1", 1, imageCallback);
  ros::spin();
  cv::destroyWindow("view");
}

