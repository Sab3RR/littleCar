//
// Created by sab3r on 02.04.20.
//

#include "ObjectsFromLaser.h"

ObjectsFromLaser::ObjectsFromLaser(ros::NodeHandle *n)
{
    subL = n->subscribe("scan", 1, &ObjectsFromLaser::AddObjects, this);
    vis_pub = n->advertise<visualization_msgs::MarkerArray>( "visualization_marker", 0 );
}

void    ObjectsFromLaser::AddObjects(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    geometry_msgs::Pose point;
    visualization_msgs::MarkerArray markerArray;
    float angle;
    float range;
    bool  add;
    int i;

    for(i = 0; msg->ranges.size() > i; i++)
    {
        if (msg->ranges[i] == INFINITY)
            continue;
        add = true;
        angle = msg->angle_min + dir + i * msg->angle_increment;
        point.position.x = cos(angle) * msg->ranges[i];
        point.position.y = sin(angle) * msg->ranges[i];
        point.position.z = 0.25;
        for (auto & j : points)
        {
            range = sqrtf(pow(point.position.x - j.position.x, 2) + pow(point.position.y - j.position.y, 2));
            if (j.position.z > range)
            {
               add = false;
               break;
            } else if (point.position.z > range)
            {
                point.position.z = range;
            }
        }
        if (add)
            points.push_back(point);
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
        marker.pose.position.z = 1;
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