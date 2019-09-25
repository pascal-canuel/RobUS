#ifndef Robot_Utils_H_
#define Robot_Utils_H_

#include <LibRobus.h>

const float ROBUS_WIDTH = 18.75;
const float ROBUS_CIRCUMFERENCE = 2*PI*ROBUS_WIDTH;

const float WHEEL_RADIUS = 3.81;
const float WHEEL_CIRCUMFERENCE = 2*PI*WHEEL_RADIUS;
const float WHEEL_TOUR_PULSE = 3200;

const float DEFAULT_SPEED = 0.2;

static int32_t convertDegreeToDistance(float degree) {
    return abs((degree/360) * ROBUS_CIRCUMFERENCE);
}

static int32_t convertDistanceToPulse(float distance) {
    return abs((distance/WHEEL_CIRCUMFERENCE) * WHEEL_TOUR_PULSE);
}

#endif