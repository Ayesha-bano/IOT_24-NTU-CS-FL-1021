# Embedded IoT Systems - Homework 1

**Name:** Ayesha Azhar
**Class:** BSCS 5th, Section A
**Registration No:** 24-NTU-CS-FL-1021
**Course:** Embedded IoT Systems

## Project Description

This project runs an SSD1306 OLED status screen on an ESP32. A push button is connected to GPIO 18 and is debounced without `delay()`, using `millis()`.

- On start-up the OLED shows the title, `Button: RELEASED` and `Count: 0`.
- Each accepted button press increases the counter by one.
- The OLED is updated with the button state (PRESSED / RELEASED) and the new count.
- The accepted count is also printed on the Serial Monitor (115200 baud).

## Components

| Component | Quantity |
|---|---|
| ESP32 DevKit (esp32dev) | 1 |
| Push button | 1 |
| SSD1306 I2C OLED (128x64) | 1 |
| Breadboard and jumper wires | - |

## Wiring

| Part | ESP32 pin | Note |
|---|---|---|
| Button (one side) | GPIO 18 | `INPUT_PULLUP`, pressed = LOW |
| Button (other side) | GND | |
| OLED VCC | 3.3V | Power |
| OLED GND | GND | Ground |
| OLED SDA | GPIO 21 | I2C data |
| OLED SCL | GPIO 22 | I2C clock (OLED address 0x3C) |

## How It Works

- **setup():** starts Serial, sets GPIO 18 as `INPUT_PULLUP`, starts I2C on GPIO 21/22, initializes the OLED at 0x3C and draws the first screen (count = 0).
- **loop():** reads the button pin and restarts a stability timer whenever the raw value changes. A new state is accepted only after it stays the same for 50 ms. The counter increases once on the accepted HIGH to LOW change (button press), prints the count to Serial, and sets a flag so the OLED is redrawn only when something changed.
- **No blocking delay:** there is no `delay()` in `loop()`, so the program stays responsive.

## Project Structure

```
Embedded-IoT-Homework-1/
|-- platformio.ini
|-- diagram.json
|-- wokwi.toml
|-- src/
|   |-- main.cpp
|-- screenshots/
|   |-- wokwi_circuit.png
|   |-- platformio_build.png
|   |-- hardware_setup.jpg
|   |-- hardware_output.jpg
|   |-- serial_monitor.png
|-- README.md
```

PlatformIO settings: board `esp32dev`, framework Arduino, libraries Adafruit GFX, Adafruit SSD1306 and Adafruit BusIO.

## Wokwi Simulation

Wokwi project link: _add your Wokwi link here_

![Wokwi circuit](screenshots/wokwi_circuit.png)

## VS Code / PlatformIO

![PlatformIO build](screenshots/platformio_build.png)

## Hardware

![Hardware setup](screenshots/hardware_setup.jpg)

![Hardware output](screenshots/hardware_output.jpg)

## Test Results

- The OLED shows the title, the button state and the press count.
- One physical press increases the count by exactly one (no double counting from bounce).
- The Serial Monitor prints the accepted count after each press.

![Serial monitor](screenshots/serial_monitor.png)

## Conclusion

The button is read with `INPUT_PULLUP` and debounced with `millis()` (50 ms), so presses are counted correctly without blocking the program. The OLED and Serial Monitor both show the same count.
