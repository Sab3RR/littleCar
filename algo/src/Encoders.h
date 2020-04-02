//
// Created by sab3r on 20.03.20.
//

#ifndef SRC_ENCODERS_H
#define SRC_ENCODERS_H
#include "rosdef.h"
#include <functional>
#include <ctime>


class Encoders {
public:
    unsigned long long TicksR = 0;
    unsigned long long TicksL = 0;
    float TicksPerSecondR = 0;
    float TicksPerSecondL = 0;
    clock_t timeR;
    clock_t timeL;

    explicit Encoders(ros::NodeHandle *n);

private:
    ros::Subscriber subR;
    ros::Subscriber subL;
    ros::Publisher  pubR;
    ros::Publisher  pubL;
    void TickR(const std_msgs::String::ConstPtr& msg);
    void TickL(const std_msgs::String::ConstPtr& msg);
};


#endif //SRC_ENCODERS_H
