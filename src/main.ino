/*
Projet: Les 100ID
Equipe: P-13
Auteurs: 
  - Pascal Canuel (canp2403)
Description: Breve description du script
*/

#include <robot/Robot.h>

robot* Robus;

void setup(){
  Robus = new robot();

  MOTOR_SetSpeed(0, 0.2);
  MOTOR_SetSpeed(1, -0.2);
}

void loop() {
  //Serial.println(ROBUS_IsBumper(2));

  if(ROBUS_IsBumper(2)) {
    MOTOR_SetSpeed(1, 0.2);
    MOTOR_SetSpeed(0, -0.2);
  }
  if(ROBUS_IsBumper(0)) {
    AX_BuzzerON();
  }
if(ROBUS_IsBumper(1)) {
    AX_BuzzerOFF();
  }
  if(ROBUS_IsBumper(3)) {
    MOTOR_SetSpeed(1, 0);
    MOTOR_SetSpeed(0, 0);
  }
  if (ROBUS_IsBumper(0) || ROBUS_IsBumper(1) || ROBUS_IsBumper(2) || ROBUS_IsBumper(3)) {
    exit(0);
  }
  
  delay(500);
}