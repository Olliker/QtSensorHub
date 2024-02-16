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
    SensorHub();
    void addSensor(string paziente, string tipo);
    void addSensorConValore(string paziente, string tipo, double valore);
    void addPaziente(string paziente);
    void removeSensor(Sensor* sensor);
    void clearSensor();
    void calibraSensor(Sensor* sensor);
    void calibraAllSensors();
    void generaValoreSensor(Sensor* sensor);
    void simulazioneSensore(Sensor* sensor);

    bool hasPreoccupante(const vector<Sensor*>& sensors) const;
    int TipiSensoriPerPaziente(string paziente, const vector<Sensor*>& sensors) const;
    vector<string> getPazienti();
    vector<Sensor*> getSensorsByPaziente(string paziente);
    vector<Sensor*> getSensors() const;
    vector<Sensor*> getValoriPreoccupanti(const vector<Sensor*> sensors);
    ~SensorHub() = default;
};

#endif // SENSORHUB_H
