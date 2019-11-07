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
  
  /*
  //UNCOMMENT TO READ ENCODERS TEST BEFORE RUN
  float shit0 = ENCODER_Read(0);
  Serial.println(shit0);
  float shit1 = ENCODER_Read(1);
  Serial.println(shit1);
*/
  if (ROBUS_IsBumper(3)) {
    /*
      Robus A - go get the ball on a color zone and place it in the middle
      Robus B - get the ball in the middle and place it on a color zone
    */
   //ROBOT A POUR ALLER AU VERT EST ISH 
   //ROBOT A POUR ALLER AU ROUGE EST EH
   //TESTER LES ENCODEURS SI IL SE MET A TOURNER EN ROND
    #ifdef ROBUS_A
      Color target = GREEN;
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
              robus.move(-30);
              robus.turn(180);
              robus.move(50);
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
              robus.move(74); 
              robus.turn(-45);
              robus.forwardBall();
              robus.move(-10);
              robus.turn(-143);
              robus.move(110);
              robus.turn(-120);
              
              robus.move(70);
              delay(500);
              robus.openClamp();
              robus.move(-20);
              robus.turn(180);
              robus.move(70);
              break;

          case RED:
              robus.turn(90);
              robus.move(38);
              robus.turn(-90);
              robus.move(81); //
              robus.turn(40);
              robus.forwardBall();
              robus.move(-10);
              robus.turn(140);
              robus.move(145);
              robus.turn(130);
              
              
              robus.move(90);
              delay(500);
              robus.openClamp();
              robus.move(-15);
              robus.turn(135);
              robus.move(70);
              
              
              
              break;
      }
    #else
      Color target = RED;
      delay(30000);
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