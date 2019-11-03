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
      // 1. Go on a line and move to a color zone 
      // 2. When on a color zone calculate fastest path to the given color zone
      // 3. Go in the middle
      // 4. Leave the ball there
      // 5. Move back as not to block the Robus B who takes the ball
    #else
      // 1. Move forward to get ball in the middle
        
      int sensorPin = 0;

// first check is shit
      bool verifBallon = false;
      int limiteMax = 9;
      int limiteMin = 5;

      Serial.println("wtf");
      robus._leftMotor.setSpeed(0.15);
      robus._rightMotor.setSpeed(0.15);
      while (verifBallon == false) {
        Serial.println(verifBallon);
        verifBallon = Detection(limiteMax ,limiteMin, sensorPin); 
        if(verifBallon==true)
        {
            delay(100);

            robus.closeClamp();
            robus._leftMotor.stop();
            robus._rightMotor.stop();
        }
      }
      // delay(100);
      // robus.openClamp();
        // robus.move(25);
      robus.move(-10);
      robus.turn(180);
      robus.moveBreak(37);
      robus.turn(90);
      robus.followLine();
      // 2. Grab the ball
      // 2. Go on a line and move to a color zone 
      // 3. When on a color zone calculate fastest path to the given color zone
      // 4. Go in the given color zone
      // 5. Leave the ball there
    #endif
  }

  delay(100);
}

bool Detection(int limiteMax, int limiteMin,int sensorPin)
{
  int val = 0;
  int distance = 0;

  val = analogRead(sensorPin);
  distance = (7960.9*pow(val,-1.094));
  Serial.println(val);

  if(distance<limiteMax && distance>limiteMin)
    return true;
  else
    return false;
}

