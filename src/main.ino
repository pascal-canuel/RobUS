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
            if (data[4] == '0') {
                robus.followLine(2);
                robus.rotate(150);
                robus.followLine(1);
                robus.move(5);
                robus.followLine(0);
                robus.move(10);
                robus.followLine(0);
                robus.move(10);
            } else if (data[4] == '1') {
                robus.followLine(2);
                robus.move(10);
                robus.followLine(1);
                robus.turn(-85);
                robus.followLine(0);
                robus.move(10);
                robus.followLine(0);
                robus.move(10);
            }
        } 
        else if (data == "FOOD") 
        {
            distributor.open();
            delay(500);
            distributor.close();
        } 
        else if (data == "PLAY")
            player.play();
        else if (data == "PAUSE") 
            player.pause();
        else if (data == "NEXT")
            player.playNext();
        else if (data == "LAST")
            player.playLast();
    }
    
    // if (ROBUS_IsBumper(3)) 
    // if (ROBUS_IsBumper(1))
    // if (ROBUS_IsBumper(0))
}