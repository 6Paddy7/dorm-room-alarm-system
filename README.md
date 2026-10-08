# Dorm room alarm system

A door alarm for my dorm room. You arm it from a keypad, an ultrasonic sensor beside the door detects someone entering, and if the code isn't typed in time, a buzzer sounds and a notification is sent over Wi-Fi.

v2 of the alarm, rebuilt on an ESP32-S3 with ESP-IDF. v1 ran on an Arduino and worked, but had a 2-second exit delay, unlimited code attempts, a hardcoded code and no notifications.

**Status:** work in progress (M0: toolchain).

## Hardware
- ESP32-S3 DevKitC-1 (N16R8 module)
- HC-SR04 ultrasonic distance sensor
- 4x4 matrix keypad
- 20x4 character LCD with I2C backpack
- Passive piezo buzzer (about 4 kHz resonance)
- Breadboard, jumper wires, 1 kΩ and 2 kΩ resistors (voltage divider for the HC-SR04's Echo pin)

## Build
- ESP-IDF v6.1, target esp32s3 (set in `sdkconfig.defaults`)
- `idf.py -p /dev/ttyACM0 flash monitor` (your port may differ)

## VS Code setup (once per clone)
Uses the official ESP-IDF extension.
1. Open the repo folder itself, not its parent folder.
2. Disable the CMake Tools extension for this workspace, then reload the window.
3. Click `ESP-IDF InvalidSetup` in the status bar and select ESP-IDF v6.1.
4. Set the port (e.g. `/dev/ttyACM0`) and the flash method (UART) in the status bar.
5. Build, flash and monitor with the status bar buttons.