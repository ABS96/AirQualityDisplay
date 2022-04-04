# Air Quality Display

A simple LED-based air quality indicator to help you decide when to let in some fresh air or do outside activities.

Air quality data is collected from the [World Air Quality Index Project](https://aqicn.org), then displayed using 4 LEDs.

## Hardware requirements

- hardware
- NodeMCU microcontroller + USB cable
- 3× LED (red, yellow, green)
- 3× resistor
- breadboard
- jumper wires
- power supply (optional)

## Software requirements

- [Visual Studio Code](https://code.visualstudio.com)
- [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) for Visual Studio Code
- An [AQICN API](https://aqicn.org/api/) token

## How to use

1. Install Visual Studio Code and the PlatformIO extension
2. Clone this repository
3. Open the project folder in Visual Studio Code
4. [Generate an API token](https://aqicn.org/api/)
5. Edit your Wi-Fi credentials, geographical location, API token, and refresh rate (in minutes) at `src/settings_example.h`, then rename it to `settings.h`
6. Connect the microcontroller to your computer via a USB cable
7. Upload the program using PlatformIO and verify that it is working correctly
8. Assemble the hardware
    1. Place the NodeMCU on the breadboard
    2. Place the red LED on the breadboard, install an appropriate resistor between its cathode and the ground rail, then connect its anode to pin `D1`
    3. Repeat step 2 with the yellow LED and pin `D2`
    4. Repeat step 2 with the green LED and pin `D3`
    5. Connect the ground rail to any pin marked `GND`
9. Verify that the hardware is working correctly (the function `testColors` may be used for debugging the LEDs)
