#ifndef robot_H 
#define robot_H

#include <LibRobus.h>


enum MotorId {
    LEFT_MOTOR = 0,
    RIGHT_MOTOR = 1,
    BOTH_MOTOR = 2,
};



class Robot
{
public:
    Robot();

    void setSpeed(MotorId motorId, float speed);
    void move(float distance);
    void rotate(float degree, float Motor_ID);
};

#endif