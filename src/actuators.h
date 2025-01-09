#ifndef ACTUATORS_H
#define ACTUATORS_H

#define PIN_PUMP 3
#define PIN_LEVEL_WATER 4
#define PIN_GATEWAY 5
#define PIN_LAMP 6
#define PIN_HEATING 7
#define PIN_VENTILATION 8

extern bool pumpRunning;
extern bool gatewayCountdownStarted;
extern unsigned long gatewayCountdownStartTime;

void modifyLampState(bool state);

void modifyHeating(bool state);

void modifyVentilation(bool state);

void openGateway();

void closeGateway();

void countdownGateway();

void checkWaterReachedLevel();

void modifyPumpState(bool pumpReceived);

#endif // ACTUATORS_H