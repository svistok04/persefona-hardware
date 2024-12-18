#include "sensors.h"

float sensorTemperature;
float sensorHumidity;
float sensorMoisture;
float sensorTurbidity;

void setup() {
    //    Serial.begin(9600);
    dht.begin();
    temperatureSensor.begin();
    temperatureSensor.getDeviceCount();
    //    Serial.println(temperatureSensor.getDeviceCount());
}

void readTemperature() {
    sensorTemperature = dht.readTemperature();
}