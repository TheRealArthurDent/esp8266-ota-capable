#pragma once

#include "wifi-dependent.hpp"

/**
 * \brief A handler that takes care of over-the-air updates of your controller.
 *
 * This controller will accept authorized uploads to your controller on the ota
 * port configured via \code SECRET_OTA_PORT \endcode.
 * The controller will simply delegate uploads to
 * <a href="https://github.com/esp8266/Arduino/tree/master/libraries/ArduinoOTA">ArduinoOTA</a>.
 */
class OtaHandler : public WifiDependent
{

  bool ready = false;

  // Singleton "constructor"
public:
  static auto getInstance() -> OtaHandler &
  {
    static OtaHandler instance;
    return instance;
  }
  // hide constructor, copy constructor and = operator
private:
  OtaHandler() = default;             // hide default constructor
  OtaHandler(OtaHandler const &);     // Don't implement.
  void operator=(OtaHandler const &); // Don't implement.

  // normal methods
public:
  void onWifiConnectionEstablished() override;

  const void handleUpload();
};
