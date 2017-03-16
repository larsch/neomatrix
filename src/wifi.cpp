/*
 * Neomatrix - Copyright (C) 2017 Lars Christensen
 * MIT Licensed
 *
 * WiFi
 */

#include "wifi.hpp"
#include "ota.hpp"

#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

static bool wifiConnected = false;

void wifi_init()
{
  WiFiMulti.addAP("hal9k", "");
  WiFiMulti.addAP("naboen", "wonderfulworld");
}

void wifi_run()
{
  if (WiFiMulti.run() == WL_CONNECTED) {
    if (!wifiConnected) {
      Serial.print("Connected as ");
      Serial.println(WiFi.localIP());
      wifiConnected = true;
      ota_init();
    }
    if (wifiConnected) {
      ota_run();
    }
  }
}
