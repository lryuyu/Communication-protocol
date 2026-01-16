#include <Arduino.h>
unsigned long previousMillis = millis();

void setup() {
    Serial.begin(115200);
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= (500))
    {
        previousMillis = currentMillis;
        //70 69 78 65 6C 65 64 69
        // Serial.write(0x70);
        // Serial.write(0x69);
        // Serial.write(0x78);
        // Serial.write(0x65);
        // Serial.write(0x6C);
        // Serial.write(0x65);
        // Serial.write(0x64);
        // Serial.write(0x69);

        //LSB
        // Serial.write(0b01100101);
        // Serial.write(0b01100100);
        // Serial.write(0b01101001);

        //MSB
        Serial.write(0b10100110);
        Serial.write(0b00100110);
        Serial.write(0b10010110);
    }

}