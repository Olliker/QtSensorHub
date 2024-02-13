#include "glucosioSensor.h"

double GlucosioSensor::maxAccettabile = 99;
double GlucosioSensor::minAccettabile = 70;
string GlucosioSensor::unitaMisura = "mg/dL";

void GlucosioSensor::calibra() {
    setOffset((rand() % 11) - 5.0);
}

void GlucosioSensor::generaValore() {
    double valore = rand() % 30 + 70 + getOffset();
    addValore(valore);
}

double GlucosioSensor::getMaxAccettabile() {
    return maxAccettabile;
}

double GlucosioSensor::getMinAccettabile() {
    return minAccettabile;
}

string GlucosioSensor::getUnitaMisura() {
    return unitaMisura;
}

string GlucosioSensor::getTipo() const {
    return "glucosio";
}


