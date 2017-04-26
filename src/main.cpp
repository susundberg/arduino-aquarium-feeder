/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */


#include <Arduino.h>
#include <Servo.h>

#include "serial.h"
#include "runtime.h"

constexpr const int PIN_LED          = 13;
constexpr const int PIN_SERVO_ENABLE = 11;
constexpr const int PIN_SERVO_PWM    = 10;

constexpr const int PIN_DELAY_INPUT_1 = 9;
constexpr const int PIN_DELAY_INPUT_2 = 8;
constexpr const int PIN_DELAY_INPUT_4 = 7;
constexpr const int PIN_BUTTON        = 3;


#include "delay.h"
#include "stime.h"
#include "led.h"
#include "servo_we.h"

namespace SUPA
{
   StatusToLed LED;
   ServoWE     SERVO;
   DelayFromPin DELAY;
   TimeFromEeprom TIME;
   Runtime RUNTIME;
};

void setup()
{
   serial_setup( "Feeder" );
   SUPA::LED.setup( PIN_LED );
   SUPA::SERVO.setup( PIN_SERVO_PWM, PIN_SERVO_ENABLE, 20, 0, 1650 );
   SUPA::DELAY.setup( PIN_DELAY_INPUT_1, PIN_DELAY_INPUT_2, PIN_DELAY_INPUT_4);
   SUPA::TIME.setup();
   SUPA::RUNTIME.setup( &SUPA::DELAY, &SUPA::TIME, &SUPA::LED, &SUPA::SERVO, PIN_BUTTON );
}



void loop()
{
  SUPA::RUNTIME.loop();
  delay(50); // i guess we could do something more meaningfull here, like sleep.
}  
