/*
Projet: Parcours du combattant
Equipe: Les 100 ID
Auteurs: 
  - Marie-Eve Castonguay
  - Adam Beliveau
  - Eloise Marchal
  - Pascal Canuel
  - Raphael Auclair
  - Williams Gravel
  - Xavier Champagne
*/

#include "Path.h"

Robot robus;
uint8_t angle = 90;

void readBle() {
  Serial.println(BLUETOOTH_read());
}

void setup(){
  BoardInit();

  robus = Robot();
  robus.reset();

  SERVO_Enable(0);
  SERVO_Enable(1);

  openCage();
}

void loop() {
  if (ROBUS_IsBumper(0)) {
    if (angle > 0) {
      angle -= 1;
      Serial.println(angle);
      SERVO_SetAngle(0, angle);
      SERVO_SetAngle(1, angle);
    }
  }
  if (ROBUS_IsBumper(1)) {
    if (angle < 180) {
      angle += 1;
      Serial.println(angle);
      SERVO_SetAngle(0, angle);
      SERVO_SetAngle(1, angle);
    }
  }
  if (ROBUS_IsBumper(3)) {
    closeCage();
    delay(500);
    MOTOR_SetSpeed(0, 0.2);
    MOTOR_SetSpeed(1, 0.2);
    delay(4000);
    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);
  }
}

void openCage() {
  SERVO_SetAngle(1, 180);
}

void closeCage() {
  SERVO_SetAngle(1, 130);
}