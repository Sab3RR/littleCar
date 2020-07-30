//
// Created by sab3r on 13.07.2020.
//

#ifndef ALGO_OBJECTSFROMLASERV2_H
#define ALGO_OBJECTSFROMLASERV2_H

#include "rosdef.h"

#define DEFAULTRADIUS 0.05
#define MINPOINTRADIUS 0.001

class ObjectsFromLaserV2 {
public:
    class Point
    {
    public:
        tf2::Vector3 pos;
        //std::vector<Wall>::iterator wall;
        float r = DEFAULTRADIUS;
    };
    ros::Subscriber subOd;
    ros::Subscriber subLas;
    ros::Publisher  vis_pub;
    ros::Publisher  points_pub;
    tf2::Vector3    pos = tf2::Vector3(0, 0, 0);
    tf2::Vector3    dir = tf2::Vector3(1, 0, 0);

    std::list<ObjectsFromLaserV2::Point> arr;


    explicit ObjectsFromLaserV2(ros::NodeHandle *n);
    void odomSub(const nav_msgs::Odometry::ConstPtr &msg);
    void AddObjects(const sensor_msgs::LaserScan::ConstPtr &msg);
    void tryAdd(tf2::Vector3 &dirToPoint, tf2::Vector3 &pointPos);
    void addPoint(tf2::Vector3 &pointPos);
    bool crossingPoint(tf2::Vector3 &dirToPoint, tf2::Vector3 &pointPos, ObjectsFromLaserV2::Point &arrPoint);

};


#endif //ALGO_OBJECTSFROMLASERV2_H
