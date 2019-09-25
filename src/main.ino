/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

#include "Robot.h"

Robot robus = Robot();

void setup(){
  BoardInit();

  ENCODER_Reset(0);
  ENCODER_Reset(1);

  delay(2000);
  robus.move(50);
  robus.rotate(-90);
  robus.move(50);
  robus.rotate(-90);
  robus.move(25);
  robus.rotate(-90);
}

void loop() {
}