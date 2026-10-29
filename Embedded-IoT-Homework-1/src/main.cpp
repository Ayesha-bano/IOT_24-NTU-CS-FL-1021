#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

// ESP32 GPIO pins
const int BUTTON_PIN = 18;

// Create the OLED display object
Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

// Button states: HIGH = released, LOW = pressed
int lastRawButtonState = HIGH;
int stableButtonState = HIGH;

// Debounce timing
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_INTERVAL = 40;

// Press counter
unsigned long pressCount = 0;

// OLED refresh control
bool displayNeedsUpdate = true;

void updateOLED() {
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("ESP32 BUTTON MONITOR");

    display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

    display.setCursor(0, 22);
    display.print("Status: ");

    if (stableButtonState == LOW) {
        display.println("PRESSED");
    } else {
        display.println("RELEASED");
    }

    display.setCursor(0, 40);
    display.print("Count: ");
    display.println(pressCount);

    display.display();
}

void setup() {
    Serial.begin(115200);

    // Button connects GPIO 18 to GND when pressed
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Initialize I2C: SDA = GPIO 21, SCL = GPIO 22
    Wire.begin(21, 22);

    if (!display.begin(
            SSD1306_SWITCHCAPVCC,
            OLED_ADDRESS)) {
        Serial.println("ERROR: OLED initialization failed!");
        while (true) {
            // Stop if the OLED cannot initialize
        }
    }

    display.clearDisplay();
    updateOLED();

    Serial.println("ESP32 OLED Button Monitor Started");
    Serial.println("Press count: 0");
}

void loop() {
    // Read the current electrical state of the button
    int rawButtonState = digitalRead(BUTTON_PIN);

    // Detect a raw state change and restart the debounce timer
    if (rawButtonState != lastRawButtonState) {
        lastDebounceTime = millis();
        lastRawButtonState = rawButtonState;
    }

    // Accept the new state only after it remains stable
    // for the complete debounce interval.
    if (millis() - lastDebounceTime >= DEBOUNCE_INTERVAL) {

        if (rawButtonState != stableButtonState) {
            stableButtonState = rawButtonState;
            displayNeedsUpdate = true;

            // Count only the transition to PRESSED (LOW).
            // Holding the button does not increment the count.
            if (stableButtonState == LOW) {
                pressCount++;

                Serial.print("Accepted press count: ");
                Serial.println(pressCount);
            }
        }
    }

    // Refresh the OLED only when its displayed data changes
    if (displayNeedsUpdate) {
        updateOLED();
        displayNeedsUpdate = false;
    }
}