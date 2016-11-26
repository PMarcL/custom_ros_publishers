#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct IMU_data_frame {
	ros::Time time;
	double x_acc;
	double y_acc;
	double z_acc;
	double yaw_vel;
	double pitch_vel;
	double roll_vel;
	double x_vel;
	double y_vel;
	double z_vel;
	double yaw;
	double pitch;
	double roll;
	double x;
	double y;
	double z;
};

static const char* IMU_DATA_FILE = "./data/malaga-urban-dataset-extract-15_all-sensors_IMU.txt";

void read_imu_data(const char* filename, vector<IMU_data_frame>& data_frames);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "imu_publisher");
  ros::NodeHandle n;
  ros::Publisher imu_publisher = n.advertise<sensor_msgs::Imu>("imu/data_raw", 1000);
  ros::Rate loop_rate(500);

	vector<IMU_data_frame> data_frames = vector<IMU_data_frame>();
	read_imu_data(IMU_DATA_FILE, data_frames);

  unsigned long i = 0;

  while (ros::ok() && i < data_frames.size())
		{
		IMU_data_frame current_frame = data_frames[i];
		sensor_msgs::Imu imu_msg = sensor_msgs::Imu();

		imu_msg.header.stamp = current_frame.time;
		imu_msg.header.frame_id = "imu";
		imu_msg.linear_acceleration.x = current_frame.x_acc;
		imu_msg.linear_acceleration.y = current_frame.y_acc;
		imu_msg.linear_acceleration.z = current_frame.z_acc;
		imu_msg.angular_velocity.x = current_frame.pitch_vel;
		imu_msg.angular_velocity.y = current_frame.roll_vel;
		imu_msg.angular_velocity.z = current_frame.yaw_vel;
		imu_msg.orientation.x = current_frame.pitch;
		imu_msg.orientation.y = current_frame.roll;
		imu_msg.orientation.z = current_frame.yaw;
		imu_msg.orientation.w = 0.0;

    ROS_INFO("send an IMU message");

    imu_publisher.publish(imu_msg);

    ros::spinOnce();
    loop_rate.sleep();
		i++;
  }

	ROS_INFO("Published all data from data file.");
  return 0;
}

ros::Time string_to_ros_time(string& time_str);

void read_imu_data(const char* filename, vector<IMU_data_frame>& data_frames) {
	ROS_INFO("reading file");
	ifstream file(filename, std::ifstream::in);
	string current_line = "";

	// skip first line, contains useless header info
	getline(file, current_line);

	while(getline(file, current_line)) {
		ROS_INFO("reading line");
		// TODO remove this line, only use to debug
		cout << current_line << endl;
		IMU_data_frame current_frame;

		istringstream line_stream(current_line);

		string time_stamp;
		line_stream >> time_stamp;
		current_frame.time = string_to_ros_time(time_stamp);

		double data;
		line_stream >> data;
		current_frame.x_acc = data;
		line_stream >> data;
		current_frame.y_acc = data;
		line_stream >> data;
		current_frame.z_acc = data;
		line_stream >> data;
		current_frame.yaw_vel = data;
		line_stream >> data;
		current_frame.pitch_vel = data;
		line_stream >> data;
		current_frame.roll_vel = data;
		line_stream >> data;
		current_frame.x_vel = data;
		line_stream >> data;
		current_frame.y_vel = data;
		line_stream >> data;
		current_frame.z_vel = data;
		line_stream >> data;
		current_frame.yaw = data;
		line_stream >> data;
		current_frame.pitch = data;
		line_stream >> data;
		current_frame.roll = data;
		line_stream >> data;
		current_frame.x = data;
		line_stream >> data;
		current_frame.y = data;
		line_stream >> data;
		current_frame.z = data;

		data_frames.push_back(current_frame);
	}

	file.close();
}

ros::Time string_to_ros_time(string& time_str) {
	// replaces the dot by a space
	unsigned int dot_pos = time_str.find('.');
	time_str.replace(dot_pos, 1, " ");

	istringstream iss(time_str);
	unsigned int sec;
	iss >> sec;
	unsigned int nsec;
	iss >> nsec;

	return ros::Time(sec, nsec);
}
