#ifndef robot_H 
#define robot_H

#include <LibRobus.h>

class robot
{
public:
    robot();

    void move(float distance);
    void rotate(float degree);
};

#endif