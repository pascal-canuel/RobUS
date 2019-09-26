#ifndef Robot_H_
#define Robot_H_

#include "Robot.Utils.h"
#include "Motor.h"

struct Robot
{
    Motor _leftMotor;
    Motor _rightMotor;

    Robot() {
        BoardInit();
        _leftMotor = Motor(LEFT_MOTOR);
        _rightMotor = Motor(RIGHT_MOTOR);

        delay(2000);
    }

    void rotate(float degree) {
        Motor motor = _leftMotor;
        if(degree > 0) 
            motor = _rightMotor;

        float distanceToReach = convertDegreeToDistance(degree);
        float pulseToReach = convertDistanceToPulse(distanceToReach);

        motor.setSpeed(DEFAULT_SPEED);
        while (motor.readEncoder() < pulseToReach) {}

        motor.stop();
    }

    void move(float distance) {
        float pulseToReach = convertDistanceToPulse(distance);
        Serial.println(pulseToReach);

        _leftMotor.setSpeed(DEFAULT_SPEED);
        _rightMotor.setSpeed(DEFAULT_SPEED);

        int32_t leftPulse;
        int32_t rightPulse;
        do
        {
            leftPulse = _leftMotor.readEncoder();
            rightPulse = _rightMotor.readEncoder();
        } while (leftPulse < pulseToReach && rightPulse < pulseToReach);
        
        _leftMotor.stop();
        _rightMotor.stop();
    }
};

#endif