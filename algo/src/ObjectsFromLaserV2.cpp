//
// Created by sab3r on 13.07.2020.
//

#include "ObjectsFromLaserV2.h"

ObjectsFromLaserV2::ObjectsFromLaserV2(ros::NodeHandle *n)
{
    subOd = n->subscribe("odom", 10, &ObjectsFromLaserV2::odomSub, this);
    subLas = n->subscribe("scan", 10, &ObjectsFromLaserV2::AddObjects, this);
    vis_pub = n->advertise<visualization_msgs::MarkerArray>( "visualization_marker_array", 0 );
    points_pub = n->advertise<algo::point_msg>( "nav_points", 0 );
}

void ObjectsFromLaserV2::odomSub(const nav_msgs::Odometry::ConstPtr &msg)
{
    //pos.setX(msg->pose.pose.position.x);
    //pos.setY(msg->pose.pose.position.y);
    pos.setValue(msg->pose.pose.position.x, msg->pose.pose.position.y, 0);
    tf::Quaternion rotation;
    tf::Vector3 vector(1, 0, 0);
    rotation.setValue(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    tf::Vector3 rotated_vector = tf::quatRotate(rotation, vector);
    dir.setValue(rotated_vector.x(), rotated_vector.y(), 0);
}

void ObjectsFromLaserV2::AddObjects(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    tf2::Vector3 dirToPoint;
    tf2::Vector3 pointPos;
    tf2::Vector3 rotVector(0, 0, 1);
    algo::point_msg pMsg;
    float angle;
    visualization_msgs::MarkerArray markerArray;
    int i = 0;
    for(auto range = msg->ranges.begin(); range != msg->ranges.end(); range++)
    {
        if (*range == INFINITY)
        {
            i++;
            continue;
        }
        angle = msg->angle_min + msg->angle_increment * i;
        dirToPoint = dir;
        dirToPoint = dirToPoint.rotate(rotVector, angle);
        pointPos = pos + (dirToPoint * *range);
        tryAdd(dirToPoint, pointPos);
        i++;
    }
    i = 0;
    for (auto & j : arr)
    {
        geometry_msgs::Vector3 pPos;
        std_msgs::Float32 pR;

        visualization_msgs::Marker marker;
        marker.header.frame_id = "laser";
        marker.header.stamp = ros::Time();
        marker.ns = "my_namespace";
        marker.id = i;
        marker.type = visualization_msgs::Marker::CYLINDER;
        marker.action = visualization_msgs::Marker::ADD;
        pPos.x = marker.pose.position.x = j.pos.x();
        pPos.y = marker.pose.position.y = j.pos.y();
        pPos.z = marker.pose.position.z = 0;
        marker.pose.orientation.x = 0.0;
        marker.pose.orientation.y = 0.0;
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 1.0;
        pR.data = marker.scale.x = j.r;
        marker.scale.y = j.r;
        marker.scale.z = 0.01;
        marker.color.a = 0.5; // Don't forget to set the alpha!
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
        marker.lifetime.fromSec(0.25);
        markerArray.markers.push_back(marker);
        pMsg.pos.push_back(pPos);
        pMsg.r.push_back(pR);
        i++;
    }
    points_pub.publish(pMsg);
    vis_pub.publish(markerArray);

}

void ObjectsFromLaserV2::tryAdd(tf2::Vector3 &dirToPoint, tf2::Vector3 &pointPos)
{
    auto point = arr.begin();
    bool belongsToPoint = false;

    while (point != arr.end())
    {
        if (pointPos.distance(point->pos) <= point->r)
            belongsToPoint = true;
        else if (crossingPoint(dirToPoint, pointPos, *point))
        {
            if (point->r < MINPOINTRADIUS)
            {
                point = arr.erase(point);
                continue;
            }
        }
        point++;
    }
    if (!belongsToPoint)
    {
        addPoint(pointPos);
    }
}
bool ObjectsFromLaserV2::crossingPoint(tf2::Vector3 &dirToPoint, tf2::Vector3 &pointPos, ObjectsFromLaserV2::Point &arrPoint)
{
    tf2::Vector3 laserVec;
    tf2::Vector3 betweenLaserAndPoint;
    tf2::Vector3 pointVec;
    float radiusVec;
    float angle;
    float angle2;

    laserVec = pos - pointPos;
    betweenLaserAndPoint = arrPoint.pos - pointPos;
    pointVec = pos - arrPoint.pos;
    angle = laserVec.angle(betweenLaserAndPoint);
    angle2 = laserVec.angle(pointVec);
    if (angle >= 1.5707 || angle2 >= 1.5707)
        return false;
    else
    {
        radiusVec = betweenLaserAndPoint.length() * sinf(angle);
        if (radiusVec < 0)
        {
            ROS_INFO("radius < 0 detect /n");
        }
        if (radiusVec < arrPoint.r)
        {
            arrPoint.r = radiusVec;
            return true;
        } else
            return false;
    }
}

void ObjectsFromLaserV2::addPoint(tf2::Vector3 &pointPos)
{
    ObjectsFromLaserV2::Point newPoint;

    newPoint.pos = pointPos;
    arr.push_back(newPoint);
}

int main(int ac, char **av)
{
    ObjectsFromLaserV2 *objectsFromLaserV2;
    ros::init(ac, av, "ObjectFromLaserV2");
    ros::NodeHandle n;
    objectsFromLaserV2 = new ObjectsFromLaserV2(&n);
    ros::spin();
}