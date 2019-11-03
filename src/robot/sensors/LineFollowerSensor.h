#ifndef LineFollowerSensor_H_
#define LineFollowerSensor_H_

#include <Arduino.h>

/*
    0 = LOW
    1 = HIGH
*/
struct Sensors {
    int leftVal, centerVal, rightVal;
};

struct LineFollowerSensor
{
    int leftSensorPin = 30;
    int centerSensorPin = 32;
    int rightSensorPin = 34;

    LineFollowerSensor() {}

    void init() {
        pinMode(leftSensorPin, INPUT);
        pinMode(centerSensorPin, INPUT);
        pinMode(rightSensorPin, INPUT);
    }

    Sensors read() {
        int leftSensorVal = digitalRead(leftSensorPin);
        int centerSensorVal = digitalRead(centerSensorPin);
        int rightSensorVal = digitalRead(rightSensorPin);

        // Serial.print("left: "); Serial.println(leftSensorVal);
        // Serial.print("center: "); Serial.println(centerSensorVal);
        // Serial.print("right: "); Serial.println(rightSensorVal);

        return Sensors { leftSensorVal, centerSensorVal, rightSensorVal };
    }
};

#endif