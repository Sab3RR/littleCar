//
// Created by sab3r on 02.04.20.
//

#ifndef SRC_OBJECTSFROMLASER_H
#define SRC_OBJECTSFROMLASER_H

#include "rosdef.h"
#include <list>
#include <cmath>

class ObjectsFromLaser {
public:
    ros::Subscriber subL;
    ros::Subscriber subpos;
    ros::Subscriber subdir;
    ros::Publisher pubpoints;
    ros::Publisher vis_pub;

    vec pos = {0.f,0.f};
    float dir = 0;
    std::list<geometry_msgs::Pose> points;

    explicit ObjectsFromLaser(ros::NodeHandle *n);
    void    AddObjects(const sensor_msgs::LaserScan::ConstPtr &msg);

};


#endif //SRC_OBJECTSFROMLASER_H
