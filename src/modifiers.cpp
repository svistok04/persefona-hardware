#include <Arduino.h>
#include <modifiers.h>
#include <transmision.h>


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