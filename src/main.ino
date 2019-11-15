/*
Equipe: Les 100ID
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

#define SerialRFID Serial1

void setup()
{
  BoardInit();

  BluetoothInit();
  AudioInit();
  SerialRFID.begin(9600);
}

void loop() {
  if (SerialBT.available()) {
    String str = SerialBT.readString();
    if (str == "MOVE") {

    } else if (str == "FOOD") {

    } else if (str == "WHISTLE") {

    }
  }
}