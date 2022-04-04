#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "main.h"

uint8_t PIN_ONBOARD_LED = D4; // Inverted
uint8_t PIN_RED_LED = D1;
uint8_t PIN_YELLOW_LED = D2;
uint8_t PIN_GREEN_LED = D3;

WiFiClient wifi;
HTTPClient http;

void initConnectivity()
{
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  bool blink = true;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    blink = !blink & 0x01;
    digitalWrite(PIN_ONBOARD_LED, blink);
    delay(250);
  }
  digitalWrite(PIN_ONBOARD_LED, HIGH);
  Serial.printf("\nConnected to %s", WIFI_SSID);
  Serial.print(" with IP address: ");
  Serial.println(WiFi.localIP());
  http.useHTTP10(true);
}

void setup()
{
  pinMode(PIN_ONBOARD_LED, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_YELLOW_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);
  Serial.begin(115200);
  initConnectivity();
}

unsigned int getAirQualityData()
{
  unsigned int aqi = 999;
  Serial.println("Getting air quality data...");
  http.begin(wifi, URL);
  int httpCode = http.GET();
  Serial.printf("[HTTP] %d\n", httpCode);
  if (httpCode > 0)
  {
    DynamicJsonDocument doc(3072);
    deserializeJson(doc, http.getStream());
    aqi = doc["data"]["aqi"].as<unsigned int>();
    Serial.print("Air quality index: ");
    Serial.print(aqi);
  }
  http.end();
  return aqi;
}

void updateAqiDisplay(unsigned int aqi)
{
  if (aqi > 300) // Hazardous, blue
  {
    setLeds(PIN_ONBOARD_LED, PIN_GREEN_LED, PIN_YELLOW_LED, PIN_RED_LED, blue);
    Serial.println(" (Hazardous)");
  }
  else if (aqi > 200) // Very Unhealthy, purple
  {
    setLeds(PIN_ONBOARD_LED, PIN_GREEN_LED, PIN_YELLOW_LED, PIN_RED_LED, purple);
    Serial.println(" (Very Unhealthy)");
  }
  else if (aqi > 150) // Unhealthy, red
  {
    setLeds(PIN_ONBOARD_LED, PIN_GREEN_LED, PIN_YELLOW_LED, PIN_RED_LED, red);
    Serial.println(" (Unhealthy)");
  }
  else if (aqi > 100) // Unhealthy for Sensitive Groups, orange
  {
    setLeds(PIN_ONBOARD_LED, PIN_GREEN_LED, PIN_YELLOW_LED, PIN_RED_LED, orange);
    Serial.println(" (Unhealthy for Sensitive Groups)");
  }
  else if (aqi > 50) // Moderate, yellow
  {
    setLeds(PIN_ONBOARD_LED, PIN_GREEN_LED, PIN_YELLOW_LED, PIN_RED_LED, yellow);
    Serial.println(" (Moderate)");
  }
  else
  { // Good, green
    setLeds(PIN_ONBOARD_LED, PIN_GREEN_LED, PIN_YELLOW_LED, PIN_RED_LED, green);
    Serial.println(" (Good)");
  }
}

void testColors()
{
  static unsigned int aqi = 0;
  Serial.printf("AQI = %d\n", aqi);
  updateAqiDisplay(aqi);
  aqi = (aqi + 50) % 400;
  delay(2000);
}

void loop()
{
  updateAqiDisplay(getAirQualityData());
  Serial.printf("Suspending for %d minutes\n", REFRESH_RATE);
  delay(REFRESH_RATE * 60000);
  // testColors();
}
