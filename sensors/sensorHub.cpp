#include "sensorHub.h"
#include "sensors/insulinaSensor.h"
#include "sensors/pressioneSensor.h"
#include "sensors/glucosioSensor.h"
#include <algorithm>

SensorHub* SensorHub::instance = nullptr;

SensorHub* SensorHub::getInstance() {
    if (instance == nullptr) {
        instance = new SensorHub();
    }
    return instance;
}

void SensorHub::addSensor(string paziente, string tipo) {
//aggiungo il sensore di un paziente gia presente ma solo se non ne ha già uno
    for (auto sensor : sensors) {
    if (sensor->getPaziente() == paziente && sensor->getTipo() == tipo) {
            return;
        }
    }
    if (tipo == "glucosio") {
        sensors.push_back(new GlucosioSensor(paziente, 0));
    }
    else if (tipo == "pressione") {
        sensors.push_back(new PressioneSensor(paziente, 0));
    }
    else if (tipo == "insulina") {
        sensors.push_back(new InsulinaSensor(paziente, 0));
    }
}

void SensorHub::addPaziente(string paziente) {

    //controlo che il paziente non sia già presente
    for (auto sensor : sensors) {
        if (sensor->getPaziente() == paziente) {
            return;
        }
    }
    //aggiungo i sensori per il paziente
    sensors.push_back(new GlucosioSensor(paziente, 0));
    sensors.push_back(new PressioneSensor(paziente, 0));
    sensors.push_back(new InsulinaSensor(paziente, 0));
}

void SensorHub::removeSensor(Sensor* sensor) {
    for (std::vector<Sensor*>::size_type i = 0; i < sensors.size(); i++) {
        if (sensors[i] == sensor) {
            sensors.erase(sensors.begin() + i);
            break;
        }
    }
}

void SensorHub::calibraSensor(Sensor* sensor) {
    sensor->calibra();
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
    sensor->calibra();
    for (int i = 0; i < 10; i++) {
        sensor->generaValore();
    }
}

bool SensorHub::hasPreoccupante(const vector<Sensor*>& sensors) const {
    for (auto sensor : sensors) {
        if (sensor->isPreoccupante()) {
            return true;
        }
    }
    return false;
}

int SensorHub::TipiSensoriPerPaziente(string paziente, const vector<Sensor*>& sensors) const {
    int isGlucosio = 0;
    int isPressione = 0;
    int isInsulina = 0;
    for (auto sensor : sensors) {
        if (sensor->getPaziente() == paziente) {
            if (sensor->getTipo() == "glucosio") {
                isGlucosio = 1;
            }
            else if (sensor->getTipo() == "pressione") {
                isPressione = 1;
            }
            else if (sensor->getTipo() == "insulina") {
                isInsulina = 1;
            }
        }
    }
    return isGlucosio + isPressione + isInsulina;
}

vector<string> SensorHub::getPazienti() {
    vector<string> pazienti;
    for (auto sensor : sensors) {
        string paziente = sensor->getPaziente();
        if (std::find(pazienti.begin(), pazienti.end(), paziente) == pazienti.end()) {
            pazienti.push_back(paziente);
        }
    }
    return pazienti;
}

vector<Sensor*> SensorHub::getSensorsByPaziente(string paziente) {
    vector<Sensor*> sensorsByPaziente;
    for (auto sensor : sensors) {
        if (sensor->getPaziente() == paziente) {
            sensorsByPaziente.push_back(sensor);
        }
    }
    return sensorsByPaziente;
}


vector<Sensor*> SensorHub::getSensors() const {
    return sensors;
}

vector<Sensor*> SensorHub::getValoriPreoccupanti(const vector<Sensor*> sensors) {
    vector<Sensor*> valoriPreoccupanti;
    for (auto sensor : sensors) {
        if (sensor->isPreoccupante()) {
            valoriPreoccupanti.push_back(sensor);
        }
    }
    return valoriPreoccupanti;
}

