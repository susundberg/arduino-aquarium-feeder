#ifndef FAKE_ARDUINO_H
#define FAKE_ARDUINO_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


#define LED_BUILTIN 13

/* Values for pin reads and writes */
static const int HIGH = 1;
static const int LOW = 0;

/* Values for pin modes */
static const uint8_t INPUT = 0;
static const uint8_t OUTPUT = 1;
static const uint8_t INPUT_PULLUP = 2;

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
void delay(unsigned long milliseconds);


/**
int analogRead(uint8_t pin);
void analogWrite(uint8_t pin, int value);


void randomSeed(unsigned int seed);
long random(long max);
long random(long min, long max);
unsigned long micros();
unsigned long millis();
int digitalRead(uint8_t pin);
*/
#endif