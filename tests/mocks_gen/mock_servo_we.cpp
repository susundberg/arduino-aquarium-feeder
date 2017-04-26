
/**
This is automatically generated mock file, see header file for more details.
*/


#include "mock_servo_we.h"
DEFINE_FAKE_VOID_FUNC( ServoWE__setup,  ServoWE*, int, int, int, int, int );
void ServoWE::setup(int pwm_pin, int enable_pin, int steps, int min_angle, int max_angle)  { ServoWE__setup(  this, pwm_pin, enable_pin, steps, min_angle, max_angle ); }
DEFINE_FAKE_VOID_FUNC( ServoWE__set_position,  ServoWE*, int, bool );
void ServoWE::set_position(int angle, bool direct)  { ServoWE__set_position(  this, angle, direct ); }
