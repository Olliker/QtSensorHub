#ifndef GRAFO_H
#define GRAFO_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>


#include "sensors/sensor.h"

class Grafo : public QWidget {
    Q_OBJECT
public:
    Grafo(Sensor* sensore, QWidget* parent = nullptr);

private:
    Sensor* sensore;
    QChart *grafico;
    QChartView *vistaGrafico;
    static Grafo* istanzaAperta;

};

#endif // GRAFO_H
