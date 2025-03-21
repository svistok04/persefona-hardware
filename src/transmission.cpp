#include "transmission.h"
#include <Arduino.h>
#include <sensors.h>



bool pumpReceived;
bool lampReceived;
bool heatingReceived;
bool ventilationReceived;
float desiredTemperature;
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
            // Serial.println("* received");
        }

        if (receiving) {
            if (incomingChar == '\\') {
                receiving = false;
                buffer[bufferIndex++] = incomingChar;
                buffer[bufferIndex++] = '\0';
                Serial.println("Why can't i read \\");
                Serial.print("I received: ");
                Serial.println(buffer);
                parseMessage(buffer);
            } else if (bufferIndex < sizeof(buffer) - 2) {
                buffer[bufferIndex++] = incomingChar;
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
                Serial.println("Pump");
                modifyPumpState(pumpReceived, 5);
            break;

            case 'l':  // lamp
                Serial.println("Lamp");
                pos += 2;
                lampReceived = msg[pos++] == '1';
                // lampReceived ? Serial.println("True") : Serial.println("False");
                modifyLampState(lampReceived);
                // digitalWrite(5, lampReceived);
            break;

            case 'h':  // heating
                pos += 2;
                heatingReceived = msg[pos++] == '1';
                modifyHeating(heatingReceived);
            break;

            case 'v':  // ventilation
                pos += 2;
                Serial.println("Ventilation");
                ventilationReceived = msg[pos++] == '1';
                modifyVentilation(ventilationReceived);
            break;

            case 't':  // time, the number of digits read was not hardcoded
                pos += 2;
                timeReceived = 0;
                while (isdigit(msg[pos])) {
                    timeReceived = timeReceived * 10 + (msg[pos++] - '0');
                }
            break;
            default: pos++;
        }
    }
}

/// send
void send() {
    char buffer[100];

    snprintf(buffer, sizeof(buffer),
             "*gh%06dah%06dli%06dph%06dqu%06dit%06dot%06dti%dpu%dla%dhe%dve%dgw%d\\\n",
             (int)(sensorSoilMoisture * 1000),
             (int)(sensorHumidity * 1000),
             (int)(sensorLight * 1000),
             (int)(sensorPH * 1000),
             (int)(sensorTurbidity * 1000),
             (int)(sensorTemperatureDHT * 1000),
             (int)(sensorTemperatureDS18B20 * 1000),
             pumpRunTime, pumpRunning, lampState,
             heatingState, ventilationState, gatewayState);

    Serial.print(buffer);
}