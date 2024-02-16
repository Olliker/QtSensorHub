#ifndef SCHEDAPAZIENTE_H
#define SCHEDAPAZIENTE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QComboBox>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QTextEdit>
#include <QTableWidget>


#include "sensors/sensor.h"
#include "sensors/sensorHub.h"

class SchedaPaziente : public QWidget {
    Q_OBJECT
public:
    SchedaPaziente(QString pazienteName, SensorHub* sensorHub, QWidget* parent = nullptr);
    void setSensoriPaziente(const std::vector<Sensor*>& sensori);
    void updateTable();
    void aggiungiValore();
    void simulaSensore();
    void eliminaSensore();
    void eliminaPaziente();
    void modificaValore(int row);
    void resetSensore();


private slots:
    void sensorSelezionato(int index);
    void cellaTabellaCliccata(QTableWidgetItem* item);



private:
    QString pazieneName;
    SensorHub* sensorHub;
    QComboBox* sensoriComboBox;
    std::vector<Sensor*> sensoriPaziente;
    static SchedaPaziente* istanzaAperta;
    QLabel* nomePazienteLabel;
    Sensor* SensoreVisualizzato;
    bool ricorsioneAttiva = false;
    QTableWidget* tabella;

};

#endif // SCHEDAPAZIENTE_H
