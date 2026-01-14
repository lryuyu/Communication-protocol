#include <Arduino.h>
const byte pvm1 = 5;
const byte pvm2 = 6;
const byte digital = 7;//数字输出

void setup() {
    Serial.begin(115200);
    pinMode(pvm1, OUTPUT);
    pinMode(pvm2, OUTPUT);
    pinMode(digital, OUTPUT);
    Serial.println("Hello World");
}

void loop() {
    delay(500);

    analogWrite(pvm1, 20);
    analogWrite(pvm2, 200);
    digitalWrite(digital, HIGH);
    delay(500);

    analogWrite(pvm1, 0);
    analogWrite(pvm2, 0);
    digitalWrite(digital, LOW);

    delay(500);
}