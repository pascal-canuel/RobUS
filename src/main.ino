/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

#include "Robot.h"

Robot robus;

void setup(){
  BoardInit();

  robus = Robot();
  robus.reset();

  robus.move(95);
  robus.rotate(45);
  robus.move(50);
  robus.rotate(-90);
  robus.move(170);
  robus.rotate(45);
  robus.move(80);
  robus.rotate(90);
  robus.move(100);
  robus.rotate(-90);
  robus.move(90);
}

void loop() {}