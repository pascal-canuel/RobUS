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
    }

    void open() {
        // SERVO_SetAngle(_servoID, );
    }

    void close() {
        // SERVO_SetAngle(_servoID, );
    }
};

#endif