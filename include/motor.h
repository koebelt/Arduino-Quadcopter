#pragma once

#include <Servo.h>
#include <Arduino.h>

#define MOT_START_MINIMUM 1090 // µs nécessaire pour décoller et avoir correction d'assiette possible
#define MOT_MINIMUM 1000 // µs min pour l'ESC
#define MOT_MAX 2000

class Motor
{
    public:
        Motor(int pin) { this->pin = pin;
            this->serv.attach(this->pin, MOT_MINIMUM, MOT_MAX);
            this->serv.writeMicroseconds(MOT_MINIMUM);
        };
        Motor() = default;
        ~Motor() {this->serv.detach();};

        void start();
        void stop();
        void doCommand();
        void setCommand(unsigned long command) { ESC_command = chechBoundaries(command); };
    private:
        int pin;
        unsigned long ESC_command = MOT_MINIMUM;
        bool started = false;
        Servo serv;
        unsigned long chechBoundaries(unsigned long command);
};

class MotorManager
{
    public:
        MotorManager(int pinA, int pinB) { this->motA = new Motor(pinA); this->motB = new Motor(pinB); this->nbMotors = 2; };
        MotorManager(int pinA, int pinB, int pinC, int pinD) { this->motA = new Motor(pinA); this->motB = new Motor(pinB); this->motC = new Motor(pinC); this->motD = new Motor(pinD);  this->nbMotors = 4; };
        ~MotorManager();

        void start();
        void stop();

        void doCommand();
        void doCorrection(unsigned long throttle, float pidYaw, float pidRoll, float pidPitch);
    private:
        Motor *motA, *motB, *motC, *motD;
        int nbMotors = 0;

};


