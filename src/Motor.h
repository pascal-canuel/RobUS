#ifndef Motor_H_
#define Motor_H_

#include <LibRobus.h>

enum MotorId {
    LEFT_MOTOR = 0,
    RIGHT_MOTOR = 1,
    BOTH_MOTOR = 2,
};

struct Motor
{
    Motor() {
        resetEncoder(BOTH_MOTOR);
    }

    void setSpeed(MotorId motorId, float speed) {
        if(motorId == BOTH_MOTOR) {
            MOTOR_SetSpeed(LEFT_MOTOR, speed);
            MOTOR_SetSpeed(RIGHT_MOTOR, speed);
        } else {
            MOTOR_SetSpeed(motorId, speed);
        }
    }

    void resetEncoder(MotorId motorId) {
        if(motorId == BOTH_MOTOR) {
            ENCODER_Reset(LEFT_MOTOR);
            ENCODER_Reset(RIGHT_MOTOR);
        } else {
            ENCODER_Reset(motorId);
        }
    }

    int32_t readEncoder(MotorId motorId) {
        if(motorId == BOTH_MOTOR) {
            Serial.println("Can't read both encoder at the same time.");
            return 0;
        }
        return ENCODER_Read(motorId);
    }
};

#endif