#include "Robot.h"
 
Robot::Robot() {
    BoardInit();
    setSpeed(BOTH_MOTOR, 0);
}
float WHEEL_RADIUS = 3.81;
float ROBUS_WITDH = 19.15;
float WHEEL_CIRCUMFERENCE = 2*PI*WHEEL_RADIUS;
float WHEEL_TOUR_PULSE = 3200;
float TURN_CIRCUMFERENCE = 2*PI*ROBUS_WITDH;



void Robot::setSpeed(MotorId motorId, float speed) {
    if(motorId == BOTH_MOTOR) {
        MOTOR_SetSpeed(LEFT_MOTOR, speed);
        MOTOR_SetSpeed(RIGHT_MOTOR, speed);
    } else {
        MOTOR_SetSpeed(motorId, speed);
    }
}

void Robot::move(float distance) {}
void Robot::rotate(float degree,float Motor_ID)
 {
     
     float ONE_TURN_DEGREE = 360;
     float NB_PIN_ONE_TURN = TURN_CIRCUMFERENCE/WHEEL_CIRCUMFERENCE*3200;
     float NB_PIN_FOR_TURN = NB_PIN_ONE_TURN*degree/ONE_TURN_DEGREE;
     if(Motor_ID==LEFT_MOTOR)
     {
         ENCODER_ReadReset(LEFT_MOTOR);
         while (ENCODER_Read(LEFT_MOTOR)<NB_PIN_FOR_TURN);
        {
            MOTOR_SetSpeed(LEFT_MOTOR,0.20);
        }
        MOTOR_SetSpeed(LEFT_MOTOR,0);
     }
     if(Motor_ID==RIGHT_MOTOR)
     {
         ENCODER_ReadReset(RIGHT_MOTOR);
          while (ENCODER_Read(RIGHT_MOTOR)<NB_PIN_FOR_TURN);
         {
            MOTOR_SetSpeed(RIGHT_MOTOR,0.2);
         }
         MOTOR_SetSpeed(RIGHT_MOTOR,0);
     }
     
 }