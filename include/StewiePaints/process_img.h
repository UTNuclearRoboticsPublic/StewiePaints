
// C++
#include <list>
#include <string>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

struct ColorPoint {
	int x, y;
	int r, g, b;
};

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