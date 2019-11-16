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

#define SerialRFID Serial1 // 19 (RX1)

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
    Serial.println(str);

    if (str.substring(0, 4) == "MOVE") {
      String targets = str.substring(4);
      for (char target: targets) {
        Serial.println(target);
      }
    } else if (str == "FOOD") {

    } else if (str == "WHISTLE") {

    }
  }
}

char crecu;
bool incoming = false;
String idTag;

String tags[][2] = {
  {"0E008E637F", "RFTC014"},
  {"0E008E6F32", "RFTC015"},
  {"0E008E9C42", "RFTC016"}
};

// void loop()
// {
//   while(1)
//   {
//     if(SerialRFID.available())
//     {
//       crecu = SerialRFID.read(); // lit le ID-12
//       switch (crecu)
//       {
//         case 0x02:
//           // START OF TRANSMIT
//           AX_BuzzerON();
//           idTag = "";
//           incoming = true;
//           break;
//         case 0x03:
//           // END OF TRANSMIT
//           AX_BuzzerOFF();
//           incoming = false;
//           // Affiche le code recu sans valider le checksum
//           idTag = idTag.substring(0, 10);
//           for (auto& tag: tags)
//           {
//             if (tag[0] == idTag)
//             {
//               Serial.println(tag[1]);
//             }
//           }
//           break;
//         default:
//           if (incoming)
//             idTag += crecu;
//           break;
//       }
//     }
//   }
// }