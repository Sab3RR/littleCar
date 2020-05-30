//
// Created by sab3r on 22.03.20.
//

#include "Position.h"

void Position::Rwheel(const algo::Encoder_msg::ConstPtr& msg)
{
    algo::vector_msg vec;
    if (inited)
    {
        wheelR.x += dir.x * PERTICK;
        wheelR.y += dir.y * PERTICK;
        pos = {(wheelL.x - wheelR.x) / 2 + wheelR.x, (wheelL.y - wheelR.y) / 2 + wheelR.y};
        vec.x = pos.x;
        vec.y = pos.y;
       /* line_list.points[0].x = wheelR.x;
        line_list.points[0].y = wheelR.y;*/
        line_list.points[1].x = pos.x;
        line_list.points[1].y = pos.y;
        marker_pub.publish(line_list);
        pubpos.publish(vec);
    } else
    {
        if (msg->Speed > 0)
            inited = true;
    }
    /*double angle;
    double lenght;
    algo::vector_msg d;
    matrix<double> m(2,2);
    vector<double> help(2);
    vector<double> v(2);
    matrix<double> vv(2, 1);

    angle = PERTICK / W;
    help = wheelR - wheelL;
    v[0] = help[0] * cos(angle) + help[1] * -sin(angle);
    v[1] = help[0] * sin(angle) + help[1] * cos(angle);
    help = v;
    wheelR = wheelL + help;
    pos = wheelL + (help / 2);
    d.x = pos[0];
    d.y = pos[1];
    pubpos.publish(d);
    lenght = LENGTH(help);
    help /= lenght;
    d.x = -help[1];
    d.y = help[0];
    pubdir.publish(d);*/


}

void Position::Lwheel(const algo::Encoder_msg::ConstPtr& msg)
{
    algo::vector_msg vec;
    if (inited)
    {
        wheelL.x += dir.x * PERTICK;
        wheelL.y += dir.y * PERTICK;
        pos = {(wheelR.x - wheelL.x) / 2 + wheelL.x, (wheelR.y - wheelL.y) / 2 + wheelL.y};
        vec.x = pos.x;
        vec.y = pos.y;
        /*line_list.points[2].x = wheelL.x;
        line_list.points[2].y = wheelL.y;*/
        line_list.points[1].x = pos.x;
        line_list.points[1].y = pos.y;
        marker_pub.publish(line_list);
        pubpos.publish(vec);
    } else
    {
        if (msg->Speed > 0)
            inited = true;
    }
    /*double angle;
    double lenght;
    algo::vector_msg d;        line_list.points[0].x = vec.x;

    matrix<double> m(2,2);
    vector<double> help(2);
    vector<double> v(2);

    angle = PERTICK / -W;
    help = wheelL - wheelR;
    v[0] = help[0] * cos(angle) + help[1] * -sin(angle);
    v[1] = help[0] * sin(angle) + help[1] * cos(angle);
    help = v;
    wheelL = wheelR + help;
    pos = wheelR + (help / 2);
    d.x = pos[0];
    d.y = pos[1];
    pubpos.publish(d);
    lenght = LENGTH(help);
    help /= lenght;
    d.x = help[1];
    d.y = -help[0];
    pubdir.publish(d);*/
}

void Position::Compas(const std_msgs::Float64::ConstPtr& msg)
{
    algo::vector_msg vec;
    float rad;
    rad = (float)(msg->data) * (float)(M_PI / 180);
    if (dir.x == 0.f && dir.y == 0.f)
    {

        dir.x = cosf(rad);
        dir.y = sinf(rad);
        vec.x = dir.x;
        vec.y = dir.y;
        pubdir.publish(vec);
        wheelR = {static_cast<float>(-dir.y * W / 2), static_cast<float>(dir.x * W / 2)};
        wheelL = {static_cast<float>(dir.y * W / 2), static_cast<float>(-dir.x * W / 2)};
    } else
    {
        dir.x = cosf(rad);
        dir.y = sinf(rad);
        vec.x = dir.x;
        vec.y = dir.y;
        arrow.points[0].x = pos.x;
        arrow.points[0].y = pos.y;
        arrow.points[1].x = pos.x + (dir.x * 0.5);
        arrow.points[1].y = pos.y + (dir.y * 0.5);

        marker_pub.publish(arrow);
        marker_pub.publish(line_list);
        pubdir.publish(vec);

    }


}


