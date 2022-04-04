#pragma once

enum Color
{
  red,
  orange,
  yellow,
  green,
  blue,
  purple
};

enum Led
{
  led_red,
  led_yellow,
  led_green,
  led_blue
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

void setLeds(unsigned int pin_blue, unsigned int pin_green, unsigned int pin_yellow, unsigned int pin_red, enum Color color);
