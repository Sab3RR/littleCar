//
// Created by sab3r on 02.04.20.
//

#ifndef SRC_OBJECTSFROMLASER_H
#define SRC_OBJECTSFROMLASER_H

#include "rosdef.h"
#include <list>

class ObjectsFromLaser {
public:
    ros::Subscriber subL;
    ros::Subscriber subpos;
    ros::Subscriber subdir;
    ros::Publisher<geometry_msgs::PoseArray>  pubpoints;

    vec pos = {0.f,0.f};
    vec dir = {1.f, 0.f};
    std::list<vec> points;

    explicit ObjectsFromLaser(ros::NodeHandle &n);

};


#endif //SRC_OBJECTSFROMLASER_H
