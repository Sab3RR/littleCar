//
// Created by sab3r on 02.04.20.
//

#include "ObjectsFromLaser.h"

ObjectsFromLaser::ObjectsFromLaser(ros::NodeHandle *n)
{
    subL = n->subscribe("scan", 1, &ObjectsFromLaser::AddObjects, this);
    vis_pub = n->advertise<visualization_msgs::MarkerArray>( "visualization_marker", 0 );
}

bool ObjectsFromLaser::hit(geometry_msgs::Pose &point, geometry_msgs::Pose points) {
    float range;

    range = sqrtf(pow(point.position.x - points.position.x, 2) + pow(point.position.y - points.position.y, 2));
    if (points.position.z > range)
    {

        return true;
    } else if (point.position.z > range)
    {
      point.position.z = range;
    }
    return false;
}


void    ObjectsFromLaser::AddObjects(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    geometry_msgs::Pose point;
    geometry_msgs::Pose currentPoint;
    std::list<geometry_msgs::Pose>::iterator p;
    visualization_msgs::MarkerArray markerArray;
    float angle;
    float dist;
    float range;
    bool  add;
    int i;
    addwall(msg);
    for(i = 0; msg->ranges.size() > i; i++)
    {
        if (msg->ranges[i] == INFINITY)
            continue;
        add = true;
        angle = msg->angle_min + dir + i * msg->angle_increment;
        point.position.x = cos(angle) * msg->ranges[i] + pos.x;
        point.position.y = sin(angle) * msg->ranges[i] + pos.y;
        point.position.z = 0.25;
        point.orientation.w = 0;
        p = points.begin();
        while (p != points.end())
        {
            if (add && hit(point, *p))
            {
                add = false;
                p++;
                continue;
            }
            else {
                dist = sqrtf(pow(p->position.x,2) + pow(p->position.y, 2));
                angle = (point.position.x * p->position.x + point.position.y * p->position.y) / (sqrtf(pow(point.position.x, 2) + pow(point.position.y, 2)) * dist);
                if (angle < 0)
                {
                    p++;
                    continue;
                }
                range = sqrtf((1/pow(angle,2)) - 1) * dist;
                if (angle != 0)
                {
                    if ((dist / angle + sqrtf(pow(p->position.z, 2) - pow(range, 2))) > sqrtf(pow(point.position.x, 2) + pow(point.position.y, 2)))
                    {
                        p++;
                        continue;
                    }
                }
                if (range < tan(msg->angle_increment) * dist)
                {
                    p = points.erase(p);
                    continue;
                }
                else if (range < p->position.z)
                    p->position.z = range;
                p++;
            }
        }
        if (add)
        {
            points.push_back(point);
        }
    }
    i = 0;
    for (auto & j : points)
    {
        visualization_msgs::Marker marker;
        marker.header.frame_id = "laser";
        marker.header.stamp = ros::Time();
        marker.ns = "my_namespace";
        marker.id = i;
        marker.type = visualization_msgs::Marker::CYLINDER;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = j.position.x;
        marker.pose.position.y = j.position.y;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        marker.scale.x = j.position.z;
        marker.scale.y = j.position.z;
        marker.scale.z = 0.01;
        marker.color.a = 0.5; // Don't forget to set the alpha!
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
        marker.lifetime.fromSec(0.25);
        markerArray.markers.push_back(marker);
        i++;
    }
    vis_pub.publish( markerArray );
}

int     main(int ac, char** av)
{
    ObjectsFromLaser *objectsFromLaser;
    ros::init(ac, av, "ObjectFromLaser");
    ros::NodeHandle n;
    objectsFromLaser = new ObjectsFromLaser(&n);
    ros::spin();
}