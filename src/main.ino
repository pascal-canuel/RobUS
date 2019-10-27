/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

#include "Path.h"
#include "math.h"


bool Detection(int,int,int);

void setup()
{
  BoardInit(); 
}

void loop()
{
  
  int sensorPin = 0;
  bool verifBallon = false;
  int limiteMax = 21;
  int limiteMin = 13;
  verifBallon = Detection(limiteMax ,limiteMin, sensorPin);  
  if(verifBallon==true)
  {
    Serial.println("pas de ballon");
  }
  else
  { 
    limiteMax = 9;
    limiteMin = 5;
    verifBallon = Detection(limiteMax,limiteMin,sensorPin);
    if(verifBallon == true)
    {
      Serial.println("Ballon");
    }
  }
 
  delay(500);
}

bool Detection(int limiteMax, int limiteMin,int sensorPin)
{
  int val = 0;
  int distance = 0;

  val = analogRead(sensorPin);
  distance = (7960.9*pow(val,-1.094));
  Serial.println(distance);

  if(distance<limiteMax && distance>limiteMin)
    return true;
  else
    return false;
}