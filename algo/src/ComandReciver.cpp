//
// Created by sab3r on 24.03.20.
//

#include "ComandReciver.h"

ComandReciver::ComandReciver(ros::NodeHandle *n)
{
    subdir = n->subscribe("direction", 0, &ComandReciver::Setdir, this);
    subpos = n->subscribe("position", 0, &ComandReciver::SetPoint, this);
    subdest = n->subscribe("destination", 0, &ComandReciver::SetPoint, this);
    pubAr = n->advertise<std_msgs::Float64MultiArray>("MotorForce", 0);
    dest = {0.f, 0.f};
    pos = {0.f, 0.f};
    dir = {0.f, 0.f};
    max_speed = 0;
    sleep(1);
}

void ComandReciver::SetPoint(const algo::vector_msg::ConstPtr &msg)
{
    dest.x = msg->x;
    dest.y = msg->y;
}

void ComandReciver::SetSpeed(const algo::vector_msg::ConstPtr &msg)
{
    pos.x = msg->x;
    pos.y = msg->y;
}

void ComandReciver::Setdir(const algo::vector_msg::ConstPtr &msg)
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
    if (distance < 1)
        max_speed = distance;
    else
        max_speed = 1;
    angle = (dir.x * dist.x + dir.y * dist.y) / (sqrtf(dir.x * dir.x + dir.y * dir.y) * sqrtf(dist.x * dist.x + dist.y * dist.y));
    div = dir.x * dist.y - dist.x * dir.y;
    if (div < 0)
    {
        Ar.data[0] = max_speed;
        if (angle > 0)
            Ar.data[1] = max_speed * angle;
        pubAr.publish(Ar);
    } else
    {
        Ar.data[1] = max_speed;
        if (angle > 0)
            Ar.data[0] = max_speed * angle;
        pubAr.publish(Ar);
    }


}

int main(int ac, char** av)
{
    ComandReciver *comand;
    ros::init(ac, av, "ComandReciver");
    ros::NodeHandle n;
    comand = new ComandReciver(&n);
    comand->dest = {1.f, 0.f};
    ros::spin();
    return 0;
}