#include <Arduino.h>

#include "main.hpp"
#include "led.h"
#include "debug.h"
#include "wifi-connection.hpp"
#include "ota-handler.hpp"
#include "metronome.hpp"

const int LOOP_DURATION = 5000;
const int BLINK_INTERVAL = LOOP_DURATION / 2;

Metronome metronome(LOOP_DURATION);

// cppcheck-suppress unusedFunction
void setup()
{

  initDebugging();

  pinMode(led_built_in_ESP, OUTPUT);
  pinMode(led_built_in_Node, OUTPUT);
  digitalWrite(led_built_in_Node, HIGH);
  digitalWrite(led_built_in_ESP, HIGH);

  std::list<WifiDependent *> deps(1);
  deps.push_back(&OtaHandler::getInstance());

  WifiConnection::getInstance().init(deps);
}

// cppcheck-suppress unusedFunction
void loop()
{
  blinkLed();
  OtaHandler::getInstance().handleUpload();
}

void blinkLed()
{
  digitalWrite(led_built_in_Node, LOW);
  delay(BLINK_INTERVAL);
  digitalWrite(led_built_in_Node, HIGH);

  metronome.waitForNextCycle();

  DEBUG_PRINT("Loop ended at: ");
  DEBUG_PRINTLN(millis());
}
