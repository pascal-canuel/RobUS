#ifndef DistanceSensor_H_
#define DistanceSensor_H_

#include <Arduino.h>

struct DistanceSensor
{
    uint8_t _sensorId;

    DistanceSensor() {};
    DistanceSensor(uint8_t sensorId) {
        _sensorId = sensorId;
    };

    bool detectBall()
    {
        int val = analogRead(_sensorId);
        int distance = (7960.9 * pow(val, -1.094));

        if (distance > 6 && distance < 13)
            return true;
        else
            return false;
    }
};

#endif