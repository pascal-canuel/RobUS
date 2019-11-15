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

#define ROBUS_A 0
#define ROBUS_B 1
#define __ROBUS__ ROBUS_A

/*
  ID-12.ino
*/

#include <LibRobus.h> // Essentielle pour utiliser RobUS

char crecu, i, incoming=0;
char id_tag[20];

void initZumoReflectanceSensorArray() {
  pinMode(40, INPUT);
  pinMode(41, INPUT);
  pinMode(42, INPUT);
  pinMode(43, INPUT);
  pinMode(44, INPUT);
  pinMode(45, INPUT);
}

void readZumboReflectanceSensorArray() {
  Serial.print("1: "); Serial.println(digitalRead(40));
  Serial.print("2: "); Serial.println(digitalRead(41));
  Serial.print("3: "); Serial.println(digitalRead(42));
  Serial.print("4: "); Serial.println(digitalRead(43));
  Serial.print("5: "); Serial.println(digitalRead(44));
  Serial.print("6: "); Serial.println(digitalRead(45));
}

void setup()
{
  BoardInit();
  Serial2.begin(2000); // RX 17
  Serial.println("Test du ID-12 sur UART2 (RX2/Digital 17)");

  initZumoReflectanceSensorArray();
}

void loop()
{
  while(1)
  {
    delay(2000);
    readZumboReflectanceSensorArray();
    if(Serial2.available())
    {
      crecu=Serial2.read();     // lit le ID-12
      switch(crecu)
      {
        case 0x02:
          // START OF TRANSMIT
          AX_BuzzerON();
          i = 0;
          incoming = 1;
          break;
        case 0x03:
          // END OF TRANSMIT
          AX_BuzzerOFF();
          incoming = 0;
          // Affiche le code recu sans valider le checksum
          for(i = 0; i < 10; i++)
            Serial.print(id_tag[i]);
          Serial.println("");
          break;
        default:
          if(incoming)
            id_tag[i++] = crecu;
          break;
      }
    }
  }
}

/* fin du fichier */