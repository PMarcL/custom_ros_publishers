#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

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
int main(int argc, char** argv){
  ros::init(argc, argv, "laser_scan_publisher");

  ros::NodeHandle n;
  ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 50);

  unsigned int num_readings = 181;
  double laser_frequency = 75;
  double ranges[num_readings];
  double intensities[num_readings];

  int count = 0;
  ros::Rate r(1.0);
  while(n.ok()){
    //generate some fake data for our laser scan
    for(unsigned int i = 0; i < num_readings; ++i){
      ranges[i] = count;
      intensities[i] = 100 + count;
    }
    // TODO mettre le "faux" temps a la place
    ros::Time scan_time = ros::Time::now();

    //populate the LaserScan message
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
      scan.ranges[i] = ranges[i];
    }

    scan_pub.publish(scan);
    ++count;
    r.sleep();
  }
}
