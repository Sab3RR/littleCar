//
// Created by sab3r on 12.05.2020.
//

#ifndef ALGO_DOTTING_H
#define ALGO_DOTTING_H
#include "rosdef.h"
#define WIDTH 0.5f

enum corners
{
    LEFTUP,
    LEFTDOWN,
    RIGHTUP,
    RIGHTDOWN
};

class dotting {
public:
    std::vector<Sector> sectors;
    std::list<vector<double>> dots;
    ros::Publisher  pubdots;
    ros::Publisher marker_pub;
    double coorddown = 0.f;

    explicit    dotting(ros::NodeHandle *n);
    void        createWay(Sector &sector);
    int         nearestCorner(Sector &sector);
    bool        downdots(vector<double> &dot, vector<double> &down, vector<double> &nearest, vector<double> &up, vector<double> &farest, vector<double> &start);
    bool        updots(vector<double> &dot, vector<double> &down, vector<double> &nearest, vector<double> &up, vector<double> &farest, vector<double> &start);
    void        direction(vector<double> &src, vector<double> &dest);
    double      angle(vector<double> &v1, vector<double> &v2);
    void        startdotting();
};


#endif //ALGO_DOTTING_H
