#include "Encoder.h"
#include <util/atomic.h>

// Define static variables
Encoder* Encoder::instance = nullptr;
volatile long Encoder::counter = 0;
uint8_t Encoder::encoderA_pin = 0;
uint8_t Encoder::encoderB_pin = 0;

// Private constructor
Encoder::Encoder() {}

// Singleton getInstance definition
Encoder* Encoder::getInstance() {
    if (instance == nullptr) {
        instance = new Encoder();
    }
    return instance;
}

// Setup method definition
void Encoder::setup(uint8_t a_pin, uint8_t b_pin) {
    encoderA_pin = a_pin;
    encoderB_pin = b_pin;
    pinMode(encoderA_pin, INPUT);
    pinMode(encoderB_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoderA_pin), isrA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderB_pin), isrB, CHANGE);
}

// ISR A definition
void Encoder::isrA() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (digitalRead(encoderA_pin) == digitalRead(encoderB_pin)) {
            counter++;
        } else {
            counter--;
        }
    }
}

// ISR B definition
void Encoder::isrB() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (digitalRead(encoderA_pin) != digitalRead(encoderB_pin)) {
            counter++;
        } else {
            counter--;
        }
    }
}

// Get counter value
int Encoder::getCounterValue() {
    int value;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        value = counter;
    }
    return value;
}

// Set counter value
void Encoder::setCounterValue(int value) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        counter = value;
    }
}