/*void Position::SetMinPower()
{
    float   power = 0;
    bool    rwheel = true;
    std_msgs::Float64MultiArray Ar;

    Ar.data.push_back(power);
    Ar.data.push_back(power);
    while (ros::ok())
    {
        if (inited)
        {
            if (rwheel)
            {
                Ar.data[0] = 0;
                Ar.data[1] = 0;
                pubAr.publish(Ar);
                sleep(1);
                rwheel = false;
                if (MinPowerToStart < power)
                    MinPowerToStart = power;
                power = 0;
                ros::spinOnce();
                inited = false;
            } else
            {
                Ar.data[0] = 0;
                Ar.data[1] = 0;
                pubAr.publish(Ar);
                if (MinPowerToStart < power)
                    MinPowerToStart = power;
                break;
            }
        }
        if (rwheel)
        {
            Ar.data[0] = power;
            Ar.data[1] = 0;
            pubAr.publish(Ar);
            ros::spinOnce();
        } else
        {
            Ar.data[0] = 0;
            Ar.data[1] = power;
            pubAr.publish(Ar);
            ros::spinOnce();
        }
        sleep(1);
        power += 0.02;
    }
}*/
Position::Position(ros::NodeHandle *n)
{
    subR = n->subscribe("SpeedAndWayR", 0, &Position::Rwheel, this);
    subL = n->subscribe("SpeedAndWayL", 0, &Position::Lwheel, this);
    subC = n->subscribe("Fcompas", 1, &Position::Compas, this);
    marker_pub = n->advertise<visualization_msgs::Marker>("visualization_marker", 10);
    pubpos = n->advertise<algo::vector_msg>("position", 1);
    pubdir = n->advertise<algo::vector_msg>("direction", 1);
    pubAr = n->advertise<std_msgs::Float64MultiArray>("MotorForce", 10);
    line_list.header.frame_id = "/my_frame";
    line_list.header.stamp = ros::Time::now();
    line_list.ns = "points_and_lines";
    line_list.action = visualization_msgs::Marker::ADD;
    line_list.pose.orientation.w = 1.0;
    line_list.id = 2;
    line_list.type = visualization_msgs::Marker::POINTS;
    line_list.scale.x = 0.05;
    line_list.scale.y = 0.05;
    line_list.color.a = 1.0;
    line_list.color.r = 1.0;
    arrow.header.frame_id = "/my_frame";
    arrow.header.stamp = ros::Time::now();
    arrow.ns = "points_and_lines";
    arrow.action = visualization_msgs::Marker::ADD;
    arrow.pose.orientation.w = 1.0;
    arrow.id = 3;
    arrow.type = visualization_msgs::Marker::ARROW;
    arrow.scale.x = 0.1;
    arrow.scale.y = 0.1;
    arrow.color.a = 1.0;
    arrow.color.r = 1.0;
    geometry_msgs::Point p;
    p.z = 0;
    p.x = 0;
    p.y = 0;
    line_list.points.push_back(p);
    line_list.points.push_back(p);
    line_list.points.push_back(p);
    arrow.points.push_back(p);
    arrow.points.push_back(p);


    /*pos[0] = 0.f;
    pos[1] = 0.f;
    dir[0] = 1.f;
    dir[1] = 0.f;
    wheelR[0] = dir[1] * W / 2;
    wheelR[1] = -dir[0] * W / 2;

    wheelL[0] = -dir[1] * W / 2;
    wheelL[1] = dir[0] * W / 2;*/

    sleep(1);

}


int main(int ac, char** av)
{
    Position *pos;
    ros::init(ac, av, "position");
    ros::NodeHandle n;
    pos = new Position(&n);


   // pos->SetMinPower();
    ros::spin();
    return 0;
}