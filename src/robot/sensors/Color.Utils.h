#ifndef Color_Utils_H_
#define Color_Utils_H_

#include <Arduino.h>

enum Color {
  YELLOW, 
  GREEN,
  BLUE,
  RED, 
  UNDEFINED
};

struct Rgb {
  float red, green, blue;
};

// Rgb redRgb { 254, 0, 0 };
// Rgb greenRgb { 0, 255, 0 };
// Rgb blueRgb { 0, 0, 255 };
// Rgb yellowRgb { 255, 255, 0 };

float _rgbToHue(Rgb rgb) {
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
Color _hueToColor(float hue) {
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
  return _hueToColor(_rgbToHue(rgb));
}

#endif