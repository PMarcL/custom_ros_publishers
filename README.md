# custom_ros_publishers

This repository contains custom ROS publishers made for an introduction to robotics course at Laval university. Our publishers reads data available here : [www.mrpt.org](http://www.mrpt.org/MalagaUrbanDataset)

## Setup ##

You need to have ROS installed in order to compile this project. We used ROS indigo, but it should work with other distributions. Here's the instructions to setup this package in a catkin workspace:

    mkdir -p catkin_ws/src
    cd catkin_ws/src
    git clone https://github.com/PMarcL/custom_ros_publishers.git
    cd ..
    catkin_make

## Recording data ##
To record the data broadcasted by our publishers and generate a .bag file, you need to run the following commands in multiple terminals:
#### Terminal 1:
    
    roscore

#### Terminal 2:

    rosbag -a -x "/rosout(.*)"
    
#### Terminal 3:

    rosrun imu_publisher imu_publisher
    
## References ##

Here's a list of references and tutorial used to make this project:

* The official ROS website: [www.ros.org/](http://www.ros.org/)
* Basic tutorial on the ROS wiki: [wiki.ros.org/fr/ROS/Tutorials](http://wiki.ros.org/fr/ROS/Tutorials)
