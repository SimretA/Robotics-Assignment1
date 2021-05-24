#include "ros/ros.h"
#include "std_msgs/String.h"
#include "transformations/position.h"
#include <math.h>
#include <cmath>


double degreeToRad(int64_t degree){
  double pi = 3.14159265359;
  return (degree * (pi / 180));
}

void chatterCallback(const transformations::position::ConstPtr& msg)
{
  float temp_x, temp_y, temp_z, x, y, z;
  temp_x = msg->v[0];
  temp_y = msg->v[1];
  temp_z = msg->v[2];


  //rotate in x
  y = temp_y;
  z = temp_z;
  temp_y = (y * cos(msg->alpha[0])) - (z * sin(msg->alpha[0]));
  temp_z = (y * sin(msg->alpha[0])) + (z * cos(msg->alpha[0]));


  //rotate in y
  x = temp_x;
  z = temp_z;
  temp_x = (x * cos(msg->alpha[1])) + (z * sin(msg->alpha[1]));
  temp_z = (z * cos(msg->alpha[1])) - (x * sin(msg->alpha[1]));

  //rotate in z
  x = temp_x;
  y = temp_y;
  temp_x = (y * sin(msg->alpha[2])) - (x * cos(msg->alpha[2]));
  temp_y = (y * cos(msg->alpha[2])) + (x * sin(msg->alpha[2]));

  //translate d in x
  temp_x += msg->d;

  ROS_INFO("New vector: [%.2f, %.2f, %.2f]", temp_x, temp_y, temp_z);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");

  ros::NodeHandle n;


  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);


  ros::spin();

  return 0;
}