#ifndef Servo_H_
#define Servo_H_

#include <LibRobus.h>

struct Servo
{
    uint8_t _servoID;

    Servo() {}
    Servo(uint8_t servoID) {
        _servoID = servoID;
    }

    void init() {
        SERVO_Enable(_servoID);
        close();
    }

    void open() {
        SERVO_Enable(_servoID);
        SERVO_SetAngle(_servoID, 180);
    }

    void close() {
        SERVO_SetAngle(_servoID, 120);
        delay(100);
        SERVO_Disable(_servoID);
    }
};

#endif