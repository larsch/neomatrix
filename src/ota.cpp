/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * Over-the-air update
 */

#include "ota.hpp"
#include "text.hpp"
#include "display.hpp"
#include "ws2812_i2s.hpp"
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>

static void message(const char* msg)
{
  Serial.println(msg);
  mprint(msg);
  ws2812_show(pixels);
}

void ota_init()
{
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  Serial.println("Setting hostname");
  ArduinoOTA.setHostname("neomatrix");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  Serial.println("Registering onStart");
  ArduinoOTA.onStart([]() {
    message("Prgmng");
  });
  Serial.println("Registering onEnd");
  ArduinoOTA.onEnd([]() {
    message("Reboot");
  });
  Serial.println("Registering onProgress");
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  Serial.println("Registering onError");
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  Serial.println("Beginning OTA");
  ArduinoOTA.begin();
}

void ota_run()
{
  ArduinoOTA.handle();
}
