#ifndef MOTOR_H
#define MOTOR_H


#include <stdint.h>
#include <Arduino.h>


class Motor
{
  private:
    static Motor* instance;

    uint8_t motorPlus_pin;
    uint8_t motorMinus_pin;

    Motor();
  public:
    static Motor* getInstance();
    void setup(uint8_t motorPlus_pin, uint8_t motorMinus_pin);
    void setSpeed(int speed);
};


#endif // MOTOR_H