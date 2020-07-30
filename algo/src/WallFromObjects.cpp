//
// Created by sab3r on 28.07.2020.
//

#include "WallFromObjects.h"

WallFromObjects::WallFromObjects(ros::NodeHandle *n)
{
    sub_points = n->subscribe("nav_points", 1, &WallFromObjects::makeWalls, this);
    vis_pub = n->advertise<visualization_msgs::MarkerArray>( "visualization_marker_array", 0 );
}

void WallFromObjects::makeWalls(const algo::point_msg::ConstPtr &msg)
{
    auto point_pos = msg->pos.begin();
    auto point_r = msg->r.begin();
    ObjectsFromLaserV2::Point point;
    visualization_msgs::MarkerArray markerArray;
    double res;
    double secs = ros::Time::now().toSec();


    points_arr.erase(points_arr.begin(), points_arr.end());
    walls.erase(walls.begin(), walls.end());
    res = ros::Time::now().toSec() - secs;
    ROS_INFO("erased - %f", res);
    ROS_INFO("points_arr - %d", points_arr.size());
    secs = ros::Time::now().toSec();
    while (point_pos != msg->pos.end() && point_r != msg->r.end())
    {
        point.pos.setX(point_pos->x);
        point.pos.setY(point_pos->y);
        point.pos.setZ(point_pos->z);
        point.r = point_r->data;
        points_arr.push_back(point);
        point_pos++;
        point_r++;
    }
    res = ros::Time::now().toSec() - secs;
    ROS_INFO("added - %f", res);
    secs = ros::Time::now().toSec();
    for (auto points : points_arr)
    {
        double res2;
        double secs2 = ros::Time::now().toSec();

        createWall(points);
        res2 = ros::Time::now().toSec() - secs2;
        ROS_INFO("creating - %f", res2);
    }
    res = ros::Time::now().toSec() - secs;
    ROS_INFO("created - %f", res);
    secs = ros::Time::now().toSec();
    int i = 0;
    for (auto & j : walls)
    {
        visualization_msgs::Marker marker;
        geometry_msgs::Point p;
        marker.header.frame_id = "laser";
        marker.header.stamp = ros::Time();
        marker.ns = "new_namespace";
        marker.id = i;
        marker.type = visualization_msgs::Marker::LINE_LIST;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = 0;
        marker.pose.position.y = 0;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = 0.05;
        marker.color.a = 0.5; // Don't forget to set the alpha!
        marker.color.r = (rand() % 50 + 50) / 100.f;
        marker.color.g = (rand() % 50 + 50) / 100.f;
        marker.color.b = (rand() % 50 + 50) / 100.f;
        p.x = j.start.x();
        p.y = j.start.y();
        p.z = 0;
        marker.points.push_back(p);
        p.x = j.end.x();
        p.y = j.end.y();
        marker.points.push_back(p);
        marker.lifetime.fromSec(0.25);
        markerArray.markers.push_back(marker);
        i++;
    }
    vis_pub.publish(markerArray);
    res = ros::Time::now().toSec() - secs;
    ROS_INFO("sended - %f", res);
}

void WallFromObjects::createWall(ObjectsFromLaserV2::Point point)
{
    for (auto points : points_arr)
    {
        if (point.pos.distance(points.pos) == 0)
            continue;
        if (point.pos.distance(points.pos) < CAPTUREDRADIUS)
        {
            tryToCreate(point, points);
        }
        /*else
        {
            for (int i = 0; i < walls.size(); i++)
            {

                tryToAdd(walls[i], i, points);
            }
        }*/
    }
}

void WallFromObjects::tryToCreate(ObjectsFromLaserV2::Point point, ObjectsFromLaserV2::Point points)
{
    Wall new_wall;
    bool add = false;

    new_wall.start = point.pos;
    new_wall.end = points.pos;
    new_wall.v = new_wall.end - new_wall.start;

    if (!wallIntersect(new_wall))
    {
        for (auto points : points_arr)
        {
            if (tryToAdd(new_wall, points))
                add = true;
        }
        if (add && new_wall.v.length() > DEFAULTRADIUS)
            walls.push_back(new_wall);
    }

}

bool WallFromObjects::wallIntersect(Wall wall)
{
    for (auto walls_arr : walls)
    {
        if (intersect(wall, walls_arr))
            return true;
    }
    return false;
}

bool WallFromObjects::wallIntersect(Wall wall, int i)
{
    for (int j = 0; j < walls.size(); j++)
    {
        if (j == i)
            continue;
        if (intersect(wall, walls[j]))
            return true;
    }
    return false;
}

bool WallFromObjects::intersect(Wall wall1, Wall wall2)
{
    tf2::Vector3 prod1;
    tf2::Vector3 prod2;

    prod1 = wall1.v.cross(wall2.end - wall1.start);
    prod2 = wall1.v.cross(wall2.start - wall1.start);

    if(sign(prod1.z()) == sign(prod2.z()) || (prod1.z() == 0) || (prod2.z() == 0))
        return false;

    prod1 = wall2.v.cross(wall1.end - wall2.start);
    prod2 = wall2.v.cross(wall1.start - wall2.start);

    if(sign(prod1.z()) == sign(prod2.z()) || (prod1.z() == 0) || (prod2.z() == 0))
        return false;

    return true;
}

int  WallFromObjects::sign(tf2Scalar scalar)
{
    if (scalar < 0)
        return -1;
    else
        return 1;
}

void WallFromObjects::tryToAdd(Wall &wall, int i, ObjectsFromLaserV2::Point point)
{
    tf2::Vector3 addble;
    Wall new_wall;
    float angle;

    new_wall = wall;
    addble = point.pos - new_wall.end;
    angle = new_wall.v.angle(addble);
    if (angle < 0.0872665 && addble.length() < W && addble.length() != 0)
    {
        new_wall.end = point.pos;
        new_wall.v = new_wall.end - new_wall.start;
        if (!wallIntersect(new_wall, i))
        {
            wall = new_wall;
            return;
        }
    }
    new_wall = wall;
    addble = point.pos - new_wall.start;
    angle = new_wall.v.angle(addble);
    if (angle > 3.05433 && addble.length() < W && addble.length() != 0)
    {
        new_wall.start = point.pos;
        new_wall.v = new_wall.end - new_wall.start;
        if (!wallIntersect(new_wall, i))
        {
            wall = new_wall;
            return;
        }
    }
}

bool WallFromObjects::tryToAdd(Wall &wall, ObjectsFromLaserV2::Point point)
{
    tf2::Vector3 addble;
    Wall new_wall;
    float angle;

    new_wall = wall;
    addble = point.pos - new_wall.end;
    angle = new_wall.v.angle(addble);
    if (angle < 0.0174533 && addble.length() < W && addble.length() != 0)
    {
        new_wall.end = point.pos;
        new_wall.v = new_wall.end - new_wall.start;
        if (!wallIntersect(new_wall))
        {
            wall = new_wall;
            return true;
        }
    }
    new_wall = wall;
    addble = point.pos - new_wall.start;
    angle = new_wall.v.angle(addble);
    if (angle > 3.29867 && addble.length() < W && addble.length() != 0)
    {
        new_wall.start = point.pos;
        new_wall.v = new_wall.end - new_wall.start;
        if (!wallIntersect(new_wall))
        {
            wall = new_wall;
            return true;
        }
    }
    return false;
}

int main(int ac, char **av)
{
    WallFromObjects *wallFromObjects;
    ros::init(ac, av, "WallFromObjects");
    ros::NodeHandle n;
    wallFromObjects = new WallFromObjects(&n);
    ros::spin();
}