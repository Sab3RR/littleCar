//
// Created by sab3r on 22.06.2020.
//

#include "ManControll.h"

ManControll::ManControll(ros::NodeHandle *n)
{
    pubAr = n->advertise<std_msgs::Float64MultiArray>("MotorForce", 0);
}

int ManControll::getch()
{
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);           // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON);                 // disable buffering
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

    int c = getchar();  // read character (non-blocking)

    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
    return c;
}

int main(int ac, char** av)
{
    ManControll *cont;
    ros::init(ac, av, "mancontroll");
    ros::NodeHandle n;
    cont = new ManControll(&n);
    int last = 0;
    std_msgs::Float64MultiArray Ar;
    double f;
    Ar.data.push_back(f);
    Ar.data.push_back(f);
    while (ros::ok()) {
        int c = cont->getch();   // call your non-blocking input function
        if (c == 'w')
        {
            Ar.data[0] = SPEED;
            Ar.data[1] = SPEED;
            cont->pubAr.publish(Ar);
        }
        else if (c == 'd')
        {
            Ar.data[0] = SPEED;
            Ar.data[1] = 0;
            cont->pubAr.publish(Ar);
        }
        else if (c == 'a')
        {
            Ar.data[0] = 0;
            Ar.data[1] = SPEED;
            cont->pubAr.publish(Ar);
        }
        else
        {
            if (last == 'w' || last == 'a' || last == 'd')
            {
                Ar.data[0] = 0;
                Ar.data[1] = 0;
                cont->pubAr.publish(Ar);
            }
        }
        last = c;
        ros::spinOnce();
    }
}
