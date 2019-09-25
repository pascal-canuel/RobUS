#ifndef Motor_H_
#define Motor_H_

#include <LibRobus.h>

enum MotorId {
    LEFT_MOTOR = 0,
    RIGHT_MOTOR = 1,
};

struct Motor
{
    MotorId _motorId;

    Motor() {}
    Motor(MotorId motorId) {
        _motorId = motorId;

        resetEncoder();
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
        MOTOR_SetSpeed(_motorId, speed);
    }

    void stop() {
        setSpeed(0);
        resetEncoder();
    }
};

#endif