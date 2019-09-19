#include "Robot.h"
 
Robot::Robot() {
    BoardInit();

    bumperInterruptsInit();
    setSpeed(BOTH_MOTOR, 0);
}

void bumperInterruptsInit() {
    attachInterrupt(digitalPinToInterrupt(LEFT_BUMPER), []() {bumperCallback(LEFT_BUMPER);}, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RIGHT_BUMPER), []() {bumperCallback(RIGHT_BUMPER);}, CHANGE);
    attachInterrupt(digitalPinToInterrupt(FRONT_BUMPER), []() {bumperCallback(FRONT_BUMPER);}, CHANGE);
    attachInterrupt(digitalPinToInterrupt(REAR_BUMPER), []() {bumperCallback(REAR_BUMPER);}, CHANGE);
}

void bumperCallback(int pin) {
    // install fmt
    // install test
  // Serial.println(pin);
}

void Robot::setSpeed(MotorId motorId, float speed) {
    if(motorId == BOTH_MOTOR) {
        MOTOR_SetSpeed(LEFT_MOTOR, speed);
        MOTOR_SetSpeed(RIGHT_MOTOR, speed);
    } else {
        MOTOR_SetSpeed(motorId, speed);
    }
}

void Robot::move(float distance) {}
void Robot::rotate(float degree) {}