#pragma once

#include <Arduino.h>
#include <transmision.h>
#include <modifiers.h>

void setup() {
    // put your setup code here, to run once:
    pinMode(PIN_LEVEL_WATER, INPUT_PULLUP);
    pinMode(PIN_PUMP, OUTPUT);
    pinMode(PIN_LAMP, OUTPUT);
    pinMode(PIN_HEATING, OUTPUT);
    pinMode(PIN_VENTILATION, OUTPUT);
    digitalWrite(PIN_PUMP, LOW);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    receive();
    checkWaterReachedLevel();
}
