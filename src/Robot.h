#include <LibRobus.h>

const float ROBUS_WIDTH = 18.75;
const float ROBUS_CIRCUMFERENCE = 2*PI*ROBUS_WIDTH;

const float WHEEL_RADIUS = 3.81;
const float WHEEL_CIRCUMFERENCE = 2*PI*WHEEL_RADIUS;
const float WHEEL_TOUR_PULSE = 3200;

struct Robot
{
    Robot() {
    }

    void rotate(float degree) {
        int motor = 0;
        if(degree > 0) {
            motor = 1;
        }

        float distance = (degree/360) * ROBUS_CIRCUMFERENCE;
        Serial.println(distance);
        float pulse = abs((distance/WHEEL_CIRCUMFERENCE) * WHEEL_TOUR_PULSE);
        Serial.println(pulse);

        MOTOR_SetSpeed(motor, 0.2);
        while (ENCODER_Read(motor) < pulse)
        {
        }
        MOTOR_SetSpeed(motor, 0);
        ENCODER_Reset(0);
    }

    void move(float distance) {
        float pulse = abs((distance/WHEEL_CIRCUMFERENCE) * WHEEL_TOUR_PULSE);

        MOTOR_SetSpeed(0, 0.2);
        MOTOR_SetSpeed(1, 0.2);
        while (ENCODER_Read(0) < pulse && ENCODER_Read(1) < pulse)
        {
        }
        
        MOTOR_SetSpeed(0, 0);
        MOTOR_SetSpeed(1, 0);

        ENCODER_Reset(0);
        ENCODER_Reset(1);
    }
};
