#ifndef SENSORS_H
#define SENSORS_H

#define DHT_PIN 7
#define DHTTYPE DHT11
#define TEMPERATURE_PIN 6 // DS18B20
#define SOIL_MOISTURE_PIN A3 // FC-28
#define PH_PIN A2 // SEN0161
#define TURBIDIY_PIN A1 // SEN0189
// light sensor missing #define LIGHT_PIN
// gateway detection sensor missing #define PIN_GATEWAY_SENSOR

extern float sensorTemperatureDHT;
extern float sensorTemperatureDS18B20;
extern float sensorHumidity;
extern float sensorSoilMoisture;
extern float sensorPH;
extern float sensorTurbidity;
extern float sensorLight;


void setupSensors();
void readDHTTemperature();
void readDHTHumidity();
void readDS18B20Temperature();
void readSoilMoisture();
void readPH();
void readTurbidity();
void readLight();
void readGateway();

#endif //SENSORS_H
