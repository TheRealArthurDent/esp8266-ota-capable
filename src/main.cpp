#include "Arduino.h"

#include "main.hpp"
#include "led.h"
#include "debug.h"
#include "wifi-connection.hpp"
#include "ota-handler.hpp"

const int BLINK_INTERVAL = 2500;

// cppcheck-suppress unusedFunction
void setup()
{

  initDebugging();

  pinMode(led_built_in_ESP, OUTPUT);
  pinMode(led_built_in_Node, OUTPUT);
  digitalWrite(led_built_in_Node, HIGH);
  digitalWrite(led_built_in_ESP, HIGH);

  std::list<WifiDependent *> deps;
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
  delay(BLINK_INTERVAL);
}
