// nothing here yet!

// C++ low-level includes

// ROS includes
#include <ros/ros.h>

// Internal includes
#include <move_interface.h>

MoveInterface* move;
ros::NodeHandle* nh("first_paint");

void paint() {
  // do the actual moves required for painting
}


// Start everything off
int main(int argc, char** argv)
{
  ros::init(argc, argv, "first_paint");
  ROS_WARN("First paint start!");

  nh = new ros::NodeHandle("first_paint");
  move = new MoveInterface();
  moveInterface->initialize("sia5");
  moveInterface->setPlannerId("RRTConnectkConfigDefault");
  moveInterface->setPlanningTime(1.0);
  moveInterface->setVelocityScaling(1);


  paint();

  ROS_WARN("First paint end!");
}