/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

#include "Path.h"

Robot robus;
Path path;

void setup(){
  BoardInit();

  robus = Robot();
  robus.reset();
}

void loop() {
  if (ROBUS_IsBumper(3)) {
    // path
    robus.move(115);
    robus.rotate(90);
    robus.move(70);
    robus.rotate(-90);
    robus.move(65);
    robus.rotate(-45);
    robus.move(185);
    robus.rotate(90);
    robus.move(40);
    robus.rotate(-45);
    robus.move(110);

    delay(1000);
    robus.turn(180);

    // reverse
    robus.move(100);
    robus.rotate(45);
    robus.move(50);
    robus.rotate(-90);
    robus.move(185);
    robus.rotate(45);
    robus.move(65);
    robus.rotate(90);
    robus.move(70);
    robus.rotate(-90);
    robus.move(115);
  }
}