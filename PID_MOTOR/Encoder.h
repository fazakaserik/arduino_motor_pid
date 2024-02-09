#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"

class Encoder {
private:
    static Encoder* instance;
    static volatile long counter;
    static uint8_t encoderA_pin;
    static uint8_t encoderB_pin;

    Encoder(); // Private constructor

public:
    static Encoder* getInstance();
    void setup(uint8_t encoderA_pin, uint8_t encoderB_pin);
    int getCounterValue();
    void setCounterValue(int value);
    static void isrA();
    static void isrB();
};

#endif // ENCODER_H
