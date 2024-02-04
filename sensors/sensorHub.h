#ifndef SENSORHUB_H
#define SENSORHUB_H

#include <vector>

#include "sensor.h"
#include "glucosioSensor.h"
#include "insulinaSensor.h"
#include "pressioneSensor.h"

using std::vector;

class SensorHub {
private:
    static SensorHub* instance;
    vector<Sensor*> sensors;
    SensorHub() = default;
public:
    static SensorHub* getInstance();
    void addSensor(Sensor* sensor);
    void removeSensor(Sensor* sensor);
    void calibraSensor(Sensor* sensor);
    void calibraAllSensors();
    void generaValoreSensor(Sensor* sensor);
    void simulazioneSensore();
    
    vector<Sensor*> getValoriPreoccupanti(const vector<Sensor*> sensors);
    ~SensorHub() = default;
};

#endif // SENSORHUB_H
