#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

/*
 * Premier brainstorm: on a 180 degrees de vision sur chaque laser
 * SICK. Le laser envoie 75 beams par tour. On capture les beams avec une resolution
 * de 1 degre. Dans le fichier chaque ligne represente un scan (un tour de 180 degre).
 * chaque colonne de la ligne represente le range trouvee a cet angle (si il y a eu
 * un retour!). Le timestamp de ce tour est dans un autre fichier........ Rien de trop
 * compliquer; a partir des donnees angulaires et du range, on constuit un nuage de point
 * pour chaque ligne de retour, et on l'envoie en message avec le timestamp.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "imu_publisher");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);

  int count = 0;
  
  while (ros::ok())
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
