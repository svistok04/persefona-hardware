#include <Arduino.h>
#include <transmission.h>
#include <actuators.h>
#include <sensors.h>

bool test = true;

void setup() {

    // put your setup code here, to run once:
    pinMode(PIN_LEVEL_WATER, INPUT_PULLUP);
    pinMode(PIN_PUMP, OUTPUT);
    pinMode(PIN_LAMP, OUTPUT);
    pinMode(PIN_HEATING, OUTPUT);
    pinMode(PIN_VENTILATION, OUTPUT);
    // digitalWrite(PIN_PUMP, LOW);
    Serial.begin(9600);
    dhtSetup();
}

void loop() {
    // put your main code here, to run repeatedly:
    static unsigned long lastSendTime = 0;
    if (millis() - lastSendTime > 1000) {
        lastSendTime = millis();
        readSensors();
        send();
        updatePumpProcess();
    }

    receive();
    // if (Serial.available() > 0) {
    //     char c = Serial.read();
    //     Serial.print(c);
    //     Serial.println("\n");
    //     test = !test;
    //     digitalWrite(5, test);
    // }
    // if (Serial.available() > 0) {
    //     char serialRead = Serial.read();
    //     test = !test;
    //     digitalWrite(PIN_LAMP, test);
    // }

    // if (pumpRunning) {
    //     checkWaterReachedLevel();
    // }
    // Serial.println(digitalRead(PIN_LEVEL_WATER));
}
