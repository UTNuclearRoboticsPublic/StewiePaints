
// C++
#include <list>
#include <string>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// ROS
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Vector3.h>
#include <move_interface.h>
#include <ros/ros.h>

using namespace cv;
using namespace std;

namespace first_paint {
	double dipDepth = 0.005;
	double canvasZ = 0;
	MoveInterface* move;
}

using namespace first_paint;

struct ColorPoint {
	int x, y;
	int r, g, b;
};

// Used to name and locate the paints and the water
class paintOrWater {
	public:
		geometry_msgs::PoseStamped paintPose; // The pose when the brush is just above the paint
};

// Define a stroke of the brush
class stroke{
	public:
		string name; // May have several named stroke types
		int x, y; // Starting position for the stroke
		vector< geometry_msgs::Vector3 > strokeVectors; // Small x,y,z vectors to define the stroke
};

// Define the names and locations of paints and water
int definePaintsAndWater()
{
	paintOrWater water;
	water.paintPose.pose.position.x = 0.;
	water.paintPose.pose.position.y = 0.;
	water.paintPose.pose.position.z = 0.;
	water.paintPose.pose.orientation.x = 0.;
	water.paintPose.pose.orientation.y = 0.;
	water.paintPose.pose.orientation.z = 0.;
	water.paintPose.pose.orientation.w = 1.;
	water.paintPose.header.stamp = ros::Time::now();
	water.paintPose.header.frame_id = "base_link";

	paintOrWater black;
	black.paintPose.pose.position.x = 0.;
	black.paintPose.pose.position.y = 0.;
	black.paintPose.pose.position.z = 0.;
	black.paintPose.pose.orientation.x = 0.;
	black.paintPose.pose.orientation.y = 0.;
	black.paintPose.pose.orientation.z = 0.;
	black.paintPose.pose.orientation.w = 1.;
	black.paintPose.header.stamp = ros::Time::now();
	black.paintPose.header.frame_id = "base_link";

	paintOrWater red;
	red.paintPose.pose.position.x = 0.;
	red.paintPose.pose.position.y = 0.;
	red.paintPose.pose.position.z = 0.;
	red.paintPose.pose.orientation.x = 0.;
	red.paintPose.pose.orientation.y = 0.;
	red.paintPose.pose.orientation.z = 0.;
	red.paintPose.pose.orientation.w = 1.;
	red.paintPose.header.stamp = ros::Time::now();
	red.paintPose.header.frame_id = "base_link";

	return 0;
}

// The different types of strokes
int defineStrokes()
{
	stroke flatStripe;
	geometry_msgs::Vector3 vec1;
	vec1.x = 0.005;
	vec1.y = 0;
	vec1.z = 0;
	flatStripe.strokeVectors.push_back( vec1 );

	return 0;
}

/*
 * imgPath: absolute path to image
 * horizRes: width of the color point grid
 * vertRes: height of the color point grid
 */
std::list<ColorPoint> getImageAsPoints(std::string img_path, int horiz_res, int vert_res) {
	std::list<ColorPoint> list = std::list<ColorPoint>();

	Mat image;
	image = imread(img_path, CV_LOAD_IMAGE_COLOR);

	if(!image.data)
	{
		std::cout << "could not load image " << img_path << "!" << std::endl;
		return list;
	}

	int img_width = image.cols;
	int img_height = image.rows;

	float x_step = ((float)img_width)/horiz_res;
	float y_step = ((float)img_height)/vert_res;

	for(int i=0; i < horiz_res; ++i) {
		for(int j=0; j < vert_res; ++j) {
			ColorPoint cp;
			// TODO: test RGB/BGR image
			int x = i * x_step;
			int y = j * y_step;
			Vec3b pix_color = image.at<Vec3b>(x, y);

			// TODO: posterize?
			cp.r = pix_color[0];
			cp.g = pix_color[1];
			cp.b = pix_color[2];
			cp.x = x;
			cp.y = y;
			// std::cout << "color (" << cp.r << ", " << cp.g << ", " << cp.b << ") at point (" << cp.x << ", " << cp.y << ")." << std::endl;
			list.push_back(cp);
		}
	}

	return list;
}
