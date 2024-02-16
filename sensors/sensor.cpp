#include "sensor.h"

string Sensor::getPaziente() const {
    return paziente;
}

vector<double> Sensor::getValori() const {
    return valori;
}

void Sensor::simulaValori(int n) {
    for (int i = 0; i < n; i++) {
        calibra();
        generaValore();
    }
}

double Sensor::getOffset() const {
    return offset;
}

int Sensor::getNumeroValori() const {
    return valori.size();
}

double Sensor::getValore(int i) const {
    return valori[i];
}

double Sensor::getUltimoValore() const {
    return valori.back();
}

void Sensor::setPaziente(string paziente) {
    this->paziente = paziente;
}

void Sensor::setValore(int i, double valore) {
    valori[i] = valore;
}

void Sensor::setOffset(double offset) {
    this->offset = offset;
}

void Sensor::addValore(double valore) {
    valori.push_back(valore);
}
void Sensor::eliminaValore(int i) {
    valori.erase(valori.begin() + i);
}

bool Sensor::isPreoccupante() {
    if (valori.empty()) {
        return false;
    }
    return valori.back() < getMinAccettabile() || valori.back() > getMaxAccettabile();
}

void Sensor::resetValori() {
    valori.clear();
}


