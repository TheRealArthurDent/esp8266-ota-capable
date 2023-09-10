#include "app.hpp"

#include "Arduino.h"
#include "led.h"
#include "wifi-connection.hpp"
#include "ota-handler.hpp"
#include "alert.hpp"
#include "debug.h"

#include <string>

App::App() : metronome(Metronome(LOOP_DURATION)), masterCaution(MasterCaution())
{
}

void App::setup()
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

void App::loop()
{
    blinkLed();
    OtaHandler::getInstance().handleUpload();
}

void App::blinkLed()
{
    digitalWrite(led_built_in_Node, LOW);
    delay(BLINK_INTERVAL);
    digitalWrite(led_built_in_Node, HIGH);

    metronome.waitForNextCycle();

    if (masterCaution.isAlarming())
    {
        DEBUG_PRINTLN("!!! MASTER CAUTION !!!");
        std::vector<Alert *> activeAlerts = masterCaution.getActiveAlerts();
        std::for_each(activeAlerts.begin(), activeAlerts.end(), [this](Alert *a)
                      { DEBUG_PRINT("!! CAUTION: "); DEBUG_PRINTLN(a->toString().c_str()); });
        DEBUG_PRINTLN("!!! MASTER CAUTION !!!");
    }

    DEBUG_PRINT("Loop ended at: ");
    DEBUG_PRINTLN(millis());
}
