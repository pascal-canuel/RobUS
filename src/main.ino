/*
Projet: Parcours du combattant
Equipe: Les 100 ID
Auteurs: 
  - Marie-Eve Castonguay
  - Adam Beliveau
  - Eloise Marchal
  - Pascal Canuel
  - Raphael Auclair
  - Williams Gravel
  - Xavier Champagne
*/

#include "Path.h"

Robot robus;
Path path;
int length;

void setup(){
  BoardInit();

  robus = Robot();
  robus.reset();
  length = 13;
  Step steps[] = {
    {MOVE, 220},
    {ROTATE, 90},
    {MOVE, 80},
    {ROTATE, -90},
    {MOVE, 25},
    {ROTATE, -90},
    {MOVE, 35},
    {ROTATE, 90},
    {MOVE, 80},
    {ROTATE, -90},
    {MOVE, 35},
    {ROTATE, 90},
    {MOVE, 125}
  };
  path = Path(robus, steps);
}

void loop() {
  if (ROBUS_IsBumper(3)) {
    path.execute(length);
    robus.turn(184);
    robus.forward();
  }
}