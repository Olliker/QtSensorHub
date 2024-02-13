#ifndef GLUCOSIOSENSOR_H
#define GLUCOSIOSENSOR_H

#include "sensor.h"

class GlucosioSensor : public Sensor {
private:
    static double maxAccettabile;
    static double minAccettabile;
    static string unitaMisura;
public:
    GlucosioSensor(string paziente, double offset) : Sensor(paziente, offset) {};

    void calibra() override;
    void generaValore() override;

    double getMaxAccettabile() override;
    double getMinAccettabile() override;
    string getUnitaMisura() override;
    string getTipo() const override;

    ~GlucosioSensor() = default;
};

#endif // GLUCOSIOSENSOR_H
