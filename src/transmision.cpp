#include "transmision.h"
#include <Arduino.h>
#include "main.cpp"

char buffer[50];
int bufferIndex = 0;
bool receiving = false;

bool pumpReceived;
bool lampReceived;
bool heatingReceived;
bool ventilationReceived;
int timeReceived;


void receive() {
    while (Serial.available() > 0) {
        char incomingChar = Serial.read();

        if (incomingChar == '*') {
            receiving = true;
            bufferIndex = 0;
            memset(buffer, 0, sizeof(buffer));
            //Serial.print("* received");
        }

        if (receiving) {
            if (incomingChar == '\\') {
                //Serial.print("\\ received");
                String dane = "";
                for (int i = 0; i < bufferIndex; i++) {
                    dane += buffer[i];
                }
                // Serial.print(dane);
                receiving = false;
                buffer[bufferIndex++] = '\0';
                parseMessage(buffer);
            } else if (bufferIndex < sizeof(buffer) - 1) {
                buffer[bufferIndex++] = incomingChar;
            }
        }
    }
}

void parseMessage(const char* msg) { // add parsing data read
    int pos = 1;  // Position tracker in the message
    while (msg[pos] != '\\') {
        Serial.print("c");
        if (strncmp(msg + pos, "pu", 2) == 0) {
            pos += 2; // move position by 2 (pu)
            pumpReceived = msg[pos++] == '1';
            if (pumpReceived) modifyPumpState();
            Serial.print("Pump received ");
        } else if (strncmp(msg + pos, "la", 2) == 0) {
            pos += 2; // move position by 2 (la)
            lampReceived = msg[pos++] == '1';
            modifyLampState(lampReceived);
            Serial.print("Lamp received ");
        } else if (strncmp(msg + pos, "he", 2) == 0) {
            pos += 2; // move position by 2 (he)
            heatingReceived = msg[pos++] == '1';
            modifyHeating(heatingReceived);
            Serial.print("Heating received ");
        } else if (strncmp(msg + pos, "ve", 2) == 0) {
            pos += 2; // move position by 2 (ve)
            ventilationReceived = msg[pos++] == '1';
            modifyVentilation(ventilationReceived);
            Serial.print("Ventilation received ");
        } else if (strncmp(msg + pos, "ti", 2) == 0) {
            pos += 2;
            timeReceived = 0;
            while (isdigit(msg[pos])) {
                timeReceived = timeReceived * 10 + (msg[pos++] - '0');
            }
        } else {
            break;
        }
    }
    Serial.print(" end parsing");
}