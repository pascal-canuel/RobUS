#ifndef REFLECTANCE_ARRAY_H_
#define REFLECTANCE_ARRAY_H_

#include <Arduino.h>

struct ReflectanceArray
{
    ReflectanceArray() {}

    int treshold(int analogValue)
    {
        return (analogValue > 900) ? 1 : 0;
    }

    // return array of size 8 (0: not black, 1: black)
    int* read() {
        int array[8];
        array[0] = treshold(analogRead(A6));
        array[1] = treshold(analogRead(A7));
        array[2] = treshold(analogRead(A8));
        array[3] = treshold(analogRead(A9));
        array[4] = treshold(analogRead(A10));
        array[5] = treshold(analogRead(A11));
        array[6] = treshold(analogRead(A12));
        array[7] = treshold(analogRead(A13));

        return array;
    }
};

#endif