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
    int leftSensorPin = 38;
    int centerSensorPin = 40;
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
    void followline(Color color_To, Color color)
    {
        Sensors sensors = read();

        int _leftVal = sensors.leftVal;
        int _centerVal = sensors.centerVal;
        int _rightVal = sensors.rightVal;

        Serial.print("Leftval : ");Serial.print(_leftVal);Serial.print("\tRightval : ");Serial.print(_rightVal);;Serial.print("\tcenterval : ");Serial.println(_centerVal);
        if (!_leftVal && !_centerVal && !_rightVal && color_To == color) {
       
        MOTOR_SetSpeed(1,0); 
        MOTOR_SetSpeed(0,0);
        }
        if (_leftVal==1) { 
        Serial.println("Good if left");
        
        MOTOR_SetSpeed(1,0.25);
        MOTOR_SetSpeed(0,0.15);
        } else if (_centerVal==1) {
        Serial.println("Good if center");
       
        MOTOR_SetSpeed(1,0.3);
        MOTOR_SetSpeed(0,0.3);
        } else if (_rightVal==1) {
        Serial.println("Good if right");
       
        MOTOR_SetSpeed(1,0.15);
        MOTOR_SetSpeed(0,0.25);
        }

       
       
    }
};

#endif