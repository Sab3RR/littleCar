//
// Created by sab3r on 19.03.20.
//

#ifndef SRC_MOTORCONTROLLER_H
#define SRC_MOTORCONTROLLER_H
#include "motor.h"
#include <cmath>

class MotorController {
public:
    float MotorR = 0;
    float MotorL = 0;
    ros::Publisher pubR;
    ros::Publisher pubL;
    ros::Subscriber SubAr;


    explicit MotorController(ros::NodeHandle *n);
    void Stop();
    void SetForce(float EnR, float EnL);
    void Forward(float En);
    void Backward(float En);
    void SetForceR(float EnR);
    void SetForceL(float EnL);
    void SubscribeArray(const std_msgs::Float64MultiArray::ConstPtr& msg);



};


#endif //SRC_MOTORCONTROLLER_H
