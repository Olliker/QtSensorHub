#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <vector>

using std::string, std::vector;

class Sensor {
private:   
    string paziente;
    double offset;
    vector<double> valori;
    
public:
    Sensor(string paziente, double offset) : paziente(paziente), offset(offset) {};
    
    virtual void calibra() = 0;
    virtual void generaValore() = 0;

    string getPaziente() const ;
    vector<double> getValori() const ;
    double getOffset() const ;
    int getNumeroValori() const ;
    double getValore(int i) const ;
    double getUltimoValore() const ;

    void setPaziente(string paziente);
    void setValore(int i, double valore);
    void setOffset(double offset);
    void addValore(double valore);

    void resetValori();

    bool isPreoccupante();

    virtual double getMinAccettabile() = 0;
    virtual double getMaxAccettabile() = 0;
    virtual string getUnitaMisura() = 0;
    virtual string getTipo() const = 0;
    ~Sensor() = default;

};

#endif // SENSOR_H
