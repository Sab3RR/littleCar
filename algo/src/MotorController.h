//
// Created by sab3r on 19.03.20.
//

#ifndef SRC_MOTORCONTROLLER_H
#define SRC_MOTORCONTROLLER_H
#include "rosdef.h"
#include <cmath>

class MotorController {
public:
    int MotorR = 0;
    int MotorL = 0;
    float EncoderR = 0.f;
    float EncoderL = 0.f;
    float ForceL = 0.f;
    float ForceR = 0.f;
    ros::Publisher pubR;
    ros::Publisher pubL;
    ros::Subscriber SubAr;
    ros::Subscriber SubLrate;
    ros::Subscriber SubRrate;
    ros::Subscriber SubDLrate;
    ros::Subscriber SubDRrate;

    explicit MotorController(ros::NodeHandle *n);
    void Stop();
    void SetForce(float EnR, float EnL);
    void Forward(float En);
    void Backward(float En);
    void SetForceR(float EnR);
    void SetForceL(float EnL);
    void SubscribeArray(const std_msgs::Float64MultiArray::ConstPtr& msg);
    void lrate(const std_msgs::Float32::ConstPtr& msg);
    void rrate(const std_msgs::Float32::ConstPtr& msg);
    void Dlrate(const std_msgs::Int32::ConstPtr& msg);
    void Drrate(const std_msgs::Int32::ConstPtr& msg);




};


#endif //SRC_MOTORCONTROLLER_H
