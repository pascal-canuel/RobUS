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
      Color target = YELLOW;
      switch (target) {
          case BLUE:
              robus.turn(-90);
              robus.move(38);
              robus.turn(-45);
              takeBall();
              returnBall();
              break;
          case YELLOW:
              robus.turn(90);
              robus.move(38);
              robus.turn(45);
              takeBall();
              returnBall();
              break;
          case GREEN:
              robus.turn(-90);
              robus.move(38);
              robus.turn(90);
              robus.move(74); //
              robus.turn(-45);
              robus.forwardBall();
              robus.move(-10);
              robus.turn(-135);
              robus.move(70);
              robus.turn(-90);
              putBallCenter();
              break;
          case RED:
              robus.turn(90);
              robus.move(38);
              robus.turn(-90);
              robus.move(84); //
              robus.turn(45);
              robus.forwardBall();
              robus.move(-10);
              robus.turn(135);
              robus.move(70);
              robus.turn(90);
              putBallCenter();
              break;
      }
    #else
      Color target = RED;
      robus.forwardBall(); // int pulses = robus.forwardBall();
      robus.move(-20); // move back the previous forward distance
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

void takeBall() {
    robus.forwardBall();
    robus.move(-10);
    robus.turn(180);
}

void returnBall() {
    robus.forwardCenter();
    robus.move(-50);
}

void putBallCenter() {
  robus.move(65);
  delay(500);
  robus.openClamp();
  robus.move(-50);
}