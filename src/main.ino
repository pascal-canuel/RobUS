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

#define ROBUS_A 0
#define ROBUS_B 1
#define __ROBUS__ ROBUS_A

Robot robus;

void setup()
{
    BoardInit();
    BluetoothInit();

    robus = Robot();
    robus.init();
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
            robus.distributor.open();
            delay(500);
            robus.distributor.close();
        } 
        else if (data == "PLAY")
            robus.player.play();
        else if (data == "PAUSE") 
            robus.player.pause();
        else if (data == "NEXT")
            robus.player.playNext();
        else if (data == "LAST")
            robus.player.playLast();
        else if (data.substring(0, 2) == "kP")
        {
            robus.kP = (float)atof(data.substring(2, 7).c_str());
        } else if (data.substring(0, 2) == "kI") {
            // kI = (float)atof(data.substring(2, 7).c_str());
        }
        else if (data.substring(0, 2) == "kD") {
            robus.kD = (float)atof(data.substring(2, 7).c_str());
        } else if (data.substring(0, 5) == "SPEED") {
            robus.speed = (float)atof(data.substring(5, 10).c_str());
        } else if (data == "RESET_PID") {
            robus.defaultPID();
        }
    }
    
    // if (ROBUS_IsBumper(3)) 
    // if (ROBUS_IsBumper(1))
    // if (ROBUS_IsBumper(0))
}
