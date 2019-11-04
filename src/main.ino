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

#define ROBUS_A 0
#define ROBUS_B 1
#define __ROBUS__ ROBUS_A

#include "robot/Robot.h"

Robot robus;
Color target;

void setup(){
    BoardInit();

    robus = Robot();
    robus.init();
}

void loop() {
    if (ROBUS_IsBumper(3)) {
#if __ROBUS__ == ROBUS_A // Get the ball in a given color zone and place it in the middle
        target = YELLOW;
        
        switch (target) {
            case BLUE:
                robus.turn(-90);
                robus.move(38);
                robus.turn(-45);
                forwardGrabBall();
                robus.turn(180);
                returnBallCenterDetection();
                break;
            case YELLOW:
                robus.turn(90);
                robus.move(38);
                robus.turn(45);
                forwardGrabBall();
                robus.turn(180);
                returnBallCenterDetection();
                break;
            case GREEN:
                robus.turn(-90);
                robus.move(38);
                robus.turn(90);
                robus.move(74); //
                robus.turn(-45);
                forwardGrabBall();
                robus.move(-10);
                robus.turn(-135);
                robus.move(70);
                robus.turn(-90);
                returnBallCenterDistance();
                break;
            case RED:
                robus.turn(90);
                robus.move(38);
                robus.turn(-90);
                robus.move(84); //
                robus.turn(45);
                forwardGrabBall();
                robus.move(-10);
                robus.turn(135);
                robus.move(70);
                robus.turn(90);
                returnBallCenterDistance();
                break;
        }
#elif __ROBUS__ == ROBUS_B // Get the ball in the middle and place it in a given color zone
        target = RED;

        robus.forward(robus.detectBall, robus.closeClamp);
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
  // delay(100);
}

void forwardGrabBall() {
    robus.forward(robus.detectBall, robus.closeClamp);
    robus.move(-10);
}

void returnBallCenterDetection() {
    robus.forward(robus.detectCenter, robus.openClamp);
    robus.move(-50);
}

void returnBallCenterDistance() {
    robus.move(65);
    delay(500);
    robus.openClamp();
    robus.move(-50);
}