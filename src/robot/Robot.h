#ifndef Robot_H_
#define Robot_H_

#include "Robot.Utils.h"
#include "actuators/Motor.h"
#include "sensors/ReflectanceArray.h"
#include "sensors/RFID.h"
#include "PID.h"

struct Robot
{
    Motor _leftMotor;
    Motor _rightMotor;

    ReflectanceArray _reflectanceArray;
    RFID _rfid;
    
    PID _pid;
    float _pidDelay;

    Robot() {
        _leftMotor = Motor(0);
        _rightMotor = Motor(1);
    
        _reflectanceArray = ReflectanceArray();
        _rfid = RFID();

        _pidDelay = 100;
        _pid = PID(_pidDelay, 0.20, 0.01);
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
        Motor forwardMotor = _leftMotor;
        Motor reverseMotor = _rightMotor;
        if (degree > 0) {
            forwardMotor = _rightMotor;
            reverseMotor = _leftMotor;
        }

        float distanceToReach = convertDegreeToDistance(degree);
        float pulseToReach = convertDistanceToPulse(distanceToReach);

        forwardMotor.setSpeed(DEFAULT_SPEED);
        reverseMotor.setSpeed(-DEFAULT_SPEED);

        int32_t forwardPulse;
        int32_t reversePulse;
        do
        {
            forwardPulse = forwardMotor.readEncoder();
            reversePulse = reverseMotor.readEncoder();

            if (forwardPulse >= pulseToReach)
                forwardMotor.setSpeed(0);
            if (reversePulse <= -pulseToReach)
                reverseMotor.setSpeed(0);
        } while (forwardPulse < pulseToReach || reversePulse > -pulseToReach);
        
        stop();
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
                     _leftMotor.setSpeed((DEFAULT_SPEED + magic + 0.02) * direction);
                #else
                   float magic = _pid.Compute(leftPulse, rightPulse);
                   _rightMotor.setSpeed((DEFAULT_SPEED + magic) * direction);
                #endif
                // Serial.print(leftPulse);
                // Serial.print(" | ");
                // Serial.println(rightPulse);
            }
        } while (leftPulse * direction <= pulseToReach && rightPulse * direction <= pulseToReach);

        stop();
        _pid.reset();
    }

    void followLine(int targetTagValue) 
    {
        while (true)
        {
            int* array = _reflectanceArray.read();
            Serial.print(array[0]); Serial.print(" | "); Serial.print(array[1]); Serial.print(" | ");Serial.print(array[2]); Serial.print(" | "); Serial.print(array[3]); Serial.print(" | "); Serial.print(array[4]); Serial.print(" | "); Serial.print(array[5]); Serial.print(" | "); Serial.print(array[6]); Serial.print(" | "); Serial.println(array[7]);
            float error = array[0] * 40 + array[1] * 30 + array[2] * 20 + array[3] * 10 + 
                array[4] * -10 + array[5] * -20 + array[6] * -30 + array[7] * -40;
            Serial.print("error: "); Serial.println(error);
            delay(500);
            delete array;
        }
        // while (_rfid.read() != targetTagValue)
        // {
        //     delay(100);
        // }
    }

    void initParts() {
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
    }

    void initSensors() {
        _rfid.init();
    }

    void init() {
        initParts();
        initSensors();
    }

    void stop() {
        _leftMotor.stop();
        _rightMotor.stop();
        delay(500); // inertia
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
    }
};

#endif