#include <Servo.h>
#include <Arduino.h>
#include "motor.h"


void MotorManager::start()
{
    Serial.println("Plug the motors in !!!");
    delay(5000);
    this->motA->start();
    this->motB->start();
    if (this->nbMotors == 4) {
        this->motC->start();
        this->motD->start();
    }
    Serial.println("too late");
}

void MotorManager::stop()
{
    this->motA->stop();
    this->motB->stop();
    if (this->nbMotors == 4) {
        this->motC->stop();
        this->motD->stop();
    }
}

void MotorManager::doCommand()
{
    this->motA->doCommand();
    this->motB->doCommand();
    if (this->nbMotors == 4) {
        this->motC->doCommand();
        this->motD->doCommand();
    }
}

void MotorManager::doCorrection(unsigned long throttle, float pidYaw, float pidRoll, float pidPitch)
{
    if (this->nbMotors == 4) {
        this->motA->setCommand(throttle + pidYaw + pidRoll - pidPitch);
        this->motB->setCommand(throttle - pidYaw - pidRoll - pidPitch);
        this->motC->setCommand(throttle - pidYaw + pidRoll + pidPitch);
        this->motD->setCommand(throttle + pidYaw - pidRoll + pidPitch);
    } else {
        this->motA->setCommand(throttle + pidRoll);
        this->motB->setCommand(throttle - pidRoll);
    }
}


unsigned long Motor::chechBoundaries(unsigned long command)
{
    if (started == false) {
        command = MOT_MINIMUM;
        return command;
    }
    if (command < MOT_START_MINIMUM)
    {
        command = MOT_START_MINIMUM;
    }
    if (command > MOT_MAX)
    {
        command = MOT_MAX;
    }
    return command;
}

void Motor::start() {
    
    this->serv.writeMicroseconds(MOT_MINIMUM);
    this->started = true;
}

void Motor::stop() {
    this->serv.writeMicroseconds(MOT_MINIMUM);
    this->started = false;
}

void Motor::doCommand() {
    this->serv.writeMicroseconds(this->ESC_command);
}



// void startESC()
// {
//     motA.attach(4, 1000, 2000);
//     motB.attach(5, 1000, 2000);
//     // indispensable pour signaler à l'ESC que un démarrage "normal" va se faire
//     // après on peut mettre le courant en route (connecter la batterie)

//     Serial.println(" TURN LIPO ON !!!: 5 sec pour le faire !!!");
//     delay(5000);
//     motA.writeMicroseconds(1000); // pour arrêter les bips
//     motB.writeMicroseconds(1000);
//     delay(5000);
//     motA.writeMicroseconds(1000); // pour arrêter les bips
//     motB.writeMicroseconds(1000);
//     motA.detach(); // pour libérer les broches de la classe SERVO et libérer le timer millis()
//     motB.detach(); // pour libérer les broches de la classe SERVO et libérer le timer millis()
// };

// void computeESC() {  // maintien d'assiette sans changer l'altitude : Mode Auto level
//     int correctionROLL = 0;
//     if(consigneGAZ <= consigneGAZ + MOT_START_MINIMUM ) {
//     consigneGAZ = consigneGAZ + MOT_START_MINIMUM;
//     };

//     if(consigneGAZ >= MOT_MAX - MOT_START_MINIMUM ) {
//     consigneGAZ = MOT_MAX - MOT_START_MINIMUM ;
//     };

//     ESC_A = consigneGAZ + correctionROLL;
//     ESC_B = consigneGAZ - correctionROLL;
// }



// void commandAllMotors() // créer le pulse de la largeur décidée par les PID Mixés pour chaque ESC
// {
//     // la cde moteur se fait au rythme nouvelle donnée FIFO cad 100 Hz; donc ICI sur 2 consignes identiques mais 2 mesures différentes
//     loop_timer = micros(); // Set the timer for the next loop.

//     PORTD |= B11110000;             // Set digital outputs 4,5,6 and 7 high.
//     timerMotA = ESC_A + loop_timer; // Calculate the time of the falling edge of the esc-A pulse.
//     timerMotB = ESC_B + loop_timer; // Calculate the time of the falling edge of the esc-B pulse.

//     // pour garder PORTD >= 16 .... force les pins 6 et 7 à low
//     PORTD &= B10111111; // Set digital output 6 to low
//     PORTD &= B01111111; // Set digital output 7 to low

//     while (PORTD >= 16)
//     {                              // Stay in this loop until output 4,5,6 and 7 are low.
//         esc_loop_timer = micros(); // Read the current time.
//         if (timerMotA <= esc_loop_timer)
//         {
//             PORTD &= B11101111; // Set digital output 4 to low if the time is expired.sans toucher aux pins 6 et 7
//         };
//         if (timerMotB <= esc_loop_timer)
//         {
//             PORTD &= B11011111; // Set digital output 5 to low if the time is expired sans toucher aux pins 6 et 7
//         };
//     }; // fin while
// };
