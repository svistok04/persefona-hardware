#ifndef SENSORS_H
#define SENSORS_H

// test init
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DHT_PIN 7
#define DHTTYPE DHT11
#define TEMPERATURE_PIN 6 // DS18B20
#define HUMIDITY_PIN A3 // FC-28
#define PH_PIN A2 // must be analog A0 // SEN0161
#define TURBIDIY_PIN A1 // SEN0189

DHT dht(DHT_PIN, DHTTYPE);
OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature temperatureSensor(&oneWire);

extern float sensorTemperature;
extern float sensorHumidity;
extern float sensorMoisture;
extern float sensorTurbidity;

void setup();

#endif //SENSORS_H
