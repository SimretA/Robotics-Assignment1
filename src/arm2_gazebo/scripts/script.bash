#!/bin/bash
sleep 4
source ./devel/setup.bash
rosrun arm2_gazebo ik.py 0 -2.5 0.1 G
rosrun arm2_gazebo ik.py 0 -2.5 0.1 C
rosrun arm2_gazebo ik.py 0 -2.5 0.1 R
rosrun arm2_gazebo ik.py 0 -2.5 0.1 G 