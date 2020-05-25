//
// Created by sab3r on 12.05.2020.
//

#include "dotting.h"

dotting::dotting(ros::NodeHandle *n) {
    Sector sector;

    for (int i = 0; i != 3; i++)
        sectors.push_back(sector);
    marker_pub = n->advertise<visualization_msgs::Marker>("visualization_marker", 10);
    pubdots = n->advertise<algo::vector_array>("dots", 1);
    /*sectors[0].rightdown[0] = -0.15f;
    sectors[0].rightdown[1] = -0.15f;
    sectors[0].rightup[0] = -0.15f;
    sectors[0].rightup[1] = 1.15f;
    sectors[0].leftdown[0] = 2.15f;
    sectors[0].leftdown[1] = -0.15f;
    sectors[0].leftup[0] = 2.15f;
    sectors[0].leftup[1] = 1.15f;
    sectors[1].rightdown[0] = 2.15f;
    sectors[1].rightdown[1] = -2.15f;
    sectors[1].rightup[0] = 2.15f;
    sectors[1].rightup[1] = 1.15f;
    sectors[1].leftup[0] = 3.30f;
    sectors[1].leftup[1] = 1.15f;
    sectors[1].leftdown[0] = 3.30f;
    sectors[1].leftdown[1] = -2.15f;
    sectors[2].leftdown[0] = 2.15f;
    sectors[2].leftdown[1] = -2.15f;
    sectors[2].leftup[0] = 2.15f;
    sectors[2].leftup[1] = -0.85f;
    sectors[2].rightup[0] = -0.15f;
    sectors[2].rightup[1] = -0.85f;
    sectors[2].rightdown[0] = -0.15f;
    sectors[2].rightdown[1] = -2.15f;
    sectors[3].leftdown[0] = -0.15f;
    sectors[3].leftdown[1] = -2.15f;
    sectors[3].rightdown[0] = -4.f;
    sectors[3].rightdown[1] = -2.15f;
    sectors[3].leftup[0] = -0.15f;
    sectors[3].leftup[1] = 1.15f;
    sectors[3].rightup[0] = -1.30f;
    sectors[3].rightup[1] = 1.15f;*/
    /*sectors[0].rightdown[0] = -0.15f;
    sectors[0].rightdown[1] = -0.15f;
    sectors[0].rightup[0] = -0.15f;
    sectors[0].rightup[1] = 19.85f;
    sectors[0].leftdown[0] = 9.85f;
    sectors[0].leftdown[1] = -0.15f;
    sectors[0].leftup[0] = 9.85f;
    sectors[0].leftup[1] = 19.85f;
    sectors[1].rightdown[0] = 0.85f;
    sectors[1].rightdown[1] = 19.85f;
    sectors[1].rightup[0] = 0.85f;
    sectors[1].rightup[1] = 24.85f;
    sectors[1].leftdown[0] = 9.85f;
    sectors[1].leftdown[1] = 19.85f;
    sectors[1].leftup[0] = 9.85f;
    sectors[1].leftup[1] = 24.85f;
    sectors[2].rightdown[0] = 0.85f;
    sectors[2].rightdown[1] = 24.85f;
    sectors[2].rightup[0] = 0.85f;
    sectors[2].rightup[1] = 34.85f;
    sectors[2].leftdown[0] = 5.85f;
    sectors[2].leftdown[1] = 24.85f;
    sectors[2].leftup[0] = 5.85f;
    sectors[2].leftup[1] = 34.85f;
    sectors[3].rightdown[0] = 0.85f;
    sectors[3].rightdown[1] = 36.85f;
    sectors[3].rightup[0] = 0.85f;
    sectors[3].rightup[1] = 51.85f;
    sectors[3].leftdown[0] = 5.85f;
    sectors[3].leftdown[1] = 36.85f;
    sectors[3].leftup[0] = 5.85f;
    sectors[3].leftup[1] = 51.85f;
    sectors[4].rightdown[0] = 0.85f;
    sectors[4].rightdown[1] = 34.85f;
    sectors[4].rightup[0] = 0.85f;
    sectors[4].rightup[1] = 36.85f;
    sectors[4].leftdown[0] = 9.85f;
    sectors[4].leftdown[1] = 34.85f;
    sectors[4].leftup[0] = 9.85f;
    sectors[4].leftup[1] = 36.85f;
    sectors[5].rightdown[0] = 6.85f;
    sectors[5].rightdown[1] = 36.85f;
    sectors[5].rightup[0] = 6.85f;
    sectors[5].rightup[1] = 51.85f;
    sectors[5].leftdown[0] = 8.85f;
    sectors[5].leftdown[1] = 36.85f;
    sectors[5].leftup[0] = 8.85f;
    sectors[5].leftup[1] = 51.85f;
    sectors[6].rightdown[0] = 6.85f;
    sectors[6].rightdown[1] = 24.85f;
    sectors[6].rightup[0] = 6.85f;
    sectors[6].rightup[1] = 34.85f;
    sectors[6].leftdown[0] = 8.85f;
    sectors[6].leftdown[1] = 24.85f;
    sectors[6].leftup[0] = 8.85f;
    sectors[6].leftup[1] = 34.85f;*/
    sectors[0].rightdown[0] = 1.f;
    sectors[0].rightdown[1] = 0.f;
    sectors[0].rightup[0] = 1.f;
    sectors[0].rightup[1] = 0.5f;
    sectors[0].leftdown[0] = 0.f;
    sectors[0].leftdown[1] = 0.f;
    sectors[0].leftup[0] = 0.f;
    sectors[0].leftup[1] = 0.5f;
    sectors[1].rightdown[0] = 1.5f;
    sectors[1].rightdown[1] = 0.f;
    sectors[1].rightup[0] = 1.5f;
    sectors[1].rightup[1] = 1.f;
    sectors[1].leftdown[0] = 1.f;
    sectors[1].leftdown[1] = 0.f;
    sectors[1].leftup[0] = 1.f;
    sectors[1].leftup[1] = 1.f;
    sectors[2].rightdown[0] = 1.f;
    sectors[2].rightdown[1] = 0.5f;
    sectors[2].rightup[0] = 1.f;
    sectors[2].rightup[1] = 1.f;
    sectors[2].leftdown[0] = 0.f;
    sectors[2].leftdown[1] = 0.5f;
    sectors[2].leftup[0] = 0.f;
    sectors[2].leftup[1] = 1.f;




}

