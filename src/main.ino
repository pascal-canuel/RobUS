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

  /*Step path[] = {
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
  };*/
  //int length = 11; // cant use vector/list...
  Step path[] = {
    {MOVE, 30},
    {ROTATE, 90},
    {MOVE, 30}
  };
  int length = 3;
  
  robus.executePath(path, length);
  robus.reversePath(path, length);
}

void loop() {}