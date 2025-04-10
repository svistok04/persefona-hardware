#include <actuators.h>
#include <Arduino.h>
#include <sensors.h>
#include <transmission.h>

bool pumpRunning;
bool lampState;
bool gatewayState;
bool heatingState;
bool ventilationState;
float temperatureRange = 2.0; // acceptable temperature disparity

bool pumpModeVersion1 = false;
// v1
bool gatewayCountdownStarted;
bool gatewayIsClosing;
unsigned long gatewayCountdownStartTime;
unsigned long gatewayClosedTime;
void modifyPumpState(bool pumpReceived) { // command sent from C# to enable pump and close gateway
    // possibly revert to a simpler version with turning on only

    if (pumpReceived) {
        closeGateway();
        digitalWrite(PIN_PUMP, HIGH);
        pumpRunning = pumpReceived;
    } else {
        // closeGateway();
    }
    // pumpReceived = false;
}

void countdownGateway() { // time [s] start counting time right after pump stopping to open gateway
    if (gatewayCountdownStarted) {
        if (millis() - gatewayCountdownStartTime > timeReceived * 1000) {
            openGateway();
            gatewayCountdownStarted = false;
        }
    }
}

void openGateway() {
    // gateway needs to be open before continue, so we wait 5s (?)
    // add direction
    digitalWrite(PIN_GATEWAY, HIGH);
    // add counter here to check?
}

void closeGateway() {
    // gateway needs to be completely closed before pumping water begins
    gatewayIsClosing = true;
    // in actual program, continue in loop():
    // if (!checkGatewayPosition) then stop closing and turn the pump on
    // add direction
    digitalWrite(PIN_GATEWAY, HIGH);
}

void stopGatewayClosing() {
    if (checkGatewayClosed()) {
        digitalWrite(PIN_GATEWAY, LOW);
        gatewayClosedTime = millis();
        gatewayCountdownStarted = true;
    }
}

void stopGatewayOpening() {
    // if counter -> stop
    digitalWrite(PIN_GATEWAY, LOW);
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

bool checkGatewayClosed() {
    bool isClosed{};
    // some sensor that detects whether the gateway is open or closed
    return isClosed;
}

// write version 2 logic: 2 funcs, where one activates on the received SW's command, while the other handles logic, updates times etc until stopped.

// v2
unsigned long pumpStartTime;
unsigned long pumpDuration;
unsigned long pumpRunTime;

void modifyPumpStateV2(bool pumpReceived, unsigned long pumpDurationReceived) {
    if (pumpReceived) {
        pumpDuration = pumpDurationReceived * 1000;
        digitalWrite(PIN_PUMP, HIGH);
        pumpStartTime = millis();
        pumpRunning = true;
    } else {
        digitalWrite(PIN_PUMP, LOW);
        pumpRunning = false;
    }
}

void updatePumpProcessV2() {
    if (pumpRunning) {
        pumpRunTime = (millis() - pumpStartTime) / 1000;

        if (millis() - pumpStartTime >= pumpDuration) {
            digitalWrite(PIN_PUMP, LOW);
            pumpRunning = false;
        }
    }
}

void modifyLampState(bool state) {
    digitalWrite(PIN_LAMP, state);
}

void modifyHeating(bool state) {
    static unsigned int lastHeatingCheck = 0;
    if (millis() - lastHeatingCheck > 60000) { // check every 1m
        lastHeatingCheck = millis();
        if (sensorTemperatureDS18B20 - desiredTemperature > -temperatureRange) {
            digitalWrite(PIN_HEATING, HIGH);
        } else if (sensorTemperatureDS18B20 - desiredTemperature > temperatureRange) {
            digitalWrite(PIN_HEATING, LOW);
        }
    }
}

void modifyVentilation(bool state) {
    digitalWrite(PIN_VENTILATION, state);
}
