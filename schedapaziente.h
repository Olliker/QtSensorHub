// schedapaziente.h
#ifndef SCHEDAPAZIENTE_H
#define SCHEDAPAZIENTE_H

#include "sensors/sensor.h"
#include <QMainWindow>


class SchedaPaziente : public QMainWindow
{
    Q_OBJECT

public:
    SchedaPaziente(Sensor* sensor, QWidget *parent = nullptr);

    void aggiungiSensore();

private:
    QString nomePaziente;
    int numSensori;

private slots:
    void mostraGraficoSensore();
};

#endif // SCHEDAPAZIENTE_H
