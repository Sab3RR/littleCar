//
// Created by sab3r on 02.04.20.
//

#ifndef SRC_OBJECTSFROMLASER_H
#define SRC_OBJECTSFROMLASER_H

#include "rosdef.h"
#include <list>
#include <cmath>
#include <vector>

#define RANGE 0.1


class ObjectsFromLaser {
public:
    ros::Subscriber subL;
    ros::Subscriber subpos;
    ros::Subscriber subdir;
    ros::Publisher pubpoints;
    ros::Publisher vis_pub;

    vec pos = {0.f,0.f};
    float dir = 0;
    std::list<geometry_msgs::Pose> points;
    std::list<Wall> walls;

    explicit ObjectsFromLaser(ros::NodeHandle *n);
    void    AddObjects(const sensor_msgs::LaserScan::ConstPtr &msg);
    bool    hit(geometry_msgs::Pose &point, geometry_msgs::Pose points);
    void    AddWall(const sensor_msgs::LaserScan::ConstPtr &msg);
    bool    checkRange(const sensor_msgs::LaserScan::ConstPtr &msg, int istart, int iend);
    void     setDirection(const sensor_msgs::LaserScan::ConstPtr &msg, int istart, int iend, vector<double> &vdir);
    bool    checkDirection(const sensor_msgs::LaserScan::ConstPtr &msg, vector<double> &vdir, int istart, int iend);
    bool    checkObjectsIntersection(const sensor_msgs::LaserScan::ConstPtr &msg, int istart, int iend);
    void    createVector(const sensor_msgs::LaserScan::ConstPtr &msg, int index, vector<double> &vect);
    void    intersectionByLidar(vector<double> &start, vector<double> &end);
    void    intersect(vector<double> vect, Wall wall);
};


#endif //SRC_OBJECTSFROMLASER_H
