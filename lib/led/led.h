#pragma once
#include <Arduino.h>
#include <color.h>

enum Led
{
  led_red,
  led_yellow,
  led_green,
  led_blue
};

const uint8_t pin_led[] = {
    [led_red] = 5,    // D1
    [led_yellow] = 4, // D2
    [led_green] = 0,  // D3
    [led_blue] = 2,   // LED_BUILTIN
};

const int max_led_pwm[] = {
    [led_red] = 255,
    [led_yellow] = 255,
    [led_green] = 100,
    [led_blue] = 255,
};

// (MSB)[blue, green, yellow, red](LSB)
const int color_flag[] = {
    [red] = 0b0001,
    [orange] = 0b0011,
    [yellow] = 0b0010,
    [green] = 0b0100,
    [blue] = 0b1000,
    [purple] = 0b1001,
};

void setLeds(unsigned int pin_blue, unsigned int pin_green, unsigned int pin_yellow, unsigned int pin_red, Color color);
