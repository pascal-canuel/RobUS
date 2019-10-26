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

#include "Path.h"

#include <Wire.h>
#include "Adafruit_TCS34725.h"

Robot robus;

Adafruit_TCS34725 tcs = Adafruit_TCS34725();

enum Color {
  YELLOW, 
  GREEN,
  BLUE,
  RED,
  UNDEFINED
};

struct Rgb {
  uint16_t red, green, blue;
};

void setup(){
  BoardInit();

  robus = Robot();
  robus.reset();

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
  }
}

void loop() {
  // uint16_t red, green, blue, clear;
  // tcs.getRawData(&red, &green, &blue, &clear);

  float red, green, blue, clear;
  tcs.getRGB(&red, &green, &blue);

  Rgb rgb { red, green, blue };
  Color color = rgbToColor(rgb);

  Serial.println(color);
  delay(2000);
}


float rgbToHue(Rgb rgb) {
  float red = rgb.red / 255.;
  float green = rgb.green / 255.;
  float blue = rgb.blue / 255.;

  float cMax = max(max(red, green), blue); 
  float cMin = min(min(red, green), blue);

  float delta = cMax - cMin;
  float hue = 0;

  if (blue == cMax) {
    hue = 60 * ((red - green) / delta + 4);
  }
  else if (green == cMax) {
    hue = 60 * ((blue - red) / delta + 2);
  }
  else if (red == cMax) {
    hue = 60 * ((green - blue) / delta);	
    if (hue < 0)
      hue += 360;
  }

  return hue / 2;
} 

/*
  Hue values range:
  Orange  0 - 22
  Yellow 22 - 38
  Green 38 - 75
  Blue 75 - 130
  Violet 130 - 160
  Red 160 - 179
*/
Color hueToColor(float hue) {
  if (22 < hue <= 38)
    return YELLOW;
  if (38 < hue <= 75) 
    return GREEN;
  if (75 < hue <= 130)
    return BLUE;
  if (160 < hue <= 179)
    return RED;
  
  return UNDEFINED;
}

Color rgbToColor(Rgb rgb) {
  return hueToColor(rgbToHue(rgb));
}