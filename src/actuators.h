#ifndef ACTUATORS_H
#define ACTUATORS_H

#define PIN_PUMP 3
#define PIN_LEVEL_WATER 4
#define PIN_GATEWAY 5
#define PIN_LAMP 6
#define PIN_HEATING 7
#define PIN_VENTILATION 8

extern bool pumpRunning;
extern bool lampState;
extern bool gatewayState;
extern bool heatingState;
extern bool ventilationState;
extern bool gatewayCountdownStarted;

// v1
extern unsigned long pumpStartTime;
extern unsigned long pumpDuration;
extern unsigned long pumpRunTime;


// v2
extern unsigned long gatewayCountdownStartTime;
extern unsigned long gatewayClosedTime;

extern bool pumpModeVersion1; // to be able to switch?

void modifyLampState(bool state); // sw-controlled

void modifyHeating(bool state); // sw-controlled

void modifyVentilation(bool state); // sw-controlled

void openGateway();

void closeGateway();

void countdownGateway();

void checkWaterReachedLevel();

void modifyPumpState(bool pumpReceived);

void checkStates();

// version 2
void modifyPumpState(bool pumpReceived, unsigned long pumpDuration);

void updatePumpProcess();

#endif // ACTUATORS_H