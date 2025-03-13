#ifndef TRANSMISION_H
#define TRANSMISION_H

#include <actuators.h>

extern bool pumpReceived;
extern bool lampReceived;
extern bool heatingReceived;
extern bool ventilationReceived;
extern float desiredTemperature;
extern int timeReceived;


void receive();
void send();

void parseMessage(const char* msg);

#endif //TRANSMISION_H
