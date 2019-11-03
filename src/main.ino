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
int step_Path = 0;

void setup(){
  BoardInit();

  robus = Robot();
  robus.init();
  
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
    // 2. Grab the ball
    // 2. Go on a line and move to a color zone 
    // 3. When on a color zone calculate fastest path to the given color zone
    // 4. Go in the given color zone
    // 5. Leave the ball there
  #endif
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
  
  // if (ROBUS_IsBumper(3)) {
  //  robus.followLine();
  // }
  
  Color color;
  LineFollowerSensor linefollowsensor;
  Color color_To = BLUE;


  color = robus.readColor();
  Serial.println(step_Path);
  if(step_Path == 2)
  linefollowsensor.followline(color_To, color);
  
  if(step_Path == 1)
  {
    MOTOR_SetSpeed(1,0.3);
    MOTOR_SetSpeed(0,0.3);
    step_Path++;
  }
  if (step_Path == 0)
  {
    robus.rotate(-90);
    step_Path++;
  }
  

  
  
  
  



  delay(100);
}

