#include "ros/ros.h"
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include "arm2_gazebo/setangles.h"
#include <iostream>
using namespace std;
namespace gazebo
{

    class SetAnglesServerPlugin : public ModelPlugin {

        public:
            SetAnglesServerPlugin(){

            }

            void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {
                printf("Service intialized---------------\n");

                if (_model->GetJointCount() == 0) {
                    std::cerr << "Invalid joint count\n";
                    return;
                }


                this->model = _model;
                this->jointController = this->model->GetJointController();
                this->jointList = _model->GetJoints();

                // Setup a PID, with a proportion = 0.1, i=0.1, d=0.2.
                this->pid = common::PID(0.1, 0.1, 0.2);

                // Apply the P-controller to the joint.
                for (auto const &joint : jointList) {
                    jointController->SetPositionPID(joint->GetScopedName(), this->pid);
                }

                int argc = 0;
                char **argv = nullptr;
                ros::init(argc, argv, "angle_listner_node");
                ros::NodeHandle n;

                
                this->pub = n.advertise<arm2_gazebo::setangles>("angle_listner_topic", 1000);
                this->sub = n.subscribe("angle_listner_topic", 1000, &SetAnglesServerPlugin::set_angles_here,this);

                printf("Subscriber intialized-2--------------\n");
            }

            void set_angles_here(const arm2_gazebo::setangles::ConstPtr& msg)
            {
                printf("message received");
                printf("angle1: ");
                cout << msg->angle1 << endl;
                double angles[4];
                angles[0] = msg->angle1;
                angles[1] = msg->angle2;
                angles[2] = msg->angle3;
                angles[3] = msg->angle4;
                int index = 0;
                for (auto joint : jointList) {
                    float rad = M_PI * angles[index++] / 180;
                    // SetJointAngle(joint->GetScopedName(), rad);
                    jointController->SetPositionTarget(joint->GetScopedName(), rad);
                }
                // res.result = "angles have been set!";        
            }

        private:
            ros::Subscriber sub;
            ros::Publisher pub;

            physics::ModelPtr model;
            physics::JointControllerPtr jointController;
            physics::Joint_V jointList;
            common::PID pid;
            // transport::NodePtr node;
            // transport::SubscriberPtr sub; //change
    };

    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(SetAnglesServerPlugin)
    
}