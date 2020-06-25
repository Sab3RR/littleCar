//
// Created by sab3r on 22.03.20.
//

#ifndef SRC_POSITION_H
#define SRC_POSITION_H

#include "rosdef.h"
#include "cmath"
#define W 0.135f
#define D 0.065f
#define TICK 20
#define PERTICK 0.010205f


class Position {
public:
    ros::Subscriber subR;
    ros::Subscriber subL;
    ros::Subscriber subC;
    ros::Publisher  pubAr;
    ros::Publisher  pubpos;
    ros::Publisher  pubdir;
    ros::Publisher marker_pub;

    vec pos = {0.f,0.f};
    vec  dir = {0.f,0.f};
    vec  wheelR;
    vec  wheelL;
    visualization_msgs::Marker line_list;
    visualization_msgs::Marker arrow;

    bool inited = false;


    explicit Position (ros::NodeHandle *n);
   // void SetMinPower ();
    void Rwheel (const algo::Encoder_msg::ConstPtr& msg);
    void Lwheel (const algo::Encoder_msg::ConstPtr& msg);
    void Compas (const std_msgs::Float64::ConstPtr& msg);
};


#endif //SRC_POSITION_H
