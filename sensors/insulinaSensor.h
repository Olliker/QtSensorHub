 #ifndef INSULINASENSOR_H
#define INSULINASENSOR_H

#include "sensor.h"

class InsulinaSensor : public Sensor {
private:
    static double maxAccettabile;
    static double minAccettabile;
    static string unitaMisura;
public:
    InsulinaSensor(string paziente, double offset) : Sensor(paziente, offset) {};

    void calibra() override;
    void generaValore() override;

    double getMaxAccettabile() override;
    double getMinAccettabile() override;
    string getUnitaMisura() override;

    ~InsulinaSensor() = default;
};

#endif // INSULINASENSOR_H
