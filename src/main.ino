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
      Color target = BLUE;
      switch (target) {
          case BLUE:
              robus.turn(-90);
              robus.move(38);
              robus.turn(-45);
              takeBall();
              robus.turn(138);
              robus.move(70);
              robus.turn(90);
              robus.move(60);
              delay(500);
              robus.openClamp();
              robus.move(-20);
              robus.turn(180);
              robus.move(58);
              break;
          case YELLOW:
              robus.turn(90);
              robus.move(38);
              robus.turn(45);
              takeBall();
              robus.turn(-145);
              robus.move(70);
              robus.turn(-90);
              robus.move(65);
              delay(500);
              robus.openClamp();
              robus.move(-20);
              robus.turn(180);
              robus.move(60);
              break;
          case GREEN:
              robus.turn(-90);
              robus.move(38);
              robus.turn(90);
              robus.move(74); //
              robus.turn(-45);
              robus.forwardBall();
              robus.move(-10);
              robus.turn(-140);
              robus.move(75);
              robus.turn(-90);
              
              robus.move(55);
              delay(500);
              robus.openClamp();
              robus.move(-20);
              robus.turn(180);
              robus.move(50);
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
              
              
              robus.move(65);
              delay(500);
              robus.openClamp();
              robus.move(-20);
              robus.turn(180);
              robus.move(40);
              
              
              
              break;
      }
    #else
      Color target = GREEN;
      robus.forwardBall(); // int pulses = robus.forwardBall();
      robus.move(50); // move back the previous forward distance
      robus.turn(180);
      switch (target) {
          case BLUE:
              robus.turn(-90);
              robus.move(38);
              robus.turn(-45);
              robus.move(60);
              break;
          case YELLOW:
              robus.turn(90);
              robus.move(38);
              robus.turn(45);
              robus.move(60);
              break;
          case GREEN:
              robus.turn(-90);
              robus.move(38);
              robus.turn(90);
              robus.move(90); //
              robus.turn(-45);
              robus.move(65);
              break;
          case RED:
              robus.turn(90);
              robus.move(38);
              robus.turn(-90);
              robus.move(80); //
              robus.turn(50);
              robus.move(65);
              break;
      }
    #endif
  }

  delay(100);
}

void takeBall() {
    robus.forwardBall();
    robus.move(-10);
}

void returnBall() {
    robus.forwardCenter();
    robus.move(-50);
}

void putBallCenter() {
  robus.move(65);
  delay(500);
  robus.openClamp();
  robus.move(-20);
  robus.turn(180);
  robus.move(40);
}