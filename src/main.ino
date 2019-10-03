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
int length;

void setup(){
  BoardInit();

  robus = Robot();
  robus.reset();
  Step steps[] = {
    {MOVE, 115}, //122.5
    {ROTATE, 90},
    {MOVE, 70}, //90
    {ROTATE, -90},
    {MOVE, 65}, //87.5
    {ROTATE, -45},
    {MOVE, 185}, //173.5
    {ROTATE, 90},
    {MOVE, 40}, //44
    {ROTATE, -45},
    {MOVE, 100} //110
  };
  length = 11;
  path = Path(robus, steps);
}

void loop() {
  if (ROBUS_IsBumper(3)) {
    path.execute(length);
    path.reverse(length);
  }
}