int     dotting::nearestCorner(Sector &sector)
{
    double range[4];
    auto i = dots.rbegin();

    if (dots.size() == 0)
    {
        range[0] = LENGTH(sector.leftup);
        range[1] = LENGTH(sector.leftdown);
        range[2] = LENGTH(sector.rightup);
        range[3] = LENGTH(sector.rightdown);

        if (range[0] <= range[1] && range[0] <= range[2] && range[0] <= range[3])
            return corners::LEFTUP;
        else if (range[1] <= range[0] && range[1] <= range[2] && range[1] <= range[3])
            return corners::LEFTDOWN;
        else if (range[2] <= range[1] && range[2] <= range[0] && range[2] <= range[3])
            return corners::RIGHTUP;
        else if (range[3] <= range[1] && range[3] <= range[2] && range[3] <= range[0])
            return corners::RIGHTDOWN;
    }
    else
    {
        range[0] = LENGTH(sector.leftup - *i);
        range[1] = LENGTH(sector.leftdown - *i);
        range[2] = LENGTH(sector.rightup - *i);
        range[3] = LENGTH(sector.rightdown - *i);

        if (range[0] <= range[1] && range[0] <= range[2] && range[0] <= range[3])
            return corners::LEFTUP;
        else if (range[1] <= range[0] && range[1] <= range[2] && range[1] <= range[3])
            return corners::LEFTDOWN;
        else if (range[2] <= range[1] && range[2] <= range[0] && range[2] <= range[3])
            return corners::RIGHTUP;
        else if (range[3] <= range[1] && range[3] <= range[2] && range[3] <= range[0])
            return corners::RIGHTDOWN;
    }

}

