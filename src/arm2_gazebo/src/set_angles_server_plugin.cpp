#include "ros/ros.h"
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include "arm2_gazebo/set_angles.h"

namespace gazebo
{

    class SetAnglesServerPlugin : public ModelPlugin {

        public:
            SetAnglesServerPlugin(){

            }

            void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {
                // Safety check
                printf("Service intialized---------------\n");

                if (_model->GetJointCount() == 0) {
                    std::cerr << "Invalid joint count\n";
                    return;
                }

                // Store the model pointer for convenience.
                this->model = _model;
                this->jointController = this->model->GetJointController();
                this->jointList = _model->GetJoints();

                // Setup a P-controller, with a gain of 0.1.
                this->pid = common::PID(0.1, 0.01, 0.02);

                // Apply the P-controller to the joint.
                for (auto const &joint : jointList) {
                    jointController->SetPositionPID(joint->GetScopedName(), this->pid);
                }

                // if (!ros::isInitialized()) {
                //     int argc = 0;
                //     char **argv = nullptr;
                //     ros::init(argc, argv, "add_two_ints_server");
                // }

                int argc = 0;
                char **argv = nullptr;
                ros::init(argc, argv, "add_two_ints_server");
                ros::NodeHandle n;

                printf("Service intialized-2--------------\n");

                ros::ServiceServer service = n.advertiseService("/set_angles",&SetAnglesServerPlugin::set_angles_here,this);

                printf("Service intialized-3--------------\n");
                // // Create the node
                // this->node = transport::NodePtr(new transport::Node());

                // this->node->Init(this->model->GetWorld()->Name());

                // // Create a topic name
                // std::string topicName = "~/" + this->model->GetName() + "/angle_cmd";
                // // Subscribe to the topic, and register a callback
                // this->sub = this->node->Subscribe(topicName, &JointSubscriberPlugin::OnMsg, this);
            }

            bool set_angles_here(arm2_gazebo::set_angles::Request  &req, arm2_gazebo::set_angles::Response &res)
            {
                double angles[4];
                angles[0] = req.angle1;
                angles[1] = req.angle2;
                angles[2] = req.angle3;
                angles[3] = req.angle4;
                int index = 0;
                for (auto joint : jointList) {
                    float rad = M_PI * angles[index++] / 180;
                    // SetJointAngle(joint->GetScopedName(), rad);
                    jointController->SetPositionTarget(joint->GetScopedName(), rad);
                }
                // res.result = "angles have been set!";
                return true;         
            }

        private:
            physics::ModelPtr model;
            physics::JointControllerPtr jointController;
            physics::Joint_V jointList;
            common::PID pid;
            transport::NodePtr node;
            transport::SubscriberPtr sub; //change
    };

    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(SetAnglesServerPlugin)
    
}