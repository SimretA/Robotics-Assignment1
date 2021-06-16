#include "ros/ros.h"
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include "arm2_gazebo/setangles.h"
#include "arm2_gazebo/grabalgles.h"
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
                this->pid = common::PID(100,50,50);

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

                //grab or release
                this->catch_object(msg);     
            }
            void catch_object(const arm2_gazebo::setangles::ConstPtr& msg){
                //get joints
                std::string left_finger_left_finger_tip = this->model->GetJoint("left_finger_left_finger_tip")->GetScopedName();
                std::string right_finger_right_finger_tip = this->model->GetJoint("right_finger_right_finger_tip")->GetScopedName();

                this->jointController->SetPositionPID(left_finger_left_finger_tip, common::PID(30.1, 10.01, 10.03));
                this->jointController->SetPositionPID(right_finger_right_finger_tip, common::PID(30.1, 10.01, 10.03));

                //angle value to be changed
                double angle = (msg->finger_finger_tip)*M_PI/180;
                double negative_angle = -1*angle;
                //set joint angles
                
                this->jointController->SetPositionTarget(left_finger_left_finger_tip, angle);
                this->jointController->SetPositionTarget(right_finger_right_finger_tip, negative_angle);


            }

        private:

            ros::Subscriber sub;
            ros::Subscriber sub2;
            ros::Publisher pub;

            physics::ModelPtr model;
            physics::JointControllerPtr jointController;
            physics::Joint_V jointList;
            common::PID pid;
    };

    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(SetAnglesServerPlugin)
    
}