void    dotting::direction(vector<double> &src, vector<double> &dest)
{
    double lenght;

    lenght = LENGTH(src);
    dest = src / lenght;
}

double  dotting::angle(vector<double> &v1, vector<double> &v2)
{
    double v3;
    vector<double> v11(2);
    vector<double> v22(2);

    v3 = norm_2(v1);
    v11 = v1 / v3;
    v3 = norm_2(v2);
    v22 = v2 / v3;
    v3 = inner_prod(v22,v11);
    return v3;
}

bool    dotting::downdots(vector<double> &dot, vector<double> &down, vector<double> &nearest, vector<double> &up, vector<double> &farest, vector<double> &start)
{
    vector<double> dirdown(2);
    vector<double> dirup(2);
    vector<double> dirnearest(2);
    vector<double> dirfarest(2);
    double lenghtdown;
    double lenghtup;
    double lenghtnearest;
    double lenghtfarest;
    double cos;
    double cos2;
    double cos3;

    direction(down, dirdown);
    direction(up, dirup);
    direction(nearest, dirnearest);
    direction(farest, dirfarest);
    lenghtdown = LENGTH(down);
    lenghtup = LENGTH(up);
    lenghtnearest = LENGTH(nearest);
    lenghtfarest = LENGTH(farest);

    if (dot[0] == start[0] && dot[1] == start[1])
    {
        dot = start;
        dots.push_back(dot);
    } else {
        coorddown += WIDTH;
        if (coorddown > lenghtdown) {
            cos = angle(down, farest);
            if (coorddown  > lenghtdown + lenghtfarest * cos)
                return true;
            dot = start + down + dirfarest * ((coorddown - lenghtdown) / cos);
            dots.push_back(dot);
        } else {
            dot = start + dirdown * coorddown;
            dots.push_back(dot);
        }
    }
        cos = angle(down, nearest);
        cos2 = angle(down, up);
        cos3 = angle( down, farest);
    if(cos3 < 0)
    {
        farest *= -1;
        cos3 = angle(down, farest);
        direction(farest, dirfarest);
    }
        if (coorddown < lenghtnearest * cos)
        {
            dot = start + dirnearest * (coorddown / cos);
            dots.push_back(dot);
        } else if((lenghtup * cos2 + lenghtnearest * cos) > coorddown)
        {
            dot = start + nearest;
            dot += dirup * ((coorddown - lenghtnearest * cos) / cos2);
            dots.push_back(dot);
        } else if (lenghtfarest * cos3 + lenghtup * cos2 + lenghtnearest * cos > coorddown)
        {
            dot = start + nearest + up + dirfarest * ((coorddown - lenghtnearest * cos - lenghtup * cos2) / cos3);
            dots.push_back(dot);
        } else
        {
            return true;
        }

    return false;
};

bool        dotting::updots(vector<double> &dot, vector<double> &down, vector<double> &nearest, vector<double> &up, vector<double> &farest, vector<double> &start)
{
    vector<double> dirdown(2);
    vector<double> dirup(2);
    vector<double> dirnearest(2);
    vector<double> dirfarest(2);
    double lenghtdown;
    double lenghtup;
    double lenghtnearest;
    double lenghtfarest;
    double cos;
    double cos2;
    double cos3;

    direction(down, dirdown);
    direction(up, dirup);
    direction(nearest, dirnearest);
    direction(farest, dirfarest);
    lenghtdown = LENGTH(down);
    lenghtup = LENGTH(up);
    lenghtnearest = LENGTH(nearest);
    lenghtfarest = LENGTH(farest);


    coorddown += WIDTH;

    cos = angle(down, nearest);
    cos2 = angle(down, up);
    cos3 = angle( down, farest);
    if(cos3 < 0)
    {
        farest *= -1;
        cos3 = angle(down, farest);
        direction(farest, dirfarest);
    }
    if (coorddown < lenghtnearest * cos)
    {
        dot = start + dirnearest * (coorddown / cos);
        dots.push_back(dot);
    } else if((lenghtup * cos2 + lenghtnearest * cos) > coorddown)
    {
        dot = start + nearest + dirup * ((coorddown - lenghtnearest * cos) / cos2);
        dots.push_back(dot);
    } else if (lenghtfarest * cos3 + lenghtup * cos2 + lenghtnearest * cos > coorddown)
    {
        dot = start + nearest + up + dirfarest * ((coorddown - lenghtnearest * cos - lenghtup * cos2) / cos3);
        dots.push_back(dot);
    } else
    {
        return true;
    }
    if (coorddown > lenghtdown)
    {
        cos = angle(down, farest);
        if (coorddown  > lenghtdown + lenghtfarest * cos)
            return true;
        dot = start + down + dirfarest * ((coorddown - lenghtdown) / cos);
        dots.push_back(dot);
    } else
    {
        dot = start + dirdown * coorddown;
        dots.push_back(dot);
    }
    return false;

}


