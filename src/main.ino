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

void setup(){
  BoardInit();

  robus = Robot();
  robus.reset();

  pinMode(leftCaptorPin, INPUT);
  pinMode(centerCaptorPin, INPUT);
  pinMode(rightCaptorPin, INPUT);
}

void loop() {
  Serial.println(digitalRead(leftCaptorPin));
  Serial.println(digitalRead(centerCaptorPin));
  Serial.println(digitalRead(rightCaptorPin));
  
  delay(2000);
}