# Embedded IoT Systems - Homework 2
## Dual-LED PWM Control with OLED Monitoring

**Name:** Ayesha Azhar
**Class:** BSCS 5th, Section A
**Registration No:** 24-NTU-CS-FL-1021
**Course:** Embedded IoT Systems

## Objective

An ESP32 fades two LEDs using two different PWM frequencies (LEDC peripheral). The live duty cycle (in percent) and the configured frequency of both LEDs are shown on an SSD1306 I2C OLED. The project was tested in Wokwi, built on real hardware and pushed to GitHub.

## Components

| Component | Quantity | Use |
|---|---|---|
| ESP32 DevKit board | 1 | Main controller, generates PWM |
| LED | 2 | LED 1 and LED 2 |
| Resistor (330 ohm on hardware) | 2 | One resistor per LED to limit current |
| SSD1306 I2C OLED (128x64) | 1 | Shows duty cycle and frequency |
| Breadboard and jumper wires | - | Connections |

## Wiring

| Part | ESP32 pin | Note |
|---|---|---|
| LED 1 (anode) via resistor | GPIO 18 | Cathode to GND |
| LED 2 (anode) via resistor | GPIO 19 | Cathode to GND |
| OLED SDA | GPIO 21 | I2C data |
| OLED SCL | GPIO 22 | I2C clock (address 0x3C) |
| OLED VCC | 3V3 | Check module voltage first |
| OLED GND | GND | |

Each LED has its own separate resistor.

## PWM Settings

| LED | Frequency | Resolution | Duty range |
|---|---|---|---|
| LED 1 | 1000 Hz | 10 bit | 0 to 1023 |
| LED 2 | 5000 Hz | 10 bit | 0 to 1023 |

## Duty-Cycle Control

- The variables `duty1` and `duty2` store the current duty value of each LED.
- In every loop each duty value is changed by a step (4 for LED 1, 8 for LED 2).
- At the maximum (1023) the step becomes negative and the LED fades down; at 0 it fades up again.
- Because the steps are different, the two LEDs fade at different speeds.
- Percentage shown on the OLED = `duty x 100 / 1023`.

## LEDC Timer Sharing (Technical Check)

The ESP32 LEDC has 16 PWM channels, but only 4 timers in each group. Channels using the same timer must use the same frequency and resolution. In Arduino-ESP32 core 2.x, channel 0 and channel 1 share timer 0, so LED 1 uses channel 0 and LED 2 uses channel 2. They then use different timers and can have different frequencies.

## Duty Cycle and Frequency

- **Duty cycle** is the percentage of time the signal is ON in one cycle. A higher duty cycle gives a brighter LED.
- **Frequency** is the number of ON/OFF cycles per second. LED 1 (1000 Hz) has a period of 1 ms and LED 2 (5000 Hz) has a period of 0.2 ms. For the same duty cycle, both LEDs have almost the same brightness.

## OLED Output

The OLED is refreshed in every loop, right after the new duty values are applied to the LEDs, so the values shown are the values actually used by the program.

```
PWM MONITOR
LED1: 25% F:1000Hz
LED2: 75% F:5000Hz
```

(The numbers are an example. The real values change while the LEDs fade.)

Libraries used: Adafruit SSD1306 and Adafruit GFX.

## Project Structure

```
Embedded-IoT-Homework-2/
|-- diagram.json
|-- wokwi.toml
|-- platformio.ini
|-- src/
|   |-- main.cpp
|-- screenshots/
|   |-- wokwi_circuit.png
|   |-- wokwi_running_oled.png
|   |-- hardware_circuit.jpg
|   |-- hardware_oled_output.jpg
|-- README.md
```

## Wokwi Simulation

Wokwi project link: _add your Wokwi link here_

![Wokwi circuit](screenshots/wokwi_circuit.png)

![Wokwi running with OLED](screenshots/wokwi_running_oled.png)

## Hardware Implementation

The same circuit was built on a breadboard with the ESP32 board, two LEDs, two 330 ohm resistors and the SSD1306 OLED.

![Hardware circuit](screenshots/hardware_circuit.jpg)

![Hardware OLED output](screenshots/hardware_oled_output.jpg)

## Test Results

- Both LEDs fade smoothly from minimum to maximum brightness and back.
- The OLED shows changing duty cycles and the two configured frequencies.
- The same results were seen in Wokwi and on hardware.

## Wokwi vs Hardware

| Point | Wokwi | Hardware |
|---|---|---|
| LED fading | Both LEDs fade | Both LEDs fade |
| OLED values | Update correctly | Update correctly |
| Pins | GPIO 18, 19, 21, 22 | Same pins |
| Wiring | No wiring mistakes possible | Wires and resistor values must be checked |
| PWM frequency | Not visible by eye | Not visible by eye |

## GitHub Commits

| Order | Commit message | What was pushed |
|---|---|---|
| 1 | `task1 completed` | Task 1 files: two-LED PWM fading, diagram.json, wokwi.toml, platformio.ini, main.cpp |
| 2 | `complete homework` | OLED code, final files, screenshots, hardware photos and README.md |

## Conclusion

Two LEDs were controlled with two different PWM frequencies (1000 Hz and 5000 Hz) using the ESP32 LEDC peripheral, and their live duty cycle and frequency were shown on an SSD1306 OLED. The project worked in Wokwi and on real hardware.
