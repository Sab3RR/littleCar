//
// Created by sab3r on 25.03.20.
//

#include "PointArray.h"

void PointArray::handPoint(const std_msgs::Float64::ConstPtr &msg)
{
    if (secondpoint)
    {
        hendpoint.y = msg->data;
        secondpoint = false;
        bhendpoint = true;
    }
    else
    {
        hendpoint.x = msg->data;
        secondpoint = true;
        bhendpoint = false;
    }
}

void PointArray::PointTransmitter(const algo::vector_msg::ConstPtr &msg)
{
    float lenght;

    if (bhendpoint)
    {
        pubdest.publish(hendpoint);
        return;
    }
    if (points.size() == 0)
        return ;
    lenght = sqrtf(pow(msg->x - points[pointI].x, 2) + pow(msg->y - points[pointI].y, 2));

    if (lenght < 0.05)
    {
        pointI++;
        if (points.size() <= pointI)
            pointI = 0;
    }
    pubdest.publish(points[pointI]);
}

PointArray::PointArray(ros::NodeHandle *n)
{
    algo::vector_msg point;

    subpos = n->subscribe("position", 0, &PointArray::PointTransmitter, this);
    subpoints = n->subscribe("handpoint", 0, &PointArray::handPoint, this);
    pubdest = n->advertise<algo::vector_msg>("destination", 1);

    point.x = 1;
    point.y = 0;
    points.push_back(point);
    point.y = 0.25;
    points.push_back(point);
    point.x = 0;
    points.push_back(point);
    point.y = 0.5;
    points.push_back(point);
    point.x = 1;
    points.push_back(point);
    point.y = 0.75;
    points.push_back(point);
    point.x = 0;
    points.push_back(point);
    point.y = 1;
    points.push_back(point);
    point.x = 1;
    points.push_back(point);
    point.y = 1.25;
    points.push_back(point);
    point.x = 0;
    points.push_back(point);
    point.y = 1.5;
    points.push_back(point);
    point.x = 1;
    points.push_back(point);
    point.y = 1.75;
    points.push_back(point);
    point.x = 0;
    points.push_back(point);
    point.y = 2;
    points.push_back(point);
    point.x = 1;
    points.push_back(point);
    point.x = 0;
    point.y = 0;
    points.push_back(point);

}

int main(int ac, char** av)
{
    PointArray *pointarray;
    ros::init(ac, av, "PointArray");
    ros::NodeHandle n;
    pointarray = new PointArray(&n);
    ros::spin();
    return 0;
}