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
    float _pidDelay;

    Robot() {
        _leftMotor = Motor(0);
        _rightMotor = Motor(1);

        _pidDelay = 500;
        _pid = PID(_pidDelay, 0.1, 0.065);
    }

    void rotate(float degree) {
        Motor motor = _leftMotor;
        if (degree > 0) 
            motor = _rightMotor;

        float distanceToReach = convertDegreeToDistance(degree);
        float pulseToReach = convertDistanceToPulse(distanceToReach);

        motor.setSpeed(DEFAULT_SPEED);
        while (motor.readEncoder() <= pulseToReach) {}

        motor.stop();
    }

    void turn(float degree) {
        degree /= 2;
        Motor motor = _leftMotor;
        Motor reverseMotor = _rightMotor;
        if (degree > 0) {
            motor = _rightMotor;
            reverseMotor = _leftMotor;
        }

        float distanceToReach = convertDegreeToDistance(degree);
        float pulseToReach = convertDistanceToPulse(distanceToReach);

        motor.setSpeed(DEFAULT_SPEED);
        reverseMotor.setSpeed(-DEFAULT_SPEED);

        while (motor.readEncoder() <= pulseToReach && reverseMotor.readEncoder() * -1 <= pulseToReach) {}

        motor.stop();
        reverseMotor.stop();
    }

    void move(float distance) {
        float pulseToReach = convertDistanceToPulse(distance);
        int direction = 1;
        if (distance < 0)
            direction = -1;

        int32_t leftPulse;
        int32_t rightPulse;
        _leftMotor.setSpeed(DEFAULT_SPEED * direction);
        _rightMotor.setSpeed(DEFAULT_SPEED * direction);

        unsigned currentMillis = millis();
        unsigned previousMillis = 0;
        do
        {
            leftPulse = _leftMotor.readEncoder();
            rightPulse = _rightMotor.readEncoder();

            currentMillis = millis();
            if (currentMillis - previousMillis > _pidDelay) {
                previousMillis = currentMillis;
                float magic = _pid.Compute(leftPulse, rightPulse);
                _rightMotor.setSpeed(DEFAULT_SPEED + magic);
            }

        } while (leftPulse * direction <= pulseToReach && rightPulse * direction <= pulseToReach);

        _leftMotor.stop();
        _rightMotor.stop();
    }

    void reset() {
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
    }

    void stop() {
        _leftMotor.stop();
        _rightMotor.stop();
    }
};

#endif