#include "transmision.h"
#include <Arduino.h>

char buffer[50];
int bufferIndex = 0;
bool receiving = false;

const int puLength = 5;
const int laLength = 5;
const int heLength = 5;
const int veLength = 5;

void receive() {
    while (Serial.available() > 0) {
        char incomingChar = Serial.read();

        if (incomingChar == '*') {
            receiving = true;
            bufferIndex = 0;
            memset(buffer, 0, sizeof(buffer));
        }

        if (receiving) {
            if (incomingChar == '\\') {
                receiving = false;
                parseMessage(buffer);
            } else if (bufferIndex < sizeof(buffer) - 1) {
                buffer[bufferIndex++] = incomingChar;
            }
        }
    }
}

void parseMessage(const char* msg) { // add parsing data read
    int pos = 0;  // Position tracker in the message

    while (msg[pos] != '\0') {
        if (strncmp(msg + pos, "pu", 2) == 0) {
            pos += 2; // move position by 2 (pu)
            char pumpData[puLength + 1];
            strncpy(pumpData, msg + pos, puLength); // copy
            pumpData[puLength] = '\0';
            pos += puLength; // move position by bits read (x)
            Serial.print("Pump data: ");
            Serial.println(pumpData);

        } else if (strncmp(msg + pos, "la", 2) == 0) {
            pos += 2; // move position by 2 (la)
            char lightingData[laLength + 1];
            strncpy(lightingData, msg + pos, laLength);
            lightingData[laLength] = '\0';
            pos += laLength; // move position by bits read (x)
            Serial.print("Lighting data: ");
            Serial.println(lightingData);

        } else if (strncmp(msg + pos, "he", 2) == 0) {
            pos += 2; // move position by 2 (he)
            char heatingData[heLength + 1];
            strncpy(heatingData, msg + pos, heLength);
            heatingData[heLength] = '\0';
            pos += heLength; // move position by bits read (x)
            Serial.print("Heating data: ");
            Serial.println(heatingData);

        } else if (strncmp(msg + pos, "ve", 2) == 0) {
            pos += 2; // move position by 2 (ve)
            char ventilationData[veLength + 1];
            strncpy(ventilationData, msg + pos, veLength);
            ventilationData[veLength] = '\0';
            pos += veLength; // move position by bits read (x)
            Serial.print("Ventilation data: ");
            Serial.println(ventilationData);

        } else {
            Serial.println("Unknown");
            break;
        }
    }
}