#ifndef REFLECTANCE_ARRAY_H_
#define REFLECTANCE_ARRAY_H_

#include <Arduino.h>

struct ReflectanceArray
{
    ReflectanceArray() {}

    int treshold(int analogValue)
    {
        return (analogValue > 800) ? 1 : 0;
    }

    // return array of size 8 (0: not black, 1: black)
    int* read() {
        int* array = new int[8];
        array[0] = treshold(analogRead(A6));
        array[1] = treshold(analogRead(A7));
        array[2] = treshold(analogRead(A8));
        array[3] = treshold(analogRead(A9));
        array[4] = treshold(analogRead(A10));
        array[5] = treshold(analogRead(A11));
        array[6] = treshold(analogRead(A12));
        array[7] = treshold(analogRead(A13));

        // Serial.print(array[0]); Serial.print(" | "); Serial.print(array[1]); Serial.print(" | ");Serial.print(array[2]); Serial.print(" | "); Serial.print(array[3]); Serial.print(" | "); Serial.print(array[4]); Serial.print(" | "); Serial.print(array[5]); Serial.print(" | "); Serial.print(array[6]); Serial.print(" | "); Serial.println(array[7]);
        return array;
    }
};

#endif