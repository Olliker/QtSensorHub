#include "sensorHub.h"

SensorHub::SensorHub() {
    srand(time(nullptr));
}

SensorHub* SensorHub::getInstance() {
    if (instance == nullptr) {
        instance = new SensorHub();
    }
    return instance;
}

void SensorHub::addSensor(Sensor* sensor) {
    sensors.push_back(sensor);
}

void SensorHub::removeSensor(Sensor* sensor) {
    for (int i = 0; i < sensors.size(); i++) {
        if (sensors[i] == sensor) {
            sensors.erase(sensors.begin() + i);
            break;
        }
    }
}

void SensorHub::calibraAllSensors() {
    for (auto sensor : sensors) {
        sensor->calibra();
    }
}

void SensorHub::generaValoreSensor(Sensor* sensor) {
    sensor->generaValore();
}

void SensorHub::simulazioneSensore(Sensor* sensor) {
    for (int i = 0; i < 10; i++) {
        sensor->generaValore();
    }
}

vector<Sensor*> SensorHub::getValoriPreoccupanti(const vector<Sensor*> sensors) {
    vector<Sensor*> valoriPreoccupanti;
    for (auto sensor : sensors) {
        if (sensor->getUltimoValore() > sensor->getMaxAccettabile() || sensor->getUltimoValore() < sensor->getMinAccettabile()) {
            valoriPreoccupanti.push_back(sensor);
        }
    }
    return valoriPreoccupanti;
}

