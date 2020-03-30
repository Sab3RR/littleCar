//
// Created by sab3r on 20.03.20.
//

#ifndef SRC_MOTOR_H
#define SRC_MOTOR_H
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Vector3.h>
#include <tf/LinearMath/Quaternion.h>
#include <sensor_msgs/Imu.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/transform_broadcaster.h>
#include <sensor_msgs/MagneticField.h>
#include <geometry_msgs/TransformStamped.h>
#include "algo/Encoder_msg.h"
#include "algo/vector_msg.h"


struct vec
{
    float x;
    float y;
};
#endif //SRC_MOTOR_H
