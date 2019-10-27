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

int leftCaptorPin = 30;
int centerCaptorPin = 32;
int rightCaptorPin = 34;

uint8_t captorCallbackId = 0;
unsigned long captorCallbackDelay = 2000;

void setup(){
  BoardInit();

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
}

/*
  LEFT - CENTER - RIGHT
  0      0        1     Adjust to the right
  0      1        0     Ok
  1      0        0     Adjust to the left
  1      1        1     Not on a line
*/
void followline(int leftVal, int centerVal, int rightVal) {
  if (leftVal && centerVal && rightVal) {

  } else if (leftVal) {

  } else if (centerVal) {

  } else if (rightVal) {

  }
}