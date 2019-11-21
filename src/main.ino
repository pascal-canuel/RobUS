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

#include "robot/Robot.h"
#include "robot/actuators/Servo.h"
#include "robot/sensors/MP3.h"

#define ROBUS_A 0
#define ROBUS_B 1
#define __ROBUS__ ROBUS_A

Robot robus;
Servo distributor;
MP3 player;

void setup()
{
    BoardInit();
    BluetoothInit();

    robus = Robot();
    robus.init();

    distributor = Servo(1);
    distributor.init();

    player.init();
}

void loop() 
{
    if (SerialBT.available()) 
    {
        String data = SerialBT.readString();
        Serial.println(data);

        if (data.substring(0, 4) == "MOVE") 
        {
            String targets = data.substring(4);
            for (char target: targets) 
            {
                // convert char to int (ascii table)
                // '0' -> 0 = 48 -> 0
                int value = target - '0';
                Serial.println(value);
                
                robus.followLine(value);
            }
        } 
        else if (data == "FOOD") 
        {
            distributor.open();
            delay(500);
            distributor.close();
        } 
        else if (data == "WHISTLE") 
        {
            player.playNext();
        }
    }
    
    if (ROBUS_IsBumper(3)) 
    {
        // player.playNext();
        robus.followLine(0);
    }
    if (ROBUS_IsBumper(1))
        player.volUp();
    if (ROBUS_IsBumper(0))
        player.volDown();
}