/*
 * filename: wifi_setup.ino
 */
#include <ArduinoOTA.h>
#include <WiFi.h>
#include "heltec.h"

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}

void setupWifi(const char *ssid, const char *password)
{
  WiFi.begin(ssid, password);
  Serial.print("WiFi connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }


  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->drawString(0, 0, "Connected to WiFi");
  Heltec.display->drawString(0, 10, "IP: " + IpAddress2String(WiFi.localIP()));
  Heltec.display->display();

  
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
