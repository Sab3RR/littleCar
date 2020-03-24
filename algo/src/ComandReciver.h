//
// Created by sab3r on 24.03.20.
//

#ifndef SRC_COMANDRECIVER_H
#define SRC_COMANDRECIVER_H

#include "motor.h"
#include <cmath>
class ComandReciver {
public:
    ros::Publisher  pubAr;
    ros::Subscriber subdir;
    ros::Subscriber subpos;
    ros::Subscriber subdest;

    vec             dest;
    vec             pos;
    vec             dir;
    float           max_speed;

    explicit    ComandReciver(ros::NodeHandle *n);
    void        SetPoint(const algo::vector_msg::ConstPtr& msg);
    void        SetSpeed(const algo::vector_msg::ConstPtr& msg);
    void        Setdir(const algo::vector_msg::ConstPtr& msg);
};


#endif //SRC_COMANDRECIVER_H
