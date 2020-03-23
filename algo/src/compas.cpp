//
// Created by sab3r on 23.03.20.
//

#include "compas.h"

compas::compas(ros::NodeHandle *n)
{
    subC = n->subscribe("compas", 100, &compas::toFloat, this);
    pubC = n->advertise<std_msgs::Float64>("Fcompas", 100);
}

void compas::toFloat(const std_msgs::String::ConstPtr& msg)
{
    std::vector<std::string> arr;
    std_msgs::Float64 new_msg;

    boost::split(arr, msg->data, boost::is_any_of(" "));
    new_msg.data = std::atof(arr[2].c_str());
    pubC.publish(new_msg);
}

int main(int ac, char** av)
{
    compas *Compas;
    ros::init(ac, av, "motor");
    ros::NodeHandle n;
    Compas = new compas(&n);
    ros::spin();
}