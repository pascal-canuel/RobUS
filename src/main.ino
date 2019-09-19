/*
Projet: Les 100ID
Equipe: P-13
Auteurs: 
  - Pascal Canuel (canp2403)
Description: Breve description du script
*/

#include <robot/Robot.h>

Robot* Robus;

void setup(){
  Robus = new Robot();
}

void loop() {
  Robus->setSpeed(LEFT_MOTOR, 0.2);
  delay(500);
  Robus->setSpeed(BOTH_MOTOR, -0.2);
  delay(500);
}