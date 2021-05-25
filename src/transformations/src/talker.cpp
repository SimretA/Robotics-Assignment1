#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include "transformations/position.h"
#include "transformations/output.h"

double degreeToRad(int64_t degree){
  double pi = 3.14159265359;
  return (degree * (pi / 180));
}

float temp_x=0, temp_y=0, temp_z = 0;
void chatterCallback(const transformations::position::ConstPtr& msg){

  float  x, y, z;
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


}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");


  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("input", 1000, chatterCallback);

  ros::Publisher chatter_pub = n.advertise<transformations::output>("chatter", 1000);

  ros::Rate loop_rate(10);


  int count = 0;
  while (ros::ok())
  {

    transformations::output output;
    output.x = temp_x;
    output.y = temp_y;
    output.z = temp_z;


    // ROS_INFO();


    chatter_pub.publish(output);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}

