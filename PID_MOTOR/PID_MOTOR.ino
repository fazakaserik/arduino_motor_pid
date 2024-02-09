// Libraries
#include <math.h>

// Custom headers
#include "pins.h"
#include "constants.h"
#include "Encoder.h"
#include "motor.h"

// Global variables
Encoder* encoder = nullptr;
Motor* motor = nullptr;

volatile long t_prev = 0;
volatile int err_prev = 0;
volatile float err_integral = 0;
volatile int filtered_err_prev = 0;

void setup() {
  Serial.begin(19200);

  motor = Motor::getInstance();
  motor->setup(MOTOR_PLUS, MOTOR_MINUS);

  encoder = Encoder::getInstance();
  encoder->setup(ENCODER_A_PHASE, ENCODER_B_PHASE);
}

void loop() {
  // Update parameters
  int set_point = map(analogRead(POT_SP), 0, 1023, 0, 2000);
  float K_P = map(analogRead(POT_P), 0, 1023, 0, 1000)/100.0;
  float K_I = map(analogRead(POT_I), 0, 1023, 0, 1000)/100.0;
  float K_D = map(analogRead(POT_D), 0, 1023, 0, 1000)/100.0;

  long t_curr = micros();
  float t_delta = ((float) (t_curr - t_prev))/( 1.0e6 );
  t_prev = t_curr;
  
  int err = constrain(set_point - encoder->getCounterValue(), -255, 255);
  
  // Apply low-pass filter
  const float alpha = 0.4;
  int filtered_err = filtered_err_prev * alpha + err * (1 - alpha);

  err_integral = constrain(err_integral + filtered_err * t_delta, -INTEGRAL_MAX, INTEGRAL_MAX);

  float P = filtered_err * K_P;
  float I = err_integral * K_I;
  float D = (filtered_err-err_prev)/t_delta * K_D;

  int control_signal = (int) constrain(round(P + I + D), -CONTROL_SIGNAL_MAX, CONTROL_SIGNAL_MAX);

  motor->setSpeed(control_signal);

  err_prev = filtered_err;
  filtered_err_prev = filtered_err;

  // Arduino Plotter Fix
  Serial.print("Min:");
  Serial.print(0);
  Serial.print(",");
  Serial.print("Max:");
  Serial.print(2000);
  Serial.print(",");
  // Signals
  Serial.print("Set point:");
  Serial.print(set_point);
  Serial.print(",");
  Serial.print("Encoder:");
  Serial.println(encoder->getCounterValue());
}
