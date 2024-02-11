#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "pazienteitemwidget.h"
#include "sensors/sensorHub.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void aggiornaLista();
    void visualizzaSensoriPaziente(PazienteItemWidget *pazienteItem);
    void visualizzaSensoriPreoccupanti();

private:
    SensorHub *sensorHub;

    QListWidget *listaPazientiWidget;
    QPushButton *aggiungiPazienteButton;
    QPushButton *vediSensoriButton;
    QLineEdit *cercaPazienteLineEdit;
    QPushButton *preoccupantiButton;
};

#endif // MAINWINDOW_H
