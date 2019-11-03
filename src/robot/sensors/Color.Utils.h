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

// Rgb redRgb { 254, 0, 0 };
// Rgb greenRgb { 0, 255, 0 };
// Rgb blueRgb { 0, 0, 255 };
// Rgb yellowRgb { 255, 255, 0 };
struct Rgb {
  float red, green, blue;
};

struct Hsv {
  float hue, saturation, value;
};

Hsv _rgbToHsv(Rgb rgb) {
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

  float saturation = 0;
  if (cMax != 0) {
    saturation = delta / cMax;
  }

  float value = cMax;
  
  return Hsv { hue / 2, saturation * 255, value * 255 };
} 

/* TODO
  - change UNDEFINED by white
  - add black
*/
/*
    Hue values range:
    Orange  0 - 22
    Yellow 22 - 38 *15-38*
    Green 38 - 99 *60-70*
    Blue 99 - 130 *70-80*
    Violet 130 - 160
    Red 160 - 179
*/
Color _hsvToColor(Hsv hsv) {
  // Serial.print("hue: "); Serial.println(hsv.hue);
  // Serial.print("saturation: "); Serial.println(hsv.saturation);
  // Serial.print("value: "); Serial.println(hsv.value);

  if (15 < hsv.hue && hsv.hue <= 38 && hsv.saturation > 100)
    return YELLOW;
  if (38 < hsv.hue && hsv.hue <= 70) 
    return GREEN;
  if (70 < hsv.hue && hsv.hue <= 130)
    return BLUE;
  if ((0 <= hsv.hue && hsv.hue <= 15) || (160 < hsv.hue && hsv.hue <= 179))
    return RED;
  
  return UNDEFINED;
}

Color rgbToColor(Rgb rgb) {
  return _hsvToColor(_rgbToHsv(rgb));
}

#endif