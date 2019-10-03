#ifndef PID
#define PID_H_

#include <LibRobus.h>

struct PID
{
    float _delay;
    float _totalError = 0;
    float _kp, _ki;

    PID() {}
    PID(float delay, float kp, float ki) {
        _delay = delay;
        // Tuning
        _kp = kp;
        _ki = ki;
    }

    float Compute(float referenceValue, float value) {
        float error = (referenceValue - value)/_delay;
        Serial.print("proportional error: ");
        Serial.println(error);

        _totalError += error;
        Serial.print("integral error: ");
        Serial.println(_totalError);

        float output = _kp * error + _ki * _totalError; 

        return output;
    }
};

#endif