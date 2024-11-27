#include <Arduino.h>
#include <transmision.h>

#define PIN_PUMP 3
#define PIN_LEVEL_WATER 4
#define PIN_GATEWAY 4
#define PIN_LAMP 5
#define PIN_HEATING 6
#define PIN_VENTILATION 7

bool pumpRunning;
bool gatewayCountdownStarted;
unsigned long gatewayCountdownStartTime;

void modifyLampState(bool state) {
    digitalWrite(PIN_LAMP, state);
}

void modifyHeating(bool state) {
    digitalWrite(PIN_HEATING, state);
}

void modifyVentilation(bool state) {
    digitalWrite(PIN_VENTILATION, state);
}

void modifyGateway() { // time [s] start counting time right after pump stopping to open gateway
    if (gatewayCountdownStarted) {
        if (millis() - gatewayCountdownStartTime > timeReceived) {
            digitalWrite(PIN_GATEWAY, LOW);
            gatewayCountdownStarted = false;
        }
    }
}

void checkWaterReachedLevel() {
    if (pumpRunning && digitalRead(PIN_LEVEL_WATER) == 0) {
        digitalWrite(PIN_PUMP, LOW);
        pumpRunning = false;
        gatewayCountdownStarted = true;
        gatewayCountdownStartTime = millis();
    } else {
        modifyGateway();
    }
}

void modifyPumpState() { // command sent from C# to enable pump and close gateway
    digitalWrite(PIN_GATEWAY, HIGH);
    digitalWrite(PIN_PUMP, HIGH);
    pumpRunning = true;
    pumpReceived = false;
}

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
