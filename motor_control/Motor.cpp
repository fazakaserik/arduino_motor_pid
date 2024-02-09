#include "Motor.h"

Motor::Motor(uint8_t motorPlus_pin, uint8_t motorMinus_pin) : motorPlus_pin(motorPlus_pin), motorMinus_pin(motorMinus_pin) {}

void Motor::setup()
{
  pinMode(this->motorPlus_pin, OUTPUT);
  pinMode(this->motorMinus_pin, OUTPUT);
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