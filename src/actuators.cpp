#include <actuators.h>
#include <Arduino.h>
#include <transmission.h>

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

void countdownGateway() { // time [s] start counting time right after pump stopping to open gateway
    if (gatewayCountdownStarted) {
        if (millis() - gatewayCountdownStartTime > timeReceived) {
            openGateway();
            gatewayCountdownStarted = false;
            gatewayCountdownStartTime = millis();
        }
    }
}

void openGateway() {
    digitalWrite(PIN_GATEWAY, HIGH);
    // eventually if (gatewayCompletelyOpen) or after some time, then stop opening
    // gatewayCountdownStarted = false;
}

void closeGateway() {
    // gateway needs to be completely closed before pumping water begins
    digitalWrite(PIN_GATEWAY, HIGH);
    // if (gatewayCompletelyClosed) then stop closing
}

void checkWaterReachedLevel() {
    if (digitalRead(PIN_LEVEL_WATER) == 0) {
        digitalWrite(PIN_PUMP, LOW);
        pumpRunning = false;
        gatewayCountdownStarted = true;
        gatewayCountdownStartTime = millis();
    } else {
    }
}

void modifyPumpState(bool pumpReceived) { // command sent from C# to enable pump and close gateway
    // possibly revert to a simpler version with turning on only

    if (pumpReceived) {
        openGateway();
        digitalWrite(PIN_PUMP, pumpReceived);
        pumpRunning = pumpReceived;
    } else {
        closeGateway();
    }
    // pumpReceived = false;
}