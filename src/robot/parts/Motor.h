#ifndef Motor_H_
#define Motor_H_

#include <LibRobus.h>

struct Motor
{
    uint8_t _motorId;
    float _currentSpeed;

    Motor() {}
    Motor(uint8_t motorId) {
        _motorId = motorId;
    }

    void resetEncoder() {
        ENCODER_Reset(_motorId);
    }

    int32_t readResetEncoder() {
        return ENCODER_ReadReset(_motorId);
    }

    int32_t readEncoder() {
        return ENCODER_Read(_motorId);
    }

    void setSpeed(float speed) {
        _currentSpeed = speed;
        MOTOR_SetSpeed(_motorId, _currentSpeed);
    }

    void addSpeed(float speed) {
        setSpeed(_currentSpeed + speed);
    }

    void stop() {
        setSpeed(0);
        delay(500); // stop inertia
        resetEncoder();
    }
};

#endif