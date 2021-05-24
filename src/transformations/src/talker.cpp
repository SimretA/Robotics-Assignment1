#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>
#include "transformations/position.h"

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");


  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 3);

  ros::Rate loop_rate(10);


  int count = 0;
  while (ros::ok())
  {

    transformations::position msg;

    // std::stringstream ss;
    // ss << "yoo " << count;
    // msg.data = ss.str();

    ROS_INFO("%.2f", msg.d);


    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}

