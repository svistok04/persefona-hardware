#include "sensors.h"
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

DHT dht(DHT_PIN, DHTTYPE);
OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature temperatureSensor(&oneWire);

float sensorTemperatureDHT;
float sensorTemperatureDS18B20;
float sensorHumidity;
float sensorSoilMoisture;
float sensorPH;
float sensorTurbidity;

void setup() {
    dht.begin();
    temperatureSensor.begin();
    // temperatureSensor.getDeviceCount();
    //    Serial.println(temperatureSensor.getDeviceCount());
}

void readDHTTemperature() {
    sensorTemperatureDHT = dht.readTemperature();
    if (isnan(sensorTemperatureDHT)) {
        sensorTemperatureDHT = -100.0;
    }
}

void readDHTHumidity() {
    sensorHumidity = dht.readHumidity();
    if (isnan(sensorHumidity)) {
        sensorHumidity = -100.0;
    }
}

void readDS18B20Temperature() {
    temperatureSensor.requestTemperatures();
    sensorTemperatureDS18B20 = temperatureSensor.getTempCByIndex(0);
    if (sensorTemperatureDS18B20 == DEVICE_DISCONNECTED_C) {
        sensorTemperatureDS18B20 = -100.0;
    }
}

void readSoilMoisture() {
    const int moistureValue = analogRead(SOIL_MOISTURE_PIN);
    sensorSoilMoisture = map(moistureValue, 0, 1023, 0, 100);
}

void readPH() {
    const float phValue = analogRead(PH_PIN);
    const float phVoltage = phValue * 5.0 / 1024.0;
    sensorPH = 3.5 * phVoltage;
}

void readTurbidity() {
    const int turbidityValue = analogRead(TURBIDIY_PIN);
    const float turbidityVoltage = turbidityValue * 5.0 / 1024.0;
    if (turbidityVoltage > 2.5) { // formula from docs
        sensorTurbidity = -1120.4 * pow(turbidityVoltage, 2) + 5742.3 * turbidityVoltage - 4352.9;

        if (sensorTurbidity < 0) {
            sensorTurbidity = 0;
        } else if (sensorTurbidity > 999.999) {
            sensorTurbidity = 999.999;
        }
    } else {
        sensorTurbidity = 0; // Turbidity voltage too low according to the formula?
    }
}

void readLight() {

}