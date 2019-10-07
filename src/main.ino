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
  length = 11;
  Step steps[11] = {
    {MOVE, 110},
    {ROTATE, 90},
    {MOVE, 72.5},
    {ROTATE, -90},
    {MOVE, 80},
    {ROTATE, -45},
    {MOVE, 175},
    {ROTATE, 90},
    {MOVE, 45},
    {ROTATE, -45},
    {MOVE, 125}
  };
  path = Path(robus, steps);
}

void loop() {
  if (ROBUS_IsBumper(3)) {
    path.execute(length);
    path.reverse(length);
  }
}