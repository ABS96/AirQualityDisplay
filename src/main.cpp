#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <color.h>
#include "main.h"

WiFiClient wifi;

void connectToWifi()
{
  static bool firstTime = true;
  Serial.print("Connecting to Wi-Fi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  bool blink = true;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    blink = !blink & 0x01;
    if (firstTime)
      digitalWrite(pin_led[led_blue], blink);
    delay(250);
  }
  digitalWrite(pin_led[led_blue], HIGH);
  Serial.printf("\nConnected to %s", WIFI_SSID);
  Serial.print(" with IP address: ");
  Serial.println(WiFi.localIP());
  firstTime = false;
}

void setup()
{
  pinMode(pin_led[led_blue], OUTPUT);
  pinMode(pin_led[led_red], OUTPUT);
  pinMode(pin_led[led_yellow], OUTPUT);
  pinMode(pin_led[led_green], OUTPUT);
  Serial.begin(115200);
  connectToWifi();
}

unsigned int getAirQualityData()
{
  HTTPClient http;
  unsigned int aqi = 999;
  Serial.print("Getting air quality data...");
  http.begin(wifi, URL);
  int httpCode = http.GET();
  Serial.printf(" [%d]\n", httpCode);
  if (httpCode > 0)
  {
    DynamicJsonDocument doc(3072);
    deserializeJson(doc, http.getStream());
    aqi = doc["data"]["aqi"].as<unsigned int>();
    Serial.printf("Air quality index: %d\n", aqi);
  }
  http.end();
  return aqi;
}

void updateAqiDisplay(unsigned int aqi)
{
  setLeds(pin_led[led_blue], pin_led[led_green], pin_led[led_yellow], pin_led[led_red], getColorForAqi(aqi));
}

void loop()
{
  updateAqiDisplay(getAirQualityData());
  Serial.printf("Suspending for %d minutes\n", REFRESH_RATE);
  WiFi.forceSleepBegin();
  delay(REFRESH_RATE * 60000);
  WiFi.forceSleepWake();
  delay(1);
  connectToWifi();
  Serial.println("Resuming");
}
