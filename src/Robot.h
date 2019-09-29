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
        Serial.println(pulseToReach);

        _leftMotor.setSpeed(DEFAULT_SPEED);
        _rightMotor.setSpeed(DEFAULT_SPEED);

        int32_t leftPulse;
        int32_t rightPulse;
        do
        {
            leftPulse = _leftMotor.readEncoder();
            rightPulse = _rightMotor.readEncoder();

           // float magic = _pid.Compute(leftPulse, rightPulse);
           // Serial.println(magic);
           // _rightMotor.addSpeed(DEFAULT_SPEED + magic);

            Serial.print("Left motor | Pulse ");
            Serial.println(leftPulse);
            Serial.print("Right motor | Pulse ");
            Serial.println(rightPulse);
        } while (leftPulse < pulseToReach && rightPulse < pulseToReach);
        
        _leftMotor.stop();
        _rightMotor.stop();
    }

    void reset() {
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
    }
};

#endif