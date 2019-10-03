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

        Serial.println("e_p | e_i | output");
    }

    float Compute(float referenceValue, float value) {
        float error = (referenceValue - value)/_delay;

        _totalError += error;

        float output = _kp * error + _ki * _totalError; 

        Serial.print(error);
        Serial.print(" | ");
        Serial.print(_totalError);
        Serial.print(" | ");
        Serial.println(output);

        return output;
    }
};

#endif