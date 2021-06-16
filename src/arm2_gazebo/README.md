# How to excute this project
Pre-requisite: ros must be installed and roscore must be running

# Steps For question 3
1. cd arm2_ws
2. catkin_make
3. source ./devel/setup.bash
4. roslaunch arm2_gazebo hello.launch
5. Open a new tab
4. On the new tab: rostopic list
5. On the new tab: rostopic echo /angle_publisher_topic #this will print the angles continously....


# Steps For question 4
1. cd arm2_ws
2. catkin_make
3. source ./devel/setup.bash
4. roslaunch arm2_gazebo hello.launch
5. Open a new tab
4. On the new tab: rostopic list
5. rostopic pub -1 /angle_listner_topic arm2_gazebo/setangles tab:: #enter tab to get the mesage on the terminal

# Steps For question Assignment 2
1. cd arm2_ws
2. catkin_make
3. source ./devel/setup.bash
4. rosrun arm2_gazebo ik.py 0 -2.7 0.3
5. rosrun arm2_gazebo ik.py 0 0 3.7 #to go back to the start position
