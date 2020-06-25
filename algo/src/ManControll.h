//
// Created by sab3r on 22.06.2020.
//

#ifndef ALGO_MANCONTROLL_H
#define ALGO_MANCONTROLL_H

#include "rosdef.h"

#define SPEED 0.1

class ManControll {
public:
    ros::Publisher pubAr;

    explicit ManControll(ros::NodeHandle *n);
    int getch();

};


#endif //ALGO_MANCONTROLL_H
