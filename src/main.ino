/*
Projet: Les 100ID
Equipe: P-13
Auteurs: 
  - Pascal Canuel (canp2403)
  - Adam Béliveau (bela1003)
Description: Breve description du script
*/

#include <robot/Robot.h>

Robot* Robus;

void setup(){
  Robus = new Robot();
  
}

void loop() {
 
if(ROBUS_IsBumper(2)==true)
  {
    Robus->rotate(180,RIGHT_MOTOR);
  }
  if(ROBUS_IsBumper(3)==true)
  {
    Robus->rotate(180,LEFT_MOTOR);
  }
}