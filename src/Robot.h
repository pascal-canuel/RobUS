#ifndef Robot_H_
#define Robot_H_

// comment to compile for robus b
#define ROBUS_A 

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

        #ifdef ROBUS_A
            _pid = PID(_pidDelay, 0.09, 0.08);
        #else
            _pid = PID(_pidDelay, 0.1, 0.065);
        #endif
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

                #ifdef ROBUS_A
                    float magic = _pid.Compute(rightPulse, leftPulse);
                    _leftMotor.setSpeed(DEFAULT_SPEED + magic);
                #else
                    float magic = _pid.Compute(leftPulse, rightPulse);
                    _rightMotor.setSpeed(DEFAULT_SPEED + magic);
                #endif
            }

        } while (leftPulse * direction <= pulseToReach && rightPulse * direction <= pulseToReach);

        _leftMotor.stop();
        _rightMotor.stop();

        _pid.reset();
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