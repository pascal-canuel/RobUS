#ifndef Robot_H_
#define Robot_H_

#include "Robot.Utils.h"
#include "actuators/Motor.h"
#include "sensors/ReflectanceArray.h"
#include "sensors/RFID.h"
#include "PID.h"
#include "sensors/MP3.h"
#include "actuators/Servo.h"

struct Robot
{
    Motor _leftMotor;
    Motor _rightMotor;

    ReflectanceArray _reflectanceArray;
    RFID _rfid;
    
    PID _pid;
    float _pidDelay;

    MP3 player;
    Servo distributor;

    float kP;
    float kI;
    float kD;
    float speed;

    Robot() {
        _leftMotor = Motor(0);
        _rightMotor = Motor(1);
    
        _reflectanceArray = ReflectanceArray();
        _rfid = RFID();

        _pidDelay = 100;
        _pid = PID(_pidDelay, 0.20, 0.01);

        distributor = Servo(1);

        defaultPID();
    }

    void rotate(float degree) {
        Motor motor = _leftMotor;
        if (degree > 0) 
            motor = _rightMotor;

        float distanceToReach = convertDegreeToDistance(degree);
        float pulseToReach = convertDistanceToPulse(distanceToReach);

        motor.setSpeed(DEFAULT_SPEED);
        while (motor.readEncoder() <= pulseToReach) {}

        motor.stop();
    }

    void turn(float degree) {
        degree /= 2;
        Motor forwardMotor = _leftMotor;
        Motor reverseMotor = _rightMotor;
        if (degree > 0) {
            forwardMotor = _rightMotor;
            reverseMotor = _leftMotor;
        }

        float distanceToReach = convertDegreeToDistance(degree);
        float pulseToReach = convertDistanceToPulse(distanceToReach);

        forwardMotor.setSpeed(DEFAULT_SPEED);
        reverseMotor.setSpeed(-DEFAULT_SPEED);

        int32_t forwardPulse;
        int32_t reversePulse;
        do
        {
            forwardPulse = forwardMotor.readEncoder();
            reversePulse = reverseMotor.readEncoder();

            if (forwardPulse >= pulseToReach)
                forwardMotor.setSpeed(0);
            if (reversePulse <= -pulseToReach)
                reverseMotor.setSpeed(0);
        } while (forwardPulse < pulseToReach || reversePulse > -pulseToReach);
        
        stop();
    }

    void move(float distance) {
        float pulseToReach = convertDistanceToPulse(distance);

        int direction = 1;
        if (distance < 0)
            direction = -1;

        int32_t leftPulse;
        int32_t rightPulse;
        _leftMotor.setSpeed(DEFAULT_SPEED * direction);
        _rightMotor.setSpeed(DEFAULT_SPEED * direction);

        unsigned currentMillis = millis();
        unsigned previousMillis = 0;
        do
        {
            leftPulse = _leftMotor.readEncoder();
            rightPulse = _rightMotor.readEncoder();

            currentMillis = millis();
            if (currentMillis - previousMillis > _pidDelay) {
                previousMillis = currentMillis;

                #ifdef ROBUS_A
                    float magic = _pid.Compute(rightPulse, leftPulse);
                     _leftMotor.setSpeed((DEFAULT_SPEED + magic + 0.02) * direction);
                #else
                   float magic = _pid.Compute(leftPulse, rightPulse);
                   _rightMotor.setSpeed((DEFAULT_SPEED + magic) * direction);
                #endif
                // Serial.print(leftPulse);
                // Serial.print(" | ");
                // Serial.println(rightPulse);
            }
        } while (leftPulse * direction <= pulseToReach && rightPulse * direction <= pulseToReach);

        stop();
        _pid.reset();
    }

    void followLine(int targetTagValue) 
    {
        // while (_rfid.read() != targetTagValue)
        // {
        //     delay(100);
        // }
        
        float pidDelay = 10;
        unsigned long totalDelay = 0;
    
        float totalError = 0;
        float lastError = 0;

        while (_rfid.read() == -1)
        {
            int* array = _reflectanceArray.read();
            float error = array[0] + array[1] * 3 + array[2] * 2 + array[3] - (array[4] *1 + array[5] * 2 + array[6] * 3 + array[7]);
            
            float errorD = (error - lastError) / pidDelay;

            // Serial.println(error); Serial.print(" | "); Serial.println(errorD);

            _leftMotor.setSpeed(speed + (kP * error) + (kI * totalError) + (kD * errorD));
            _rightMotor.setSpeed(speed - (kP * error) - (kI * totalError) - (kD * errorD));

            totalError += error;
            lastError = error;

            delete[] array;

            totalDelay += pidDelay;
            if (totalDelay % 500 == 0) {
                readBluetooth();
            }
            delay(pidDelay);
        }
        
        stop();
    }

    void readBluetooth() {
        if (SerialBT.available()) 
        {
            stop();
            String data = SerialBT.readString();
            Serial.println(data);
            if (data == "PLAY")
                player.play();
            else if (data == "PAUSE") 
                player.pause();
            else if (data == "NEXT")
                player.playNext();
            else if (data == "LAST")
                player.playLast();
            else if (data == "FOOD") 
            {
                distributor.open();
                delay(500);
                distributor.close();
            } 
            else if (data.substring(0, 2) == "kP")
            {
                kP = (float)atof(data.substring(2, 7).c_str());
            } else if (data.substring(0, 2) == "kI") {
                // kI = (float)atof(data.substring(2, 7).c_str());
            }
            else if (data.substring(0, 2) == "kD") {
                kD = (float)atof(data.substring(2, 7).c_str());
            } else if (data.substring(0, 5) == "SPEED") {
                speed = (float)atof(data.substring(5, 10).c_str());
            } else if (data == "RESET_PID") {
                defaultPID();
            }
        }
    }
    
    void defaultPID() {
        kP = 0.05;
        kI = 0;
        kD = 0.02;
        speed = 0.15;
    }


    void initParts() {
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
        distributor.init();
    }

    void initSensors() {
        _rfid.init();
        player.init();
    }

    void init() {
        initParts();
        initSensors();
    }

    void stop() {
        _leftMotor.stop();
        _rightMotor.stop();
        delay(500); // inertia
        _leftMotor.resetEncoder();
        _rightMotor.resetEncoder();
    }
};

#endif