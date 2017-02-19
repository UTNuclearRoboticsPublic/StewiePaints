
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

struct color_point {
	int x, y;
	int r, g, b;
};

// Used to name and locate the paints and the water
class paint_or_water {
	public:
		geometry_msgs::PoseStamped paint_pose; // The pose when the brush is just above the paint
};

// Define a stroke of the brush
class stroke{
	public:
		string name; // May have several named stroke types
		int x, y; // Starting position for the stroke
		vector< geometry_msgs::Vector3 > stroke_vectors; // Small x,y,z vectors to define the stroke
};

/*
 * imgPath: absolute path to image
 * horizRes: width of the color point grid
 * vertRes: height of the color point grid
 */
std::list<color_point> get_image_as_points(std::string img_path, int horiz_res, int vert_res) {
	std::list<color_point> list = std::list<color_point>();

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
			color_point cp;
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
