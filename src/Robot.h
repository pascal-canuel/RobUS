#ifndef Robot_H_
#define Robot_H_

#include "Motor.h"

const float ROBUS_WIDTH = 18.75;
const float ROBUS_CIRCUMFERENCE = 2*PI*ROBUS_WIDTH;

const float WHEEL_RADIUS = 3.81;
const float WHEEL_CIRCUMFERENCE = 2*PI*WHEEL_RADIUS;
const float WHEEL_TOUR_PULSE = 3200;

const float DEFAULT_SPEED = 0.2;

struct Robot
{
    Motor _motor;

    Robot() {
        BoardInit();
        _motor = Motor();

        delay(1000);
    }

    int32_t convertDegreeToDistance(float degree) {
        return abs((degree/360) * ROBUS_CIRCUMFERENCE);
    }

    int32_t convertDistanceToPulse(float distance) {
        return abs((distance/WHEEL_CIRCUMFERENCE) * WHEEL_TOUR_PULSE);
    }

    void rotate(float degree) {
        MotorId motorId = LEFT_MOTOR;
        if(degree > 0) 
            motorId = RIGHT_MOTOR;

        float distanceToReach = convertDegreeToDistance(degree);
        float pulseToReach = convertDistanceToPulse(distanceToReach);

        _motor.setSpeed(motorId, DEFAULT_SPEED);
        while (_motor.readEncoder(motorId) < pulseToReach) {}

        _motor.setSpeed(motorId, 0);
        _motor.resetEncoder(motorId);
    }

    void move(float distance) {
        float pulseToReach = convertDistanceToPulse(distance);

        _motor.setSpeed(BOTH_MOTOR, DEFAULT_SPEED);
        while (_motor.readEncoder(LEFT_MOTOR) < pulseToReach && _motor.readEncoder(RIGHT_MOTOR) < pulseToReach) {}
        
        _motor.setSpeed(BOTH_MOTOR, 0);
        _motor.resetEncoder(BOTH_MOTOR);
    }
};

#endif