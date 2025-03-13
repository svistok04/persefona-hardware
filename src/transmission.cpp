#include "transmission.h"
#include <Arduino.h>
#include <sensors.h>



bool pumpReceived;
bool lampReceived;
bool heatingReceived;
bool ventilationReceived;
int timeReceived;


/// start reading after receiving *, read full message, stop at \ and append it back
void receive() {
    static char buffer[50];
    static int bufferIndex = 0;
    static bool receiving = false;

    while (Serial.available() > 0) {
        char incomingChar = Serial.read();

        if (incomingChar == '*') {
            receiving = true;
            bufferIndex = 0;
            //Serial.print("* received");
        }

        if (receiving) {
            if (bufferIndex < sizeof(buffer) - 2) {
                buffer[bufferIndex++] = incomingChar;
            } else if (incomingChar == '\\') {
                receiving = false;
                buffer[bufferIndex++] = '\0'; // append \ back
                parseMessage(buffer);
            }
        }
    }
}


/// parse until \ is reached
void parseMessage(const char* msg) {
    int pos = 1;  // Start after '*'

    while (msg[pos] != '\\' && msg[pos] != '\0') {
        switch (msg[pos]) {
            case 'p':  // pump
                pos += 2;
                pumpReceived = (msg[pos++] == '1');
                modifyPumpState(pumpReceived, 60);
            break;

            case 'l':  // lamp
                pos += 2;
                lampReceived = (msg[pos++] == '1');
                modifyLampState(lampReceived);
            break;

            case 'h':  // heating
                pos += 2;
                heatingReceived = (msg[pos++] == '1');
                modifyHeating(heatingReceived);
            break;

            case 'v':  // ventilation
                pos += 2;
                ventilationReceived = (msg[pos++] == '1');
                modifyVentilation(ventilationReceived);
            break;

            case 't':  // time, the number of digits read was not hardcoded
                pos += 2;
                timeReceived = 0;
                while (isdigit(msg[pos])) {
                    timeReceived = timeReceived * 10 + (msg[pos++] - '0');
                }
            break;

            default:
                pos++;
        }
    }
}

/// send
void send() {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "*gh%07.3fah%07.3fli%07.3fph%07.3fqu%07.3fit%07.3fot%07.3fti%07.3fpu%dla%dhe%dve%dgw%d\\",
             sensorSoilMoisture, sensorHumidity, sensorLight, sensorPH, sensorTurbidity,
             sensorTemperatureDHT, sensorTemperatureDS18B20, pumpRunTime, pumpRunning, lampState,
             heatingState, ventilationState, gatewayState);
    Serial.print(buffer);
}