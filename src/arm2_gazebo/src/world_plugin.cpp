#include <iostream>
#include <string>
#include <functional>
#include <memory>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>

namespace gazebo {
    class WorldPluginTutorial : public ModelPlugin {
    private:
        physics::ModelPtr model;
        physics::Joint_V jointList;
        sdf::ElementPtr sdf;
        event::ConnectionPtr updateConnection;

        int jointsCount = 0;

        ros::NodeHandle n;
        ros::Publisher chatter_pub;
        sensor_msgs::JointState jointMsg;

        void CreateRosTopic() {
            if (!ros::isInitialized()) {
                int argc = 0;
                char **argv = nullptr;
                ros::init(argc, argv, "world_plugin_node", ros::init_options::NoSigintHandler);
            }
            this->chatter_pub = n.advertise<sensor_msgs::JointState>("/angle_publisher_topic", 10, false);

            this->jointMsg = sensor_msgs::JointState();

            this->jointsCount = this->jointList.size();

            this->jointMsg.position.resize(this->jointsCount);

            for (auto const &j : jointList) {
                this->jointMsg.name.push_back(j->GetName());
            }
        }

    public:
        void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) {
            this->model = _parent;
            this->sdf = _sdf;
            jointList = model->GetJoints();

            //this created configuration related to ros and topic
            CreateRosTopic();

            this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&WorldPluginTutorial::OnUpdate, this));

        }
        void OnUpdate() {
            for (int i = 0; i < jointsCount; i++) {
                this->jointMsg.position[i] = jointList[i]->Position(i ? 0 : 2);
                // this->jointMsg.position[i] = jointList[i]->GetAngle(i ? 0 : 2)->Degree();
            }
            jointMsg.header.stamp = ros::Time::now();
            this->chatter_pub.publish(this->jointMsg);

        }
    };

    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(WorldPluginTutorial)
}
