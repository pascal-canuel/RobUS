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

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_4X);

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

// Rgb redRgb { 254, 0, 0 };
// Rgb greenRgb { 0, 255, 0 };
// Rgb blueRgb { 0, 0, 255 };
// Rgb yellowRgb { 255, 255, 0 };

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

  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);

  if (red == green && red == blue && green == blue) {
    Serial.println("error with the captor");
  } else {
    Rgb rgb { red, green, blue };
    Color color = rgbToColor(rgb);
    Serial.println("red | green | blue | color");
    Serial.print(red); Serial.print(" | "); Serial.print(green); Serial.print(" | "); Serial.print(blue); Serial.print(" | "); Serial.println(color);
  }
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

  if (delta != 0) {
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
  if (22 < hue && hue <= 38)
    return YELLOW;
  if (38 < hue && hue <= 75) 
    return GREEN;
  if (75 < hue && hue <= 130)
    return BLUE;
  if ((0 <= hue && hue <= 22) || (160 < hue && hue <= 179))
    return RED;
  
  return UNDEFINED;
}

Color rgbToColor(Rgb rgb) {
  return hueToColor(rgbToHue(rgb));
}