#ifndef Robot_H_
#define Robot_H_

#include "Robot.Utils.h"

#include "parts/Motor.h"
#include "parts/Clamp.h"

#include "sensors/ColorSensor.h"
#include "sensors/DistanceSensor.h"
#include "sensors/LineFollowerSensor.h"

#include "PID.h"

struct Robot
{
    Motor _leftMotor;
    Motor _rightMotor;
    Clamp _clamp;

    ColorSensor _colorSensor;
    DistanceSensor _distanceSensor;
    LineFollowerSensor _lineFollowerSensor;

    PID _pid;
    float _pidDelay;

    Robot() {
        _leftMotor = Motor(0);
        _rightMotor = Motor(1);
        _clamp = Clamp(1);

        _colorSensor = ColorSensor();
        _distanceSensor = DistanceSensor();
        _lineFollowerSensor = LineFollowerSensor();
        
        _pidDelay = 100;
        _pid = PID(_pidDelay, 0.15, 0.05);
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
        
        forwardMotor.stop();
        reverseMotor.stop();
    }

    void move(float distance) {
        delay(1000);
        
        float pulseToReach = convertDistanceToPulse(distance);
        int direction = 1;
        if (distance < 0)
            direction = -1;

        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
        
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
#if __ROBUS__ == ROBUS_A
                    float magic = _pid.Compute(rightPulse, leftPulse);
                     _leftMotor.setSpeed((DEFAULT_SPEED + magic + 0.02) * direction);
#elif __ROBUS__ == ROBUS_B
                   float magic = _pid.Compute(leftPulse, rightPulse);
                   _rightMotor.setSpeed((DEFAULT_SPEED + magic) * direction);
#endif
                // Serial.print(leftPulse);
                // Serial.print(" | ");
                // Serial.println(rightPulse);
            }
        } while (leftPulse * direction <= pulseToReach && rightPulse * direction <= pulseToReach);

        _leftMotor.stop();
        _rightMotor.stop();

        _pid.reset();
    }

    void forwardBall() {
        delay(300);
        
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
        
        int32_t leftPulse;
        int32_t rightPulse;
        _leftMotor.setSpeed(DEFAULT_SPEED);
        _rightMotor.setSpeed(DEFAULT_SPEED);

        unsigned currentMillis = millis();
        unsigned previousMillis = 0;
        do
        {
            leftPulse = _leftMotor.readEncoder();
            rightPulse = _rightMotor.readEncoder();

            currentMillis = millis();
            if (currentMillis - previousMillis > _pidDelay) {
                previousMillis = currentMillis;

#if __ROBUS__ == ROBUS_A
                    float magic = _pid.Compute(rightPulse, leftPulse);
                     _leftMotor.setSpeed(DEFAULT_SPEED + magic + 0.02);
#elif __ROBUS__ == ROBUS_B
                   float magic = _pid.Compute(leftPulse, rightPulse);
                   _rightMotor.setSpeed(DEFAULT_SPEED + magic);
#endif
                // Serial.print(leftPulse);
                // Serial.print(" | ");
                // Serial.println(rightPulse);
            }
        } while(!Detection(13, 6));

        _pid.reset();

        delay(125);
        stop();
        closeClamp();
    }

    void forwardCenter() {
        delay(300);
        
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
        
        int32_t leftPulse;
        int32_t rightPulse;
        _leftMotor.setSpeed(DEFAULT_SPEED);
        _rightMotor.setSpeed(DEFAULT_SPEED);

        Sensors sensors = { 0, 0, 0 };

        unsigned currentMillis = millis();
        unsigned previousMillis = 0;
        do
        {
            leftPulse = _leftMotor.readEncoder();
            rightPulse = _rightMotor.readEncoder();

            currentMillis = millis();
            if (currentMillis - previousMillis > _pidDelay) {
                previousMillis = currentMillis;

#if __ROBUS__ == ROBUS_A
                    float magic = _pid.Compute(rightPulse, leftPulse);
                     _leftMotor.setSpeed(DEFAULT_SPEED + magic + 0.02);
#elif __ROBUS__ == ROBUS_B
                   float magic = _pid.Compute(leftPulse, rightPulse);
                   _rightMotor.setSpeed(DEFAULT_SPEED + magic);
#endif
                // Serial.print(leftPulse);
                // Serial.print(" | ");
                // Serial.println(rightPulse);
            }
            sensors = _lineFollowerSensor.read();
        } while(!(sensors.leftVal && sensors.centerVal && sensors.rightVal));

        _pid.reset();

        delay(50);
        stop();
        delay(500);
        openClamp();
    }

    bool Detection(int limiteMax, int limiteMin)
    {
        int val = 0;
        int distance = 0;

        val = analogRead(0);
        distance = (7960.9*pow(val,-1.094));

        Serial.println(distance);
        if(distance<limiteMax && distance>limiteMin)
            return true;
        else
            return false;
    }

    /*
        0 - yellow
        1 - green
        2 - blue
        3 - red
        4 - undefined
    */
    Color readColor() {
        return _colorSensor.read();
    }

    /*
        LEFT - CENTER - RIGHT
        0      0        1     Adjust to the right
        0      1        0     Ok
        1      0        0     Adjust to the left
        0      0        0     On a white space or color zone
    */
    void followLine() {
        Sensors sensors = _lineFollowerSensor.read();
        Serial.print("left: "); Serial.println(sensors.leftVal);
        Serial.print("center: "); Serial.println(sensors.centerVal);
        Serial.print("right: "); Serial.println(sensors.rightVal);

        float error = 0.03;

        Color color = readColor();
        Serial.print("init color: "); Serial.println(color);
        unsigned currentMillis = millis();
        unsigned initMillis = currentMillis;
        unsigned previousMillis = 0;

        _leftMotor.setSpeed(DEFAULT_SPEED);
        _rightMotor.setSpeed(DEFAULT_SPEED);

        while (color == UNDEFINED) {
            if (sensors.leftVal) {
                _leftMotor.setSpeed(DEFAULT_SPEED);
                _rightMotor.setSpeed(DEFAULT_SPEED + error);
            } else if (sensors.centerVal) {
                _leftMotor.setSpeed(DEFAULT_SPEED);
                _rightMotor.setSpeed(DEFAULT_SPEED);
            } else if (sensors.rightVal) {
                _leftMotor.setSpeed(DEFAULT_SPEED + error);
                _rightMotor.setSpeed(DEFAULT_SPEED);
            }

            currentMillis = millis();

            if (currentMillis - previousMillis > 50) {
                 previousMillis = currentMillis;
                 color = readColor();
                 Serial.print("caliss: "); Serial.println(color);
             }
             unsigned diffMillis = currentMillis - initMillis;
             Serial.print("diff millis: "); Serial.println(currentMillis - initMillis);
            if (!(sensors.leftVal && sensors.centerVal && sensors.rightVal) && diffMillis > 1000) {
                Serial.println("TBK");
                Serial.println(currentMillis);
                _leftMotor.stop();
                _rightMotor.stop();
                delay(100);
                color = readColor();
                if (color == UNDEFINED) {
                    _leftMotor.setSpeed(DEFAULT_SPEED);
                    _rightMotor.setSpeed(DEFAULT_SPEED);
                }
                Serial.print("sir path: "); Serial.println(color);
            }
        }
        
        _leftMotor.stop();
        _rightMotor.stop();
    }

    void initParts() {
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();

        _clamp.init();
    }

    void closeClamp() {
        _clamp.close();
    }

    void openClamp() {
        _clamp.open();
    }

    void initSensors() {
        _colorSensor.init();

        _lineFollowerSensor.init();
    }

    void init() {
        initParts();
        initSensors();
    }

    void stop() {
        _leftMotor.stop();
        _rightMotor.stop();
    }
};

#endif