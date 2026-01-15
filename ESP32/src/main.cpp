#include <Arduino.h>
#include <HardwareSerial.h>


unsigned long previousMillis = millis();
HardwareSerial SerialESP32(2);
const byte rxpin = 16;
const byte txpin = 17;


void setup()
{
    Serial.begin(115200);
    //SerialESP32.begin(115200);
    SerialESP32.begin(115200,SERIAL_8E1,rxpin,txpin);

    while (!Serial && !SerialESP32);

    Serial.println("Hello World");
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > (300 * 1))
    {
        previousMillis = currentMillis;
        Serial.println("Hello Serial Monitor");
        SerialESP32.println("Hello PulseView");
    }
}