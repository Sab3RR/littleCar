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

     boost::split(arr, msg->data, boost::is_any_of(","));
     new_msg.data = std::atof((arr[2].c_str()));
     if (calibrated == -1)
     {
         calibrated = new_msg.data;
     }
     new_msg.data = new_msg.data - calibrated;

     pubC.publish(new_msg);
}
   /* static tf2_ros::TransformBroadcaster br;
    tf2::Quaternion quat_tf;
    geometry_msgs::TransformStamped quat_msg;

    quat_msg.header.stamp = ros::Time::now();
    quat_msg.header.frame_id = "world";
    quat_msg.child_frame_id = "compas";
    quat_msg.transform.translation.x = 0;
    quat_msg.transform.translation.y = 0;
    quat_msg.transform.translation.z = 0;
    quat_msg.transform.rotation.x = msg->orientation.x;
    quat_msg.transform.rotation.y = msg->orientation.y;
    quat_msg.transform.rotation.z = msg->orientation.z;
    quat_msg.transform.rotation.w = msg->orientation.w;
    br.sendTransform(quat_msg);*/

//}

int main(int ac, char** av)
{
    compas *Compas;
    ros::init(ac, av, "compas");
    ros::NodeHandle n;
    Compas = new compas(&n);
    ros::spin();
}