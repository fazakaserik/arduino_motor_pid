#include "Encoder.h"
#include <util/atomic.h>

Encoder::Encoder(uint8_t a_pin, uint8_t b_pin) : encoderA_pin(a_pin), encoderB_pin(b_pin), counter(0) {}

// Setup method definition
void Encoder::setup() {
    pinMode(this->encoderA_pin, INPUT);
    pinMode(this->encoderB_pin, INPUT);
}

void Encoder::registerInterruptHandlers(void (*isrA)(void), void (*isrB)(void)) {
    isrAHandler = isrA;
    isrBHandler = isrB;
    attachInterrupt(digitalPinToInterrupt(this->encoderA_pin), isrAHandler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(this->encoderB_pin), isrBHandler, CHANGE);
}

uint8_t Encoder::getEncoderAPin()
{
  return this->encoderA_pin;
}

uint8_t Encoder::getEncoderBPin()
{
  return this->encoderA_pin;
}

// Get counter value
int Encoder::getCounterValue() {
    int value;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        value = this->counter;
    }
    return value;
}

// Set counter value
void Encoder::setCounterValue(int value) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        this->counter = value;
    }
}

void Encoder::incrementCounterValue() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        this->counter++;
    }
}

void Encoder::decrementCounterValue() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        this->counter--;
    }
}
