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

int leftCaptorPin = 40;
int centerCaptorPin = 44;
int rightCaptorPin = 42;
int isbumper = 0;
float vitesse1 = 0;
float vitesse = 0;

uint8_t captorCallbackId = 0;
unsigned long captorCallbackDelay = 100;

void setup(){
  BoardInit();
  SERVO_Enable(0);
  SERVO_SetAngle(0,180);
  robus = Robot();
  robus.reset();
  
  pinMode(leftCaptorPin, INPUT);
  pinMode(centerCaptorPin, INPUT);
  pinMode(rightCaptorPin, INPUT);

  SOFT_TIMER_SetCallback(captorCallbackId, captorCallback);
  SOFT_TIMER_SetDelay(captorCallbackId, captorCallbackDelay);
  SOFT_TIMER_Enable(captorCallbackId);
}

void loop() {
  SOFT_TIMER_Update();
  //delay(2000);
}

void captorCallback() {

  
  /*
    0 = LOW
    1 = HIGH
  */
  int leftCaptorVal = digitalRead(leftCaptorPin);
  int centerCaptorVal = digitalRead(centerCaptorPin);
  int rightCaptorVal = digitalRead(rightCaptorPin);

  Serial.print("left: "); Serial.println(leftCaptorVal);
  Serial.print("center: "); Serial.println(centerCaptorVal);
  Serial.print("right: "); Serial.println(rightCaptorVal);
  if(ROBUS_IsBumper(3))
  isbumper = 1;
  if(isbumper == 1)
  {
    followline(leftCaptorVal,centerCaptorVal,rightCaptorVal);
  }

}

/*
  LEFT - CENTER - RIGHT
  0      0        1     Adjust to the right
  0      1        0     Ok
  1      0        0     Adjust to the left
  0      0        0     color zone or white space
*/
void followline(int leftVal, int centerVal, int rightVal) {
  
  Serial.print("Leftval : ");Serial.print(leftVal);Serial.print("\tRightval : ");Serial.print(rightVal);;Serial.print("\tcenterval : ");Serial.println(centerVal);
  //if ((!leftVal && !centerVal && !rightVal) ) {
    // MOTOR_SetSpeed(1,0);
    // MOTOR_SetSpeed(0,0);
  //} 
  if (leftVal==1) {
    Serial.println("Good if left");
   vitesse = 0.2;
   vitesse1 = 0.17;
  } else if (centerVal==1) {
    Serial.println("Good if center");
   vitesse = 0.3;
   vitesse1 = 0.3;
  } else if (rightVal==1) {
    Serial.println("Good if right");
   vitesse = 0.17;
   vitesse1 = 0.2;
  }

  Serial.print("vitesse : ");Serial.print(vitesse);Serial.print("\tvitesse1 : ");Serial.println(vitesse1);
  MOTOR_SetSpeed(1,vitesse);
  MOTOR_SetSpeed(0,vitesse1);
  
}