#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "fakes/fff.h"

extern "C"{
#include "runtime.h"
#include "main.h"
}

#include "fakes/mock_runtime.h"
#include "fakes/mock_Arduino.h"
#include "fakes/mock_serial.h"

DEFINE_FFF_GLOBALS;

TEST_CASE( "main_execution", "[main]" ) 
{
   setup();

   
}