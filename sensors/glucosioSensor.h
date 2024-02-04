#ifndef GLICOSIOSENSOR_H
#define GLICOSIOSENSOR_H

#include "sensor.h"

class GlicosioSensor : public Sensor {
private:
    static double maxAccettabile;
    static double minAccettabile;
    static string unitaMisura;
public:
    GlicosioSensor(string paziente, double offset) : Sensor(paziente, offset) {};

    void calibra() override;
    void generaValore() override;

    double getMaxAccettabile() override;
    double getMinAccettabile() override;
    string getUnitaMisura() override;

    ~GlicosioSensor() = default;
};

#endif // GLICOSIOSENSOR_H