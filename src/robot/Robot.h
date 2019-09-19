#ifndef robot_H 
#define robot_H

#include <LibRobus.h>

enum BumperPin {
    LEFT_BUMPER = 27,
    RIGHT_BUMPER = 29,
    FRONT_BUMPER = 26,
    REAR_BUMPER = 28
};

enum MotorId {
    LEFT_MOTOR = 0,
    RIGHT_MOTOR = 1,
    BOTH_MOTOR = 2,
};

float WHEEL_RADIUS = 3.81;
float WHEEL_CIRCUMFERENCE = 2*PI*WHEEL_RADIUS;
float WHEEL_TOUR_PULSE = 3200;

class Robot
{
public:
    Robot();

    void setSpeed(MotorId motorId, float speed);
    void move(float distance);
    void rotate(float degree);
};

#endif