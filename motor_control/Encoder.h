#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"

class Encoder {
private:
    volatile long counter;
    uint8_t encoderA_pin;
    uint8_t encoderB_pin;
    void (*isrAHandler)(void); // Function pointer for ISR A handler
    void (*isrBHandler)(void); // Function pointer for ISR B handler

public:
    Encoder(uint8_t encoderA_pin, uint8_t encoderB_pin); // Constructor with pin setup

    void setup();
    void registerInterruptHandlers(void (*isrA)(void), void (*isrB)(void));
    uint8_t Encoder::getEncoderAPin();
    uint8_t Encoder::getEncoderBPin();
    int getCounterValue();
    void setCounterValue(int value);
    void incrementCounterValue();
    void decrementCounterValue();
};

#endif // ENCODER_H
