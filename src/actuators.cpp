#include <actuators.h>
#include <Arduino.h>
#include <sensors.h>
#include <transmission.h>

bool pumpRunning;
bool gatewayCountdownStarted;
float temperatureRange = 2.0; // acceptable temperature disparity

void modifyLampState(bool state) {
    digitalWrite(PIN_LAMP, state);
}

void modifyHeating() {
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


///

// void modifyPumpState(bool pumpReceived) { // command sent from C# to enable pump and close gateway
//     // possibly revert to a simpler version with turning on only
//
//     if (pumpReceived) {
//         closeGateway();
//         digitalWrite(PIN_PUMP, HIGH);
//         pumpRunning = pumpReceived;
//
//     } else {
//         closeGateway();
//     }
//     // pumpReceived = false;
// }
//
// void countdownGateway() { // time [s] start counting time right after pump stopping to open gateway
//     if (gatewayCountdownStarted) {
//         if (millis() - gatewayCountdownStartTime > timeReceived) {
//             openGateway();
//             gatewayCountdownStarted = false;
//             gatewayCountdownStartTime = millis();
//         }
//     }
// }
//
// void openGateway() {
//     digitalWrite(PIN_GATEWAY, HIGH);
//     // eventually if (gatewayCompletelyOpen) or after some time, then stop opening
//     // gatewayCountdownStarted = false;
//     // if (checkGatewayOpen()) {
//     //     digitalWrite(PIN_GATEWAY, LOW);
//     // }
// }
//
// void closeGateway() {
//     // gateway needs to be completely closed before pumping water begins
//     digitalWrite(PIN_GATEWAY, HIGH);
//     // if (gatewayCompletelyClosed) then stop closing
// }
//
// void checkWaterReachedLevel() {
//     if (digitalRead(PIN_LEVEL_WATER) == 0) {
//         digitalWrite(PIN_PUMP, LOW);
//         pumpRunning = false;
//         gatewayCountdownStarted = true;
//         gatewayCountdownStartTime = millis();
//     } else {
//     }
// }
//


// write version 2 logic: 2 funcs, where one activates on the received SW's command, while the other handles logic, updates times etc until stopped.

void modifyPumpState(bool pumpReceived, unsigned long pumpDurationReceived) {
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

void updatePumpProcess() {
    if (pumpRunning) {
        pumpRunTime = (millis() - pumpStartTime) * 1000;

        if (millis() - pumpStartTime >= pumpDuration) {
            digitalWrite(PIN_PUMP, LOW);
            pumpRunning = false;
        }
    }
}