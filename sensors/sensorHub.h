#ifndef SENSORHUB_H
#define SENSORHUB_H

#include <vector>

#include "sensor.h"

using std::vector;

class SensorHub {
private:
    static SensorHub* instance;
    vector<Sensor*> sensors;
public:
    static SensorHub* getInstance();
    SensorHub() = default;
    void addSensor(Sensor* sensor);
    void addPaziente(string paziente);
    void removeSensor(Sensor* sensor);
    void calibraSensor(Sensor* sensor);
    void calibraAllSensors();
    void generaValoreSensor(Sensor* sensor);
    void simulazioneSensore(Sensor* sensor);

    vector<Sensor*> getSensors() const;
    
    vector<Sensor*> getValoriPreoccupanti(const vector<Sensor*> sensors);
    ~SensorHub() = default;
};

#endif // SENSORHUB_H
