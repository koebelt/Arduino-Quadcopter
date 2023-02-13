#include <Arduino.h>
#include "mpu6050.h"
#include "serial_management.h"
#include "motor.h"
#include "config.h"

MotorManager *motors;
unsigned long throttle = 1000;

void setup() {
  Serial.begin(9600);
  mpu6050_setup();
  motors = new MotorManager(4, 5);
  motors->start();
  // put your setup code here, to run once:
}

void loop() {
  // Serial.println("Hello World");

  handleCommands();
  mpu6050_loop();
  motors->doCorrection(throttle, 0, 0, 0);
  motors->doCommand();

  // put your main code here, to run repeatedly:
}