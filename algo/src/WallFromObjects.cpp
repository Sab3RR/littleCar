//
// Created by sab3r on 28.07.2020.
//

#include "WallFromObjects.h"

WallFromObjects::WallFromObjects(ros::NodeHandle *n)
{
    sub_points = n->subscribe("nav_points", 0, &WallFromObjects::makeWalls, this);
}

void WallFromObjects::makeWalls(const algo::point_msg::ConstPtr &msg)
{
    auto point_pos = msg->pos.begin();
    auto point_r = msg->r.begin();

    while (point_pos != msg->pos.end() && point_r != msg->r.end())
    {
        createWall(point_pos, point_r, msg);
    }

}