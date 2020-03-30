//
// Created by sab3r on 24.03.20.
//

#include "ComandReceiver.h"

ComandReceiver::ComandReceiver(ros::NodeHandle *n)
{
    subdir = n->subscribe("direction", 0, &ComandReceiver::Setdir, this);
    subpos = n->subscribe("position", 0, &ComandReceiver::SetSpeed, this);
    subdest = n->subscribe("destination", 0, &ComandReceiver::SetPoint, this);
    pubAr = n->advertise<std_msgs::Float64MultiArray>("MotorForce", 0);
    dest = {0.f, 0.f};
    pos = {0.f, 0.f};
    dir = {0.f, 0.f};
    max_speed = 0;
    sleep(1);
}

void ComandReceiver::SetPoint(const algo::vector_msg::ConstPtr &msg)
{
    dest.x = msg->x;
    dest.y = msg->y;
}

void ComandReceiver::SetSpeed(const algo::vector_msg::ConstPtr &msg)
{
    pos.x = msg->x;
    pos.y = msg->y;
}

void ComandReceiver::Setdir(const algo::vector_msg::ConstPtr &msg)
{
    std_msgs::Float64MultiArray Ar;
    float angle;
    float div;
    float distance;
    vec   dist;

    Ar.data.push_back(0);
    Ar.data.push_back(0);
    dir.x = msg->x;
    dir.y = msg->y;
    dist.x = dest.x - pos.x;
    dist.y = dest.y - pos.y;
    distance = sqrtf(pow(dest.x - pos.x, 2) + pow(dest.y - pos.y, 2));
    if (distance < 10)
    {
        if (distance / 2. > 10)
        {
            max_speed = distance / 2.;
        } else
        {
            max_speed = 0.23f;
        }
    }
    else
        max_speed = 0.23f;
    angle = (dir.x * dist.x + dir.y * dist.y) / (sqrtf(dir.x * dir.x + dir.y * dir.y) * sqrtf(dist.x * dist.x + dist.y * dist.y));
    div = dir.x * dist.y - dist.x * dir.y;
    if (div < 0)
    {
        Ar.data[0] = max_speed;
        if (angle > 0.99)
            Ar.data[1] = max_speed * angle;
        pubAr.publish(Ar);
    } else
    {
        Ar.data[1] = max_speed;
        if (angle > 0.99)
            Ar.data[0] = max_speed * angle;
        pubAr.publish(Ar);
    }


}

int main(int ac, char** av)
{
    ComandReceiver *comand;
    ros::init(ac, av, "ComandReceiver");
    ros::NodeHandle n;
    comand = new ComandReceiver(&n);
   // comand->dest = {1.f, 0.f};
    ros::spin();
    return 0;
}