#include "led.h"

void setLeds(unsigned int pin_blue, unsigned int pin_green, unsigned int pin_yellow, unsigned int pin_red, enum Color color)
{
  int colorFlag = color_flag[color];
  digitalWrite(pin_blue, !(colorFlag >> 3 & 1) ? max_led_pwm[led_blue] & 1 : 0);
  analogWrite(pin_green, (colorFlag >> 2 & 1) ? max_led_pwm[led_green] : 0);
  analogWrite(pin_yellow, (colorFlag >> 1 & 1) ? max_led_pwm[led_yellow] : 0);
  analogWrite(pin_red, (colorFlag & 1) ? max_led_pwm[led_red] : 0);
}
