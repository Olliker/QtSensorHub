#include "pressioneSensor.h"

double PressioneSensor::maxAccettabile = 145;
double PressioneSensor::minAccettabile = 88;
string PressioneSensor::unitaMisura = "mmHg";

void PressioneSensor::calibra() {
    setOffset((rand() % 5) - 2.0);
}

void PressioneSensor::generaValore() {
    double valore = rand() % 60 + 70 + getOffset();
    addValore(valore);
}


double PressioneSensor::getMaxAccettabile() {
    return maxAccettabile;
}

double PressioneSensor::getMinAccettabile() {
    return minAccettabile;
}

string PressioneSensor::getUnitaMisura() {
    return unitaMisura;
}

string PressioneSensor::getTipo() const {
    return "pressione";
}
