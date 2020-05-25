//
// Created by sab3r on 20.03.20.
//

#ifndef SRC_ROSDEF_H
#define SRC_ROSDEF_H
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf/LinearMath/Quaternion.h>
#include <sensor_msgs/Imu.h>
//#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
//#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <sensor_msgs/MagneticField.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/TransformStamped.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include "algo/Encoder_msg.h"
#include "algo/vector_msg.h"
#include "algo/vector_array.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <vector>
#define LENGTH norm_2
using namespace boost::numeric::ublas;
struct vec
{
    float x;
    float y;
};

class Wall
{
public:
    vector<double> *start;
    vector<double> *end;
    vector<double> *dir;
    vector<double> *v;


    Wall()
    {
        start = new vector<double>(2);
        end = new vector<double>(2);
        dir = new vector<double>(2);
        v = new vector<double>(2);
    }

};

class Sector
{
public:
    vector<double> leftup = vector<double>(2);
    vector<double> leftdown = vector<double>(2);
    vector<double> rightup = vector<double>(2);
    vector<double> rightdown =  vector<double>(2);
    std::vector<Sector *> transit;
};
#endif //SRC_ROSDEF_H
