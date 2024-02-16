// pazienteitemwidget.h

#ifndef PAZIENTEITEMWIDGET_H
#define PAZIENTEITEMWIDGET_H

#include "sensors/sensor.h"
#include "sensors/sensorHub.h"
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class PazienteItemWidget : public QWidget
{
    Q_OBJECT

public:
    PazienteItemWidget(Sensor* sensor,SensorHub* SensorHub, QWidget* parent = nullptr);

    QString getNomePaziente() const;
    Sensor* getSensor() const;
    int getNumeroTipologieSensori() const;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel* infoLabel;
    Sensor* sensor;
    SensorHub* sensorHub;

};

#endif // PAZIENTEITEMWIDGET_H
