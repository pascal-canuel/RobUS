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

  robus.move(30);
  robus.rotate(90);
  robus.rotate(-90);
  robus.move(-30);
}

void loop() {}

/*
  Step steps[] = {
    {MOVE, 90}, 
    {ROTATE, 45},
    {MOVE, 50},
    {ROTATE, -90},
    {MOVE, 165},
    {ROTATE, 45},
    {MOVE, 80},
    {ROTATE, 90},
    {MOVE, 100},
    {ROTATE, -90},
    {MOVE, 90}
  };
  int length = 11;
  path = Path(robus, steps);
  path.execute(length);
  path.reverse(length);
*/