#include <Arduino.h>

#define DAC_PIN 25

int values[] = {0, 64, 128, 192, 255};

void setup()
{
    Serial.begin(115200);

    Serial.println("DAC Stepped Output Program");
}

void loop()
{
    for (int i = 0; i < 5; i++)
    {
        dacWrite(DAC_PIN, values[i]);

        Serial.print("DAC Value: ");
        Serial.print(values[i]);

        float voltage = (values[i] / 255.0) * 3.3;

        Serial.print(" | Voltage: ");
        Serial.println(voltage);

        delay(1000);
    }
}