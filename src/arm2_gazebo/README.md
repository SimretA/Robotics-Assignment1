# How to excute this project
Pre-requisite: ros must be installed and roscore must be running

#### Question 1 is plotting the arm which can be seen by opening the .sdf file

## Steps For question 3
1. cd arm2_ws
2. catkin_make
3. source ./devel/setup.bash
4. roslaunch arm2_gazebo hello.launch
5. Open a new tab
4. On the new tab: rostopic list
5. On the new tab: rostopic echo /angle_publisher_topic #this will print the angles continously....


## Steps For question 4
1. cd arm2_ws
2. catkin_make
3. source ./devel/setup.bash
4. roslaunch arm2_gazebo hello.launch
5. Open a new tab
4. On the new tab: rostopic list
5. rostopic pub -1 /angle_listner_topic arm2_gazebo/setangles tab:: #enter tab to get the mesage on the terminal

# Steps For Assignment 2 Part 1: Forward kinematics
1. cd arm2_ws
2. catkin_make
3. source ./devel/setup.bash
4. roslaunch arm2_gazebo hello.launch
5. sudo chmod +x ./src/arm2_gazebo/scripts/fk.py
6. rosrun arm2_gazebo fk.py #run the service
7. sudo chmod +x ./src/arm2_gazebo/scripts/fk_client.py
8. rosrun arm2_gazebo fk_client.py 5 12 0 13 #the desired angles


# Steps For Assignment 2
1. cd arm2_ws
2. catkin_make
3. source ./devel/setup.bash
4. roslaunch arm2_gazebo hello.launch
5. sudo chmod +x ./src/arm2_gazebo/scripts/script.bash
6. sudo ./src/arm2_gazebo/scripts/script.bash
