#pragma once
#include "settings.h"

extern "C"
{
#include "led.h"
}

#define URL "http://api.waqi.info/feed/geo:" LATITUDE ";" LONGITUDE "/?token=" API_TOKEN
