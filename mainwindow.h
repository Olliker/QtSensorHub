#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QListWidget>

#include "Sensors/sensorHub.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void aggiungiPaziente();
    void visualizzaGrafo();
    void aggiornaLista();
    void visualizzaSensoriPaziente(QListWidgetItem *item);


private:
    QLineEdit *nomePazienteLineEdit;
    QPushButton *aggiungiPazienteButton;
    QPushButton *visualizzaGrafoButton;
    QGraphicsView *grafoView;
    QGraphicsScene *grafoScene;
    QListWidget *listaPazientiWidget;
    QVBoxLayout *mainLayout;


    SensorHub *sensorHub;
};

#endif // MAINWINDOW_H
