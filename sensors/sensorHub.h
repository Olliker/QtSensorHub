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
    SensorHub() {
        addPaziente("paziente1");
        addPaziente("paziente2");
        addPaziente("paziente3");
        addPaziente("oLO tRINCA");
        addPaziente("paziente5");
        addPaziente("Oliver");
        addPaziente("paziente7");
        addPaziente("paziente8");
        addPaziente("paziente9");
        addPaziente("paziente10");\
        addPaziente("paziente11");
        addPaziente("paziente12");
        addPaziente("paziente13");
        addPaziente("paziente14");
        addPaziente("paziente15");
        addPaziente("paziente16");
        addPaziente("paziente17");
        addPaziente("paziente18");
        addPaziente("paziente19");
        addPaziente("paziente20");
        addPaziente("paziente21");
        addPaziente("paziente22");
        addPaziente("paziente23");
        addPaziente("paziente24");
        addPaziente("paziente25");
        addPaziente("paziente26");
        //aggiungi un paziente preoccupante
        addSensor("paziente1", "pressione");//NON DEVE AGGIUNGERLO
        addSensor("paziente6", "glucosio");
        addSensor("paziente6", "glucosio");//NON DEVE AGGIUNGERLO


    }
    void addSensor(string paziente, string tipo);
    void addPaziente(string paziente);
    void removeSensor(Sensor* sensor);
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
