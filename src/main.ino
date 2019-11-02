/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

#include "Path.h"
#include "math.h"
#include "Robot.h"

Robot robus;
Path path;
int length;

bool Detection(int,int,int);

void setup()
{
  BoardInit(); 
}

void loop()
{
  SERVO_Enable(0);
  SERVO_SetAngle(0, 180);
  

  if (ROBUS_IsBumper(3)) {
    MOTOR_SetSpeed(0,0.3);
    MOTOR_SetSpeed(1,0.3);
  } 
  checkBall(0);

}
void callCheckBall(int startUp){

}

void checkBall(int sensorPin){
  Serial.println("1");
  bool verifBallon = false;
  int limiteMax = 21;
  int limiteMin = 13;

  verifBallon = Detection(limiteMax ,limiteMin, sensorPin); 
  if(verifBallon==true)
  {
    Serial.println("Pas de ballon");
  }
  else
  { 
    limiteMax = 9;
    limiteMin = 5;
    verifBallon = Detection(limiteMax,limiteMin,sensorPin);
    if(verifBallon == true)
    {
      SERVO_SetAngle(0,130);
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
  Serial.println(val);

  if(distance<limiteMax && distance>limiteMin)
    return true;
  else
    return false;
}