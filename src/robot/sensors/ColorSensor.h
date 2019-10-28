#ifndef ColorSensor_H_
#define ColorSensor_H_

#include <Wire.h>
#include "Adafruit_TCS34725.h"

#include "Color.Utils.h"

struct ColorSensor
{
    Adafruit_TCS34725 _tcs;

    ColorSensor() {
        _tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_4X);
    }

    void init() {
        if (_tcs.begin()) {
             Serial.println("Found sensor");
        } else {
             Serial.println("No TCS34725 found ... check your connections");
        }
    }

    Color read() {
        float red, green, blue;
        Color color;

        _tcs.getRGB(&red, &green, &blue);
        if (red == green && red == blue && green == blue) {
            Serial.println("can't read color");
        } else {
            Rgb rgb { red, green, blue };
            color = rgbToColor(rgb);

            // Serial.println("red | green | blue | color");
            // Serial.print(red); Serial.print(" | "); Serial.print(green); Serial.print(" | "); Serial.print(blue); Serial.print(" | "); Serial.println(color);
        }

        return color;
    }
};

#endif