#ifndef Robot_H_
#define Robot_H_

#include "Robot.Utils.h"
#include "PID.h"
#include "Motor.h"

struct Robot
{
    Motor _leftMotor;
    Motor _rightMotor;
    PID _pid;
    
    Robot() {
        _leftMotor = Motor(0);
        _rightMotor = Motor(1);
        _pid = PID(2, 5, 1);
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
        int direction = 1;
        if(distance < 0)
            direction = -1;

        int32_t leftPulse;
        int32_t rightPulse;
        _leftMotor.setSpeed(DEFAULT_SPEED * direction);
        _rightMotor.setSpeed(DEFAULT_SPEED * direction);
        do
        {
            leftPulse = _leftMotor.readEncoder();
            rightPulse = _rightMotor.readEncoder();

            // float magic = _pid.Compute(leftPulse, rightPulse);
            // _rightMotor.addSpeed(DEFAULT_SPEED + magic);
        } while (leftPulse * direction < pulseToReach && rightPulse * direction < pulseToReach);

        _leftMotor.stop();
        _rightMotor.stop();
    }

    void reset() {
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
    }
};

#endif