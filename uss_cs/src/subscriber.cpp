#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include <iostream>
#include <vector>

void topic_reader (const std_msgs::Float32MultiArray::ConstPtr& message)
{
  int number_of_elements = 0;
  for(std::vector<float>::const_iterator it = message->data.begin();
  it != message->data.end(); ++it)
    number_of_elements++;
  if (number_of_elements == 0)                                            //Обрабатываем ситуацию с пустым пакетом
  {
    ROS_INFO("No solutions");
    return;
  }
  ROS_INFO("x = %.2f, y = %.2f", message->data[0], message->data[1]);
  return;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle nh_;
  ROS_INFO("Ready to read topic.");
  ros::Subscriber sub = nh_.subscribe("slae_solver", 1000, topic_reader);
  ros::spin();
  return 0;
}
