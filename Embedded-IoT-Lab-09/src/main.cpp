#include <Arduino.h>

#define DAC_PIN 25
#define PWM_PIN 18

#define PWM_CHANNEL 0
#define PWM_FREQUENCY 5000
#define PWM_RESOLUTION 8

void setup()
{
    Serial.begin(115200);

    Serial.println("Task 6: DAC and PWM");

    // Configure PWM
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);

    ledcAttachPin(PWM_PIN, PWM_CHANNEL);
}

void loop()
{
    // Increase brightness
    for (int value = 0; value <= 255; value++)
    {
        // DAC output on GPIO25
        dacWrite(DAC_PIN, value);

        // PWM output on GPIO18
        ledcWrite(PWM_CHANNEL, value);

        delay(20);
    }

    // Decrease brightness
    for (int value = 255; value >= 0; value--)
    {
        dacWrite(DAC_PIN, value);

        ledcWrite(PWM_CHANNEL, value);

        delay(20);
    }
}