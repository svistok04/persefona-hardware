// Created by zongc on 13.11.2024.

#ifndef TRANSMISION_H
#define TRANSMISION_H

extern char buffer[50];

extern const int puLength;
extern const int laLength;
extern const int heLength;
extern const int veLength;

void receive();

void parseMessage(const char* msg);

#endif //TRANSMISION_H
