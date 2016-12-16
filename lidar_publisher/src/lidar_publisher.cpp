#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

/*
 * Premier brainstorm: on a 180 degrees de vision sur chaque laser
 * SICK. Le laser envoie 75 beams par tour. On capture les beams avec une resolution
 * de 1 degre. Dans le fichier chaque ligne represente un scan (un tour de 180 degre).
 * chaque colonne de la ligne represente le range trouvee a cet angle (si il y a eu
 * un retour! 0 sinon). NB: on a 181 mesures, on prend une mesure a 0 degre.
 * Le timestamp de ce tour est dans un autre fichier........ Rien de trop
 * complique; a partir des donnees angulaires et du range, on constuit un message
 * pour chaque ligne de retour, et on l'envoie avec le timestamp.
 */
void Split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> Split(const std::string &s, char delim);
std::vector<float> str_to_scan(std::string str);

int main(int argc, char** argv) {
  if (argc != 3)
  {
    // path_to_scan path_to_time
    std::cout << "Bad number of arguments" << std::endl;
    return 1;
  }

  std::ifstream file_scan(argv[1]);
  std::ifstream file_scan_time(argv[2]);
  std::string line_scan;
  std::string line_time;

  ros::init(argc, argv, "laser_scan_publisher");

  ros::NodeHandle n;
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);

  unsigned int num_readings = 181;
  double laser_frequency = 75;
  double ranges[num_readings];
  double intensities[num_readings];

  int count = 0;
  ros::Rate r(laser_frequency);
  sleep(5);
  while(n.ok() && std::getline(file_scan, line_scan) && std::getline(file_scan_time, line_time)){
    std::vector<std::string> ranges = Split(line_scan, ' ');
    std::cout << "Premiere lecture : " << ranges[0];
    double scan_time_UNIX = std::stod(line_time);
    ros::Time scan_time(scan_time_UNIX);
    std::cout << " temps UNIX : " << scan_time_UNIX << std::endl;

    // populate the LaserScan message
    sensor_msgs::LaserScan scan;
    scan.header.stamp = scan_time;
    scan.header.frame_id = "laser_frame";
    // TODO: verifier avec le referentiel du laser si ca a du sens.
    scan.angle_min = 0;
    scan.angle_max = 3.14159;

    scan.angle_increment = 3.14159 / (num_readings-1);
    scan.time_increment = (1 / laser_frequency) / (num_readings-1);
    scan.range_min = 0.0;
    scan.range_max = 10.0;

    scan.ranges.resize(num_readings);
    // TODO populer a l'aide du fichier texte
    for(unsigned int i = 0; i < num_readings; ++i){
      scan.ranges[i] = std::stod(ranges[i]);
    }

    scan_pub.publish(scan);
    ++count;
    r.sleep();
    ROS_INFO("send an IMU message");
  }
}

// Stack overflow code for splitting string
void
Split(const std::string &s, char delim, std::vector<std::string> &elems)
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
}


std::vector<std::string>
Split(const std::string &s, char delim)
{
  std::vector<std::string> elems;
  Split(s, delim, elems);
  return elems;
}
// End of stackoverflow code
