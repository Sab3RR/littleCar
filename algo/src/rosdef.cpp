#include "MotorController.h"
#include "Encoders.h"
#include "rosdef.h"


int main(int ac, char** av)
{
    MotorController* motor;
    Encoders* encoders;
    ros::init(ac, av, "motor");
    ros::NodeHandle n;
    //ros::Rate r(50);
    encoders = new Encoders(&n);
    motor = new MotorController(&n);
    ros::spin();
    return 0;
}


