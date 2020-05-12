//
// Created by sab3r on 12.05.2020.
//

#ifndef ALGO_DOTTING_H
#define ALGO_DOTTING_H
#include "rosdef.h"
#define WIDTH 0.15

class dotting {
public:
    std::vector<Sector> sectors;
    ros::Publisher  pubdots;

    explicit dotting(ros::NodeHandle *n);

};


#endif //ALGO_DOTTING_H
