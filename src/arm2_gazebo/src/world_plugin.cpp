#include <functional>
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

namespace gazebo
{
class WorldPluginTutorial : public WorldPlugin
{
public:
  // ros::NodeHandle n;
  WorldPluginTutorial() : WorldPlugin()
  {
    // ros::init("","","talker");
    ROS_INFO("Plugin intialized!");
  }

  void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
  {
    // Make sure the ROS node for Gazebo has already been initialized
    if (!ros::isInitialized())
    {
      ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
        << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
      return;
    }

    // ros::Publisher chatter_pub = this->n.advertise<std_msgs::String>("chatter", 1000);
    ROS_INFO("Plugin loaded...");
    // printf("Loaded");
    // this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&WorldPluginTutorial::OnUpdate, this));
    // this->world = _world;
  }

  void OnUpdate(){
    ROS_INFO("Updated");
    printf("Updated");
  }


// private:
//   //pointer to world
//   physics::WorldPtr world;
//   // Pointer to the update event connection
//   event::ConnectionPtr updateConnection;

};
GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)
}