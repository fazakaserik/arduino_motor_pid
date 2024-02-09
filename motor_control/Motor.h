#ifndef MOTOR_H
#define MOTOR_H


#include <stdint.h>
#include <Arduino.h>


class Motor
{
  private:
    uint8_t motorPlus_pin;
    uint8_t motorMinus_pin;
  public:
    Motor(uint8_t motorPlus_pin, uint8_t motorMinus_pin);
    void setup();
    void setSpeed(int speed);
};


#endif // MOTOR_H