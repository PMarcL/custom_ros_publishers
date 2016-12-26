# custom_ros_publishers

This repository contains custom ROS publishers made for an introduction to robotics course at Laval university. Our publishers reads data available here : [www.mrpt.org](http://www.mrpt.org/MalagaUrbanDataset)

## Setup ##

You need to have ROS installed in order to compile this project. We used ROS indigo, but it should work with other distributions. Here's the instructions to setup this package in a catkin workspace:

    mkdir catkin_ws
    cd catkin_ws
    git clone https://github.com/PMarcL/custom_ros_publishers.git
    mv custom_ros_publishers src
    catkin_make
    source devel/setup.bash

## Recording data ##
To record the data broadcasted by our publishers and generate a .bag file, you need to run the following commands in multiple terminals:
#### Terminal 1:
    
    roscore

#### Terminal 2:

    rosbag record -a -x "/rosout(.*)"
    
#### Terminal 3:

    ./generate_data_file.sh
    
You'll need to modify the paths in the Shell script so that they correspond to the location of your data files. Once the publishers are done publishing data, you can stop rosbag in terminal 2 with ctrl+c. The .bag file will be saved in the working directory of terminal 2.
    
## References ##

Here's a list of references and tutorial used to make this project:

* The official ROS website: [www.ros.org/](http://www.ros.org/)
* Basic tutorial on the ROS wiki: [wiki.ros.org/fr/ROS/Tutorials](http://wiki.ros.org/fr/ROS/Tutorials)
