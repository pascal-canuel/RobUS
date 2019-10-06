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
  #ifdef ROBUS_A
    float diff = 5;
    Step steps[11] = {
        {MOVE, 120},
        {ROTATE, 90},
        {MOVE, 90 - diff},
        {ROTATE, -90},
        {MOVE, 90 - diff},
        {ROTATE, -45},
        {MOVE, 183 - diff},
        {ROTATE, 90},
        {MOVE, 50 - diff},
        {ROTATE, -45},
        {MOVE, 135 - diff}
      };
  #else
    Step steps[11] = {
        {MOVE, 120},
        {TURN, 90},
        {MOVE, 90},
        {TURN, -90},
        {MOVE, 90},
        {TURN, -45},
        {MOVE, 183},
        {TURN, 90},
        {MOVE, 50},
        {TURN, -45},
        {MOVE, 135}
      };
  #endif
  path = Path(robus, steps);
}

void loop() {
  if (ROBUS_IsBumper(3)) {
    path.execute(length);
    path.reverse(length);
  }
}