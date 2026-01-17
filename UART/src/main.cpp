#include <Arduino.h>
#include <SoftwareSerial.h>

const byte rxPin = 5;
const byte txPin = 6;
SoftwareSerial arduinoSerial (txPin, txPin);
void setup() {
    Serial.begin(115200);
    arduinoSerial.begin(9600);
}

void loop() {

    Serial.println("Hello Pulse");
    arduinoSerial.println("Hello PulseView Serial");
    delay(500);
}