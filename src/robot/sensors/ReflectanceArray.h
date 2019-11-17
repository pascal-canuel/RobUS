#ifndef REFLECTANCE_ARRAY_H_
#define REFLECTANCE_ARRAY_H_

#include <Arduino.h>

struct ReflectanceArray
{
    ReflectanceArray() {}

    // return array of size 8
    int* read() {
        int array[8];
        array[0] = analogRead(A6);
        array[1] = analogRead(A7);
        array[2] = analogRead(A8);
        array[3] = analogRead(A9);
        array[4] = analogRead(A10);
        array[5] = analogRead(A11);
        array[6] = analogRead(A12);
        array[7] = analogRead(A13);

        return array;
    }
};

#endif