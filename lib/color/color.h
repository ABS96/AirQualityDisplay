#pragma once

typedef enum Color
{
  red,
  orange,
  yellow,
  green,
  blue,
  purple
} Color;

typedef struct AqiColor
{
  unsigned int aqi;
  enum Color color;
} AqiColor;

const AqiColor aqiForColor[6] = {{300, blue}, {200, purple}, {150, red}, {100, orange}, {50, yellow}, {0, green}};

Color getColorForAqi(unsigned int aqi);