void    dotting::createWay(Sector &sector)
{
    int corner;
    vector<double> left(2);
    vector<double> down(2);
    vector<double> up(2);
    vector<double> right(2);
    vector<double> dot(2);
    Sector copysector;
    corner = nearestCorner(sector);
    left = sector.leftdown - sector.leftup;
    direction(left, left);
    up = sector.rightup - sector.leftup;
    direction(up, up);
    copysector.leftup = sector.leftup + left * WIDTH + up * WIDTH;
    down = sector.rightdown - sector.leftdown;
    direction(down, down);
    copysector.leftdown = sector.leftdown + down * WIDTH + left * -WIDTH;
    right = sector.rightdown - sector.rightup;
    direction(right, right);
    copysector.rightup = sector.rightup + right * WIDTH + up * -WIDTH;
    copysector.rightdown = sector.rightdown + left * -WIDTH + down * -WIDTH;

    switch (corner) {
        case corners::LEFTUP :
            right = copysector.leftdown - copysector.leftup;
            down = copysector.rightup - copysector.leftup;
            up = copysector.rightdown - copysector.leftdown;
            left = copysector.rightdown - copysector.rightup;
            dot = copysector.leftup;
            while (true)
            {
                if (downdots(dot, down, right, up, left, copysector.leftup))
                    break;
                else if(updots(dot, down, right, up, left, copysector.leftup))
                    break;
            }
            break;
        case corners::LEFTDOWN :
            right = copysector.rightup - copysector.rightdown;
            down = copysector.rightdown - copysector.leftdown;
            up = copysector.rightup - copysector.leftup;
            left = copysector.leftup - copysector.leftdown;
            dot = copysector.leftdown;
            if (LENGTH(down) < LENGTH(left))
            {
                while (true)
                {
                    if (downdots(dot, down, left, up, right, copysector.leftdown))
                        break;
                    else if(updots(dot, down, left, up, right, copysector.leftdown))
                        break;
                }
            } else
            {
                while (true)
                {
                    if (downdots(dot, left, down, right, up, copysector.leftdown))
                        break;
                    else if(updots(dot, left, down, right, up, copysector.leftdown))
                        break;
                }
            }
            /*while (true)
            {
                if (downdots(dot, down, left, up, right, copysector.leftdown))
                    break;
                else if(updots(dot, down, left, up, right, copysector.leftdown))
                    break;
            }*/

            break;
        case corners::RIGHTDOWN :
            right = copysector.rightup - copysector.rightdown;
            down = copysector.leftdown - copysector.rightdown;
            up = copysector.leftup - copysector.rightup;
            left = copysector.leftup - copysector.leftdown;
            dot = copysector.rightdown;
            if (LENGTH(down) < LENGTH(right))
            {
                while (true)
                {
                    if (downdots(dot, down, right, up, left, copysector.rightdown))
                        break;
                    else if(updots(dot, down, right, up, left, copysector.rightdown))
                        break;
                }
            } else
            {
                while (true)
                {
                    if (downdots(dot, right, up, left, down, copysector.rightdown))
                        break;
                    else if(updots(dot, right, up, left, down, copysector.rightdown))
                        break;
                }
            }


            break;
        case corners::RIGHTUP :
            right = copysector.leftdown - copysector.leftup;
            down = copysector.leftup - copysector.rightup;
            up = copysector.leftdown - copysector.rightdown;
            left = copysector.rightdown - copysector.rightup;
            dot = copysector.rightup;
            if (LENGTH(down) < LENGTH(left))
            {
                while (true)
                {
                    if (downdots(dot, down, left, up, right, copysector.rightup))
                        break;
                    else if(updots(dot, down, left, up, right, copysector.rightup))
                        break;
                }
            } else
            {
                while (true)
                {
                    if (downdots(dot, left, up, right, down, copysector.rightup))
                        break;
                    else if(updots(dot, left, up, right, down, copysector.rightup))
                        break;
                }
            }

            break;
    }
    /*for (auto j = dots.begin(); j != dots.end(); j++)
    {
        std::cout << *j << std::endl;
    }*/
}

void    dotting::startdotting()
{
    vector<double> dot(2);
    algo::vector_array arr;
    algo::vector_msg msg;

    for (int i = 0; i != sectors.size(); i++)
    {
        coorddown = 0.f;
        if (i == 1)
        {
            dot[0] = 0.85;
            dot[1] = 0.25;
            dots.push_back(dot);
            dot[0] = 1.15;
            dot[1] = 0.25;
            dots.push_back(dot);
        } else if( i == 2)
        {
            dot[0] = 1.15;
            dot[1] = 0.75;
            dots.push_back(dot);
            dot[0] = 0.85;
            dot[1] = 0.75;
            dots.push_back(dot);
        }
        createWay(sectors[i]);
    }
    visualization_msgs::Marker line_list, points_list;
    line_list.header.frame_id = "/my_frame";
    line_list.header.stamp = ros::Time::now();
    line_list.ns = "points_and_lines";
    line_list.action = visualization_msgs::Marker::ADD;
    line_list.pose.orientation.w = 1.0;
    line_list.id = 0;
    line_list.type = visualization_msgs::Marker::LINE_LIST;
    line_list.scale.x = 0.05;
    line_list.color.g = 1.0;
    line_list.color.a = 1.0;
    points_list = line_list;
    points_list.id = 1;
    points_list.type = visualization_msgs::Marker::LINE_STRIP;
    points_list.color.b = 1.0;
    geometry_msgs::Point p;
    p.z = 0;
    for (int i = 0; i != sectors.size(); i++)
    {
        p.x = sectors[i].rightdown[0];
        p.y = sectors[i].rightdown[1];
        line_list.points.push_back(p);
        p.x = sectors[i].rightup[0];
        p.y = sectors[i].rightup[1];
        line_list.points.push_back(p);
        p.x = sectors[i].rightdown[0];
        p.y = sectors[i].rightdown[1];
        line_list.points.push_back(p);
        p.x = sectors[i].leftdown[0];
        p.y = sectors[i].leftdown[1];
        line_list.points.push_back(p);
        p.x = sectors[i].leftdown[0];
        p.y = sectors[i].leftdown[1];
        line_list.points.push_back(p);
        p.x = sectors[i].leftup[0];
        p.y = sectors[i].leftup[1];
        line_list.points.push_back(p);
        p.x = sectors[i].leftup[0];
        p.y = sectors[i].leftup[1];
        line_list.points.push_back(p);
        p.x = sectors[i].rightup[0];
        p.y = sectors[i].rightup[1];
        line_list.points.push_back(p);
    }
    for (auto i = dots.begin(); i != dots.end(); i++)
    {
        p.x = (*i)[0];
        p.y = (*i)[1];
        points_list.points.push_back(p);
    }

    for (auto j = dots.begin(); j != dots.end(); j++)
    {
        msg.x = (*j)[0];
        msg.x = (*j)[1];
        arr.vec.push_back(msg);
        std::cout << *j << std::endl;
    }
    pubdots.publish(arr);

    while (true)
    {
        marker_pub.publish(line_list);
        marker_pub.publish(points_list);
    }

}

int     main(int ac, char** av)
{
    dotting *dot;
    ros::init(ac, av, "ObjectFromLaser");
    ros::NodeHandle n;
    dot = new dotting(&n);
    dot->startdotting();
    ros::spin();
}