#ifndef PID
#define PID_H_

#include <LibRobus.h>

struct PID
{
    float _delay;
    float _totalError, _lastError;
    float _kp, _ki, _kd;

    PID() {}
    PID(float delay, float kp, float ki, float kd) {
        _delay = delay;
        // Tuning
        _kp = kp;
        _ki = ki;
        _kd = kd;
    }

    float Compute(float referenceValue, float value) {
        float output = 0; 

        return output;
    }
};

#endif