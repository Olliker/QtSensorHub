#ifndef PRESSIONESENSOR_H
#define PRESSIONESENSOR_H

#include "sensor.h"

class PressioneSensor : public Sensor {
private:
    static double maxAccettabile;
    static double minAccettabile;
    static string unitaMisura ;
public:
    PressioneSensor(string paziente, double offset) : Sensor(paziente, offset) {};
    void calibra() override;
    void generaValore() override;

    double getMaxAccettabile() override;
    double getMinAccettabile() override;
    string getUnitaMisura() override;

    ~PressioneSensor() = default;
};

#endif // PRESSIONESENSOR_H
