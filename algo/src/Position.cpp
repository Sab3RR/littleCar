//
// Created by sab3r on 22.03.20.
//

#include "Position.h"

void Position::Rwheel(const algo::Encoder_msg::ConstPtr& msg)
{
    algo::vector_msg vec;
    if (inited)
    {
        wheelR.x += dir.x * PERTICK;
        wheelR.y += dir.y * PERTICK;
        pos = {(wheelL.x - wheelR.x) / 2 + wheelR.x, (wheelL.y - wheelR.y) / 2 + wheelR.y};
        vec.x = pos.x;
        vec.y = pos.y;
        pubpos.publish(vec);
    } else
    {
        if (msg->Speed > 0)
            inited = true;
    }
}

void Position::Lwheel(const algo::Encoder_msg::ConstPtr& msg)
{
    algo::vector_msg vec;
    if (inited)
    {
        wheelL.x += dir.x * PERTICK;
        wheelL.y += dir.y * PERTICK;
        pos = {(wheelR.x - wheelL.x) / 2 + wheelL.x, (wheelR.y - wheelL.y) / 2 + wheelL.y};
        vec.x = pos.x;
        vec.y = pos.y;
        pubpos.publish(vec);
    } else
    {
        if (msg->Speed > 0)
            inited = true;
    }
}

void Position::Compas(const std_msgs::Float64::ConstPtr& msg)
{
    algo::vector_msg vec;
    float rad;
    rad = (float)(msg->data) * (float)(M_PI / 180);
    if (dir.x == 0.f && dir.y == 0.f)
    {

        dir.x = cosf(rad);
        dir.y = sinf(rad);
        vec.x = dir.x;
        vec.y = dir.y;
        pubdir.publish(vec);
        wheelR = {static_cast<float>(dir.y * W / 2), static_cast<float>(-dir.x * W / 2)};
        wheelL = {static_cast<float>(-dir.y * W / 2), static_cast<float>(dir.x * W / 2)};
    } else
    {
        dir.x = cosf(rad);
        dir.y = sinf(rad);
        vec.x = dir.x;
        vec.y = dir.y;
        pubdir.publish(vec);

    }
}


/*void Position::SetMinPower()
{
    float   power = 0;
    bool    rwheel = true;
    std_msgs::Float64MultiArray Ar;

    Ar.data.push_back(power);
    Ar.data.push_back(power);
    while (ros::ok())
    {
        if (inited)
        {
            if (rwheel)
            {
                Ar.data[0] = 0;
                Ar.data[1] = 0;
                pubAr.publish(Ar);
                sleep(1);
                rwheel = false;
                if (MinPowerToStart < power)
                    MinPowerToStart = power;
                power = 0;
                ros::spinOnce();
                inited = false;
            } else
            {
                Ar.data[0] = 0;
                Ar.data[1] = 0;
                pubAr.publish(Ar);
                if (MinPowerToStart < power)
                    MinPowerToStart = power;
                break;
            }
        }
        if (rwheel)
        {
            Ar.data[0] = power;
            Ar.data[1] = 0;
            pubAr.publish(Ar);
            ros::spinOnce();
        } else
        {
            Ar.data[0] = 0;
            Ar.data[1] = power;
            pubAr.publish(Ar);
            ros::spinOnce();
        }
        sleep(1);
        power += 0.02;
    }
}*/
Position::Position(ros::NodeHandle *n)
{
    subR = n->subscribe("SpeedAndWayR", 0, &Position::Rwheel, this);
    subL = n->subscribe("SpeedAndWayL", 0, &Position::Lwheel, this);
    subC = n->subscribe("Fcompas", 1, &Position::Compas, this);
    pubpos = n->advertise<algo::vector_msg>("position", 1);
    pubdir = n->advertise<algo::vector_msg>("direction", 1);
    pubAr = n->advertise<std_msgs::Float64MultiArray>("MotorForce", 10);
    sleep(1);

}


int main(int ac, char** av)
{
    Position *pos;
    ros::init(ac, av, "position");
    ros::NodeHandle n;
    pos = new Position(&n);


   // pos->SetMinPower();
    ros::spin();
    return 0;
}