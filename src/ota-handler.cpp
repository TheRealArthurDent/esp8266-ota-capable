#include "ota-handler.hpp"
#include "debug.h"
#include "ArduinoOTA.h"

/********************************************************
 * Yes! You are absolutely right! This is ugly as ****. *
 * But who cares as long as it works, right?            *
 ********************************************************/

// cppcheck-suppress unusedFunction
void OtaHandler::onWifiConnectionEstablished()
{
  DEBUG_PRINTLN("OtaHandler connected!");

  ArduinoOTA.setPassword(SECRET_OTA_PASSWORD);
  ArduinoOTA.setPort(8266);

  ArduinoOTA.onStart([]()
                     {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    DEBUG_PRINTLN("Start updating " + type); });
  ArduinoOTA.onEnd([]()
                   { DEBUG_PRINTLN("\nEnd"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        { DEBUG_PRINTF("Progress: %u%%\r", (progress / (total / 100))); });
  ArduinoOTA.onError([](ota_error_t error)
                     {
    DEBUG_PRINTF("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      DEBUG_PRINTLN("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      DEBUG_PRINTLN("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      DEBUG_PRINTLN("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      DEBUG_PRINTLN("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      DEBUG_PRINTLN("End Failed");
    } });
  ArduinoOTA.begin();
  ready = true;

  DEBUG_PRINTLN("ArduinoOTA ready.");
}

void OtaHandler::handleUpload()
{
  if (ready)
  {
    DEBUG_PRINTLN("handleUpload");
    ArduinoOTA.handle();
  }
  else
  {
    DEBUG_PRINTLN("OtaHandler is not yet ready to accept uploads.");
  }
}
