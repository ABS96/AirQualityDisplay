#include "color.h"

Color getColorForAqi(unsigned int aqi)
{
  enum Color color = blue;
  for (int i = 0; i < 6; ++i)
  {
    color = aqiForColor[i].color;
    if (aqiForColor[i].aqi < aqi)
      break;
  }
  return color;
}