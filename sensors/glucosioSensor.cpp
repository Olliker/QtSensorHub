#include "glucosioSensor.h"

double GlicosioSensor::maxAccettabile = 99;
double GlicosioSensor::minAccettabile = 70;
string GlicosioSensor::unitaMisura = "mg/dL";

void GlicosioSensor::calibra() {
    setOffset((rand() % 11) - 5.0);
}

void GlicosioSensor::generaValore() {
    double valore = rand() % 30 + 70 + getOffset();
    addValore(valore);
}

double GlicosioSensor::getMaxAccettabile() {
    return maxAccettabile;
}

double GlicosioSensor::getMinAccettabile() {
    return minAccettabile;
}

string GlicosioSensor::getUnitaMisura() {
    return unitaMisura;
}



