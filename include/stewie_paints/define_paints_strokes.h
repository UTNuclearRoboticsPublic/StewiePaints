
namespace stewie_paints {
	double dip_depth = 0.005;
	double canvas_Z = 0;

	// Stroke types
	stroke flat_stripe;
	stroke rinse;

	// Paints and water
	paint_or_water water;
	paint_or_water red;
	paint_or_water black;

	MoveInterface* move;
}

using namespace stewie_paints;

// Define the names and locations of paints and water
void define_paints_and_water()
{
	water.paint_pose.pose.position.x = 0.;
	water.paint_pose.pose.position.y = 0.;
	water.paint_pose.pose.position.z = 0.;
	water.paint_pose.pose.orientation.x = 0.;
	water.paint_pose.pose.orientation.y = 0.;
	water.paint_pose.pose.orientation.z = 0.;
	water.paint_pose.pose.orientation.w = 1.;
	water.paint_pose.header.stamp = ros::Time::now();
	water.paint_pose.header.frame_id = "base_link";

	black.paint_pose.pose.position.x = 0.;
	black.paint_pose.pose.position.y = 0.;
	black.paint_pose.pose.position.z = 0.;
	black.paint_pose.pose.orientation.x = 0.;
	black.paint_pose.pose.orientation.y = 0.;
	black.paint_pose.pose.orientation.z = 0.;
	black.paint_pose.pose.orientation.w = 1.;
	black.paint_pose.header.stamp = ros::Time::now();
	black.paint_pose.header.frame_id = "base_link";

	red.paint_pose.pose.position.x = 0.;
	red.paint_pose.pose.position.y = 0.;
	red.paint_pose.pose.position.z = 0.;
	red.paint_pose.pose.orientation.x = 0.;
	red.paint_pose.pose.orientation.y = 0.;
	red.paint_pose.pose.orientation.z = 0.;
	red.paint_pose.pose.orientation.w = 1.;
	red.paint_pose.header.stamp = ros::Time::now();
	red.paint_pose.header.frame_id = "base_link";
}

// The different types of strokes
void define_strokes()
{
	geometry_msgs::Vector3 vec;

	// Flat stripe
	vec.x = 0.005;
	vec.y = 0;
	vec.z = 0;
	flat_stripe.stroke_vectors.push_back( vec );

	// Move back and forth to rinse the brush
	vec.x = 0.005;
	vec.y = 0;
	vec.z = 0;
	rinse.stroke_vectors.push_back( vec );
	vec.x = -0.005;
	vec.y = 0;
	vec.z = 0;
	rinse.stroke_vectors.push_back( vec );
	vec.x = 0.005;
	vec.y = 0;
	vec.z = 0;
	rinse.stroke_vectors.push_back( vec );
}

