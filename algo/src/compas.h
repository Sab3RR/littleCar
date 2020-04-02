//
// Created by sab3r on 23.03.20.
//

#ifndef SRC_COMPAS_H
#define SRC_COMPAS_H

#include "rosdef.h"
#include <string>
#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>

class compas {
public:
    ros::Subscriber subC;
    ros::Publisher pubC;

    float calibrated = -1;
    explicit compas(ros::NodeHandle *n);
    void toFloat(const std_msgs::String::ConstPtr& msg);
};


#endif //SRC_COMPAS_H
