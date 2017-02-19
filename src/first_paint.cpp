// nothing here yet!

#include <stewie_paints/process_img.h>

void clean_brush() {
  //move over water
  //dip in water   (use first_paint::dipDepth)
  //swish
  //move back
}

void pointilism(std::string img_path) {
  // first, get the image as a series of point/color combos
  std::list<ColorPoint> dots = getImageAsPoints(img_path, 10, 10);
  //now go through all points
  for(std::list<ColorPoint>::iterator it = dots.begin(); it != dots.end(); ++it) {
    // paint a dot

    // select the nearest color
    if(it->r > 250 && it->g > 250 && it->b > 250) {
      ROS_INFO("dot: white");
      continue; //skip white dots
    } else if(it->r < 5 && it->g < 5 && it->b < 5) {
      ROS_INFO("dot: black");
      //set color position
    } else if(it->r > 250 && it->g < 5 && it->b < 5) {
      ROS_INFO("dot: red");
      //set color position
    }
    else {
      ROS_INFO("dot: uncaught");
      continue;
    }

    //move over color

    //dip into color   (use first_paint::dipDepth)
    //lift
    //move to dot
    //move down
    //perform the specified stroke (xy vectors)
    //move up

    //clean off the brust
    clean_brush();
  }
}

// Start everything off
int main(int argc, char** argv)
{
  if(argc < 2) {
    std::cout << "problem! Must supply image path as first argument" << std::endl;
    return -1;
  } else {
    std::cout << "going to paint based on image " << argv[1] << std::endl;
  }

  ros::init(argc, argv, "first_paint");
  ros::NodeHandle nh("first_paint");
  ROS_WARN("First paint start!");

  // move = new MoveInterface();
  // move->initialize("sia5");
  // move->setPlannerId("RRTConnectkConfigDefault");
  // move->setPlanningTime(1.0);
  // move->setVelocityScaling(1);

  pointilism(std::string(argv[1]));

  ROS_WARN("First paint end!");

  //delete move;
  return 0;
}
