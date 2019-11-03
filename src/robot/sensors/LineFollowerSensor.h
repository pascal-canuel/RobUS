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
    int leftSensorPin = 40;
    int centerSensorPin = 44;
    int rightSensorPin = 42;

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
    void followline(char color_To)
    {
        Sensors sensors;
        leftval = sensors.leftval;
        centerval = sensors.centerVal;
        rightval = sensors.rightval;
        Serial.print("Leftval : ");Serial.print(leftVal);Serial.print("\tRightval : ");Serial.print(rightVal);;Serial.print("\tcenterval : ");Serial.println(centerVal);
        if (!leftVal && !centerVal && !rightVal && color_To == robus.readColor()) {
        MOTOR_SetSpeed(1,0); 
        MOTOR_SetSpeed(0,0);
        }
        if (leftVal==1) { 
        Serial.println("Good if left");
        vitesse = 0.2;
        vitesse1 = 0.17;
        } else if (centerVal==1) {
        Serial.println("Good if center");
        vitesse = 0.3;
        vitesse1 = 0.3;
        } else if (rightVal==1) {
        Serial.println("Good if right");
        vitesse = 0.17;
        vitesse1 = 0.2;
        }

        Serial.print("vitesse : ");Serial.print(vitesse);Serial.print("\tvitesse1 : ");Serial.println(vitesse1);
        MOTOR_SetSpeed(1,vitesse);
        MOTOR_SetSpeed(0,vitesse1);
    }
};

#endif