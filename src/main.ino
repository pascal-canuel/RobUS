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

#define ROBUS_A 0
#define ROBUS_B 1
#define __ROBUS__ ROBUS_A

Robot robus;
Servo distributor;

void setup()
{
    BoardInit();
    BluetoothInit();

    robus = Robot();
    robus.init();

    distributor = Servo(1);
    distributor.init();
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
                readBluetooth();
                robus.rotate(150);
                robus.followLine(1);
                readBluetooth();
                robus.move(5);
                robus.followLine(0);
                readBluetooth();
                robus.move(10);
                robus.followLine(0);
                readBluetooth();
                robus.move(10);
            } else if (data[4] == '1') {
                robus.followLine(2);
                readBluetooth();
                robus.move(10);
                robus.followLine(1);
                readBluetooth();
                robus.turn(-85);
                robus.followLine(0);
                readBluetooth();
                robus.move(10);
                robus.followLine(0);
                readBluetooth();
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
            robus.player.play();
        else if (data == "PAUSE") 
            robus.player.pause();
        else if (data == "NEXT")
            robus.player.playNext();
        else if (data == "LAST")
            robus.player.playLast();
    }
    
    // if (ROBUS_IsBumper(3)) 
    // if (ROBUS_IsBumper(1))
    // if (ROBUS_IsBumper(0))
}

void readBluetooth() {
    if (SerialBT.available()) 
    {
        String data = SerialBT.readString();
        Serial.println(data);
        if (data == "PLAY")
            robus.player.play();
        else if (data == "PAUSE") 
            robus.player.pause();
        else if (data == "NEXT")
            robus.player.playNext();
        else if (data == "LAST")
            robus.player.playLast();
        else if (data == "FOOD") 
        {
            distributor.open();
            delay(500);
            distributor.close();
        } 
    }
}