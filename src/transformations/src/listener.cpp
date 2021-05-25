#include "ros/ros.h"
#include "std_msgs/String.h"
#include "transformations/output.h"
#include <math.h>
#include <cmath>


void chatterCallback(const transformations::output::ConstPtr& output)
{
  
  ROS_INFO("New vector: [%.2f, %.2f, %.2f]", output->x, output->y, output->z);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");

  ros::NodeHandle n;


  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);


  ros::spin();

  return 0;
}