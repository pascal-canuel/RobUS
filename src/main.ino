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

#include "robot/Robot.h"

Robot robus;

void setup(){
  BoardInit();

  robus = Robot();
  robus.init();
}

void loop() {
  /*
    0 - yellow
    1 - green
    2 - blue
    3 - red
    4 - undefined
  */
  // Color color = robus.readColor();
  // Serial.print("color: "); Serial.println(color);
  if (ROBUS_IsBumper(3)) {
    /*
      Robus A - go get the ball on a color zone and place it in the middle
      Robus B - get the ball in the middle and place it on a color zone
    */
    #ifdef ROBUS_A
      Color target = RED;
      switch (target) {
          case BLUE:
              robus.turn(-90);
              robus.move(38);
              robus.turn(-45);
              takeAndReturn();
              break;
          case YELLOW:
              robus.turn(90);
              robus.move(38);
              robus.turn(45);
              takeAndReturn();
              break;
          case GREEN:
              robus.turn(-90);
              robus.move(38);
              robus.turn(90);
              robus.move(74);
              robus.turn(-45);
              takeAndReturn();
              break;
          case RED:
              robus.turn(90);
              robus.move(38);
              robus.turn(-90);
              robus.move(80); //
              robus.turn(45);
              takeAndReturn();
              break;
      }
    #else
      Color target = RED;
      robus.forwardBall(); // move back
      robus.move(-20);
      switch (target) {
          case BLUE:
              break;
          case YELLOW:
              break;
          case GREEN:
              break;
          case RED:
              break;
      }
    #endif
  }

  delay(100);
}

void takeAndReturn() {
    robus.forwardBall();
    robus.move(-10);
    robus.turn(180);
    robus.forwardCenter();
    robus.move(-50);
}

