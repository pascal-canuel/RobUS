#ifndef Clamp_H_
#define Clamp_H_

#include <LibRobus.h>

struct Clamp
{
    uint8_t _clampId;

    Clamp() {}
    Clamp(uint8_t clampId) {
        _clampId = clampId;
    }

    void init() {
        SERVO_Enable(_clampId);
        open();
    }

    void open() {
        SERVO_SetAngle(_clampId, 180);
    }

    void close() {
        #ifdef ROBUS_A
            SERVO_SetAngle(_clampId, 90);
        #else
            SERVO_SetAngle(_clampId, 120);
        #endif
    }
};

#endif