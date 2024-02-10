#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>

#include "Sensors/sensorHub.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void aggiungiPaziente();
    void visualizzaGrafo();

private:
    QLineEdit *nomePazienteLineEdit;
    QPushButton *aggiungiPazienteButton;
    QPushButton *visualizzaGrafoButton;
    QGraphicsView *grafoView;
    QGraphicsScene *grafoScene;

    SensorHub *sensorHub;
};

#endif // MAINWINDOW_H
