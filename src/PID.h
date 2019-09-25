#ifndef PID_H_
#define PID_H_

#include <LibRobus.h>

struct PID
{
    unsigned long _lastTime;
    float _totalError, _lastError;
    float _kp, _ki, _kd;

    PID() {}
    PID(float kp, float ki, float kd) {
        // Tuning
        _kp = kp;
        _ki = ki;
        _kd = kd;
    }

    float Compute(float referenceValue, float value) {
        float error = referenceValue - value;

        unsigned long now = millis();
        float timeChange = now - _lastTime;

        // The more often we read the error, the less important it will be
        _totalError += error * timeChange;

        // Rate of change of the error
        float rofError = (error - _lastError) / timeChange;

        float output =  _kp * error + _ki * _totalError + _kd * rofError;

        _lastError = error;
        _lastTime = now;

        return output;
    }
};

#endif