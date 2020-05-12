//
// Created by sab3r on 12.05.2020.
//

#include "dotting.h"

dotting::dotting(ros::NodeHandle *n)
{
    Sector sector;
    pubdots = n->advertise<algo::vector_array>("destination", 1);
    sector.rightdown.x = -0.15;
    sector.rightdown.y = -0.15;
    sector.rightup.x = -0.15;
    sector.rightup.y = 1.15;
    sector.leftdown.x = 2.15;
    sector.leftdown.y = -0.15;
    sector.leftup.x = 2.15;
    sector.leftup.y = 1.15;
}