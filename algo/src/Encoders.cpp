//
// Created by sab3r on 20.03.20.
//

#include "Encoders.h"

void Encoders::TickR(const std_msgs::String::ConstPtr& msg)
{
    clock_t cl;
    algo::Encoder_msg sp;

    TicksR++;
    cl = clock();
    TicksPerSecondR = 1 / (float)(cl - timeR) / CLOCKS_PER_SEC;
    if ((cl - timeR) / CLOCKS_PER_SEC > 1)
    {
        TicksPerSecondR = 0;
    }
    timeR = clock();
    sp.Way = TicksR;
    sp.Speed = TicksPerSecondR;
    pubR.publish(sp);
}

void Encoders::TickL(const std_msgs::String::ConstPtr& msg)
{
    clock_t cl;
    algo::Encoder_msg sp;

    TicksL++;
    cl = clock();
    TicksPerSecondL = 1 / ((float)(cl - timeL) / CLOCKS_PER_SEC);
    if ((cl - timeL) / CLOCKS_PER_SEC > 1)
    {
        TicksPerSecondL = 0;
    }
    timeL = clock();
    sp.Way = TicksL;
    sp.Speed = TicksPerSecondL;
    pubL.publish(sp);
}

Encoders::Encoders(ros::NodeHandle *n)
{
    subR = n->subscribe<std_msgs::String>("EncoderR", 100, &Encoders::TickR, this);
    subL = n->subscribe<std_msgs::String>("EncoderL", 100, &Encoders::TickL, this);
    pubR = n->advertise<algo::Encoder_msg>("SpeedAndWayR", 100);
    pubL = n->advertise<algo::Encoder_msg>("SpeedAndWayL", 100);
    timeR = 0;
    timeL = 0;
}