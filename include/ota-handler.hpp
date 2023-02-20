#pragma once

#include "wifi-dependent.hpp"

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

  void handleUpload();
};
