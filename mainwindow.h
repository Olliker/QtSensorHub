#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "qcheckbox.h"
#include "sensors/sensorHub.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void aggiornaLista();
    void visualizzaSensoriPaziente(Sensor* sensor);
    void visualizzaSensoriPreoccupanti();
    void cercaPaziente(const QString& searchText);
    void aggiungiPaziente();
    void mostraPopupNuovoSensore();
    void aggiungiPazienteAllaLista(Sensor* sensor, SensorHub* sensorHub);
    void salvaSalvataggio();
    void caricaSalvataggio();


private:

    SensorHub* sensorHub;
    QListWidget* listaPazientiWidget;
    QPushButton* aggiungiPazienteButton;
    QLineEdit* cercaPazienteLineEdit;
    QCheckBox *preoccupantiCheckBox;
    QPushButton *salvaSalvataggioButton;
    QPushButton *caricaSalvataggioButton;

};

#endif // MAINWINDOW_H
