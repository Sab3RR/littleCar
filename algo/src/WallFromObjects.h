//
// Created by sab3r on 28.07.2020.
//

#ifndef ALGO_WALLFROMOBJECTS_H
#define ALGO_WALLFROMOBJECTS_H

#include "rosdef.h"
#include "ObjectsFromLaserV2.h"

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
    std::vector<Wall> walls;
    std::vector<ObjectsFromLaserV2::Point> points_arr;

    explicit WallFromObjects(ros::NodeHandle *n);
    void makeWalls(const algo::point_msg::ConstPtr &msg);
    void createWall(algo::point_msg::_pos_type::iterator pos, algo::point_msg::_r_type::iterator r, const algo::point_msg::ConstPtr &msg);


};


#endif //ALGO_WALLFROMOBJECTS_H
