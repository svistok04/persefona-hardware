// Created by zongc on 13.11.2024.

#ifndef TRANSMISION_H
#define TRANSMISION_H

#include <modifiers.h>

extern bool pumpReceived;
extern bool lampReceived;
extern bool heatingReceived;
extern bool ventilationReceived;
extern int timeReceived;


void receive();

void parseMessage(const char* msg);

#endif //TRANSMISION_H
