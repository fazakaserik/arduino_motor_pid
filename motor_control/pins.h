#ifndef PINS_H
#define PINS_H


/* INPUTS */

// Potmeters
#define POT_1 A2
#define POT_2 A3
#define POT_3 A4
#define POT_4 A5

// Potmeter aliases
#define POT_SP POT_1
#define POT_P  POT_2
#define POT_I  POT_3
#define POT_D  POT_4


/* OUTPUTS */

// Encoder
#define ENCODER_A_PHASE 3 // ITR PIN on Arduino UNO
#define ENCODER_B_PHASE 2 // ITR PIN on Arduino UNO

// Motor
#define MOTOR_PLUS  11
#define MOTOR_MINUS 10


#endif