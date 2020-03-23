//
// Created by sab3r on 22.03.20.
//

#ifndef SRC_POSITION_H
#define SRC_POSITION_H

#include "motor.h"
#define W 0.135
#define D 0.065
#define TICK 20
#define PERTICK 0.10205

struct vec
{
    float x;
    float y;
};

class Position {
public:
    ros::Subscriber subR;
    ros::Subscriber subL;
    vec             pos;
    vec             wheelR;
    vec             wheelL;
    float MinPowerToStart = 0;

    explicit Position(ros::NodeHandle *n);
    void SetMinPower();
};


#endif //SRC_POSITION_H
