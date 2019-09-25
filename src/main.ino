/*
Projet: Les 100ID
Equipe: P-13
Auteurs: 
- Pascal Canuel
- Adam Beliveau
- Eloise Marchal
- Marie-Eve Castonguay
- Raphael Auclair
- William Gravel
- Xavier Champagne
Description: Breve description du script
*/

#include "Robot.h"

Robot robus;

void setup(){
    robus = Robot();

    robus.move(50);
    robus.rotate(-90);
    robus.move(25);
    robus.rotate(-45);
    robus.move(25);
    robus.rotate(-45);
}

void loop() {
}