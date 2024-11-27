#ifndef MODIFIERS_H
#define MODIFIERS_H

#define PIN_PUMP 3
#define PIN_LEVEL_WATER 4
#define PIN_GATEWAY 4
#define PIN_LAMP 5
#define PIN_HEATING 6
#define PIN_VENTILATION 7

extern bool pumpRunning;
extern bool gatewayCountdownStarted;
extern unsigned long gatewayCountdownStartTime;

void modifyLampState(bool state);

void modifyHeating(bool state);

void modifyVentilation(bool state);

void modifyGateway();

void checkWaterReachedLevel();

void modifyPumpState();

#endif