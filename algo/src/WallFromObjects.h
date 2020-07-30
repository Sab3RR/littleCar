//
// Created by sab3r on 28.07.2020.
//

#ifndef ALGO_WALLFROMOBJECTS_H
#define ALGO_WALLFROMOBJECTS_H

#include "rosdef.h"
#include "ObjectsFromLaserV2.h"
#include "Position.h"
#define CAPTUREDRADIUS DEFAULTRADIUS * 3

class WallFromObjects {
public:
    class Wall
    {
    public:
        tf2::Vector3 start;
        tf2::Vector3 end;
        tf2::Vector3 v;
    };
    ros::Subscriber sub_points;
    ros::Publisher vis_pub;
    std::vector<Wall> walls;
    std::vector<ObjectsFromLaserV2::Point> points_arr;

    explicit WallFromObjects(ros::NodeHandle *n);
    void makeWalls(const algo::point_msg::ConstPtr &msg);
    void createWall(ObjectsFromLaserV2::Point point);
    void tryToCreate(ObjectsFromLaserV2::Point point, ObjectsFromLaserV2::Point points);
    void tryToAdd(Wall &wall, int i, ObjectsFromLaserV2::Point point);
    bool tryToAdd(Wall &wall, ObjectsFromLaserV2::Point point);
    bool wallIntersect(Wall wall);
    bool wallIntersect(Wall wall, int i);
    bool intersect(Wall wall1, Wall wall2);
    int  sign(tf2Scalar scalar);
};


#endif //ALGO_WALLFROMOBJECTS_H
