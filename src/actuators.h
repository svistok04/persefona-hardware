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

extern bool pumpModeVersion1;
// v1
extern bool gatewayCountdownStarted;
extern bool gatewayIsClosing;
extern unsigned long gatewayCountdownStartTime;
extern unsigned long gatewayClosedTime;
void openGateway();
void closeGateway();
bool checkGatewayClosed();
void countdownGateway();
void stopGatewayClosing();
void stopGatewayOpening();
void checkWaterReachedLevel();

// v2
extern unsigned long pumpStartTime;
extern unsigned long pumpDuration;
extern unsigned long pumpRunTime;
void modifyPumpStateV2(bool pumpReceived, unsigned long pumpDuration);
void updatePumpProcessV2();


void modifyLampState(bool state); // sw-controlled

void modifyHeating(bool state); // sw-controlled

void modifyVentilation(bool state); // sw-controlled


void modifyPumpState(bool pumpReceived);

void checkStates();



#endif // ACTUATORS_H