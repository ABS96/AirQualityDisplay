#include <Arduino.h>
#include <unity.h>

extern "C"
{
#include <led.h>
}

void test_led_blue()
{
  TEST_ASSERT_EQUAL(LOW, digitalRead(pin_led[led_blue]));
}

void setup()
{
  UNITY_BEGIN();
  pinMode(pin_led[led_blue], OUTPUT);
  pinMode(pin_led[led_red], OUTPUT);
  pinMode(pin_led[led_yellow], OUTPUT);
  pinMode(pin_led[led_green], OUTPUT);
}

void loop()
{
  static uint8_t i = 0;
  static uint8_t max_loops = 10;

  if (i < max_loops)
  {
    setLeds(pin_led[led_blue], pin_led[led_green], pin_led[led_yellow], pin_led[led_red], blue);
    RUN_TEST(test_led_blue);
    delay(500);
    setLeds(pin_led[led_blue], pin_led[led_green], pin_led[led_yellow], pin_led[led_red], red);
    delay(500);
    setLeds(pin_led[led_blue], pin_led[led_green], pin_led[led_yellow], pin_led[led_red], yellow);
    delay(500);
    setLeds(pin_led[led_blue], pin_led[led_green], pin_led[led_yellow], pin_led[led_red], green);
    delay(500);
    digitalWrite(pin_led[led_blue], true);
    analogWrite(pin_led[led_red], 0);
    analogWrite(pin_led[led_yellow], 0);
    analogWrite(pin_led[led_green], 0);
    delay(500);
    ++i;
  }
  else
  {
    UNITY_END();
  }
}