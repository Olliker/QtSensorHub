#include "insulinaSensor.h"

double InsulinaSensor::maxAccettabile = 24;
double InsulinaSensor::minAccettabile = 4;
string InsulinaSensor::unitaMisura = "µU/mL";

void InsulinaSensor::calibra() {
    setOffset((rand() % 3) - 2.0);
}

void InsulinaSensor::generaValore() {
    double valore = rand() % 20 + 5 + getOffset();
    addValore(valore);
}

double InsulinaSensor::getMaxAccettabile() {
    return maxAccettabile;
}

double InsulinaSensor::getMinAccettabile() {
    return minAccettabile;
}

string InsulinaSensor::getUnitaMisura() {
    return unitaMisura;
}

string InsulinaSensor::getTipo() const {
    return "insulina";
}
