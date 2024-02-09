#include "Motor.h"

Motor* Motor::instance = nullptr;

Motor::Motor() {}

Motor* Motor::getInstance()
{
  if (!instance)
  {
    instance = new Motor();
  }
  return instance;
}

void Motor::setup(uint8_t motorPlus_pin, uint8_t motorMinus_pin)
{
  pinMode(motorPlus_pin, OUTPUT);
  pinMode(motorMinus_pin, OUTPUT);

  this->motorPlus_pin = motorPlus_pin;
  this->motorMinus_pin = motorMinus_pin;
}

void Motor::setSpeed(int speed)
{
  speed = constrain(speed, -255, 255);
  if (speed >= 0)
  {
    analogWrite(this->motorPlus_pin, 0);
    analogWrite(this->motorMinus_pin, speed);
  }
  else
  {
    analogWrite(this->motorPlus_pin, abs(speed));
    analogWrite(this->motorMinus_pin, 0);
  }
}