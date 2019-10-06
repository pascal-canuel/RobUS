/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

#include "Path.h"

Robot robus;
Path path, path2;
int length,lenght2;

void setup(){
  BoardInit();

  robus = Robot();
  robus.reset();
  Step steps[] = {
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
  length = 11;
  path = Path(robus, steps);

  robus.reset();
  Step steps2[] = {
    {MOVE, 135},
    {TURN, 45},
    {MOVE, 50},
    {TURN, -90},
    {MOVE, 185},
    {TURN, -45},
    {MOVE, 70},
    {TURN, -90},
    {MOVE, 70},
    {TURN, 90},
    {MOVE, 115}
  };
  lenght2 = 11;
  path2 = Path(robus, steps2);
}

void loop() {
  if (ROBUS_IsBumper(3)) {
    path.execute(length);
    //robus.turn(180);
    path.reverse(length);
    //path2.execute(lenght2);
   
  }
}