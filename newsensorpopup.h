
#ifndef NEWSENSORPOPUP_H
#define NEWSENSORPOPUP_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include "sensors/sensorHub.h"
#include "mainwindow.h"

class NewSensorPopup : public QDialog {
    Q_OBJECT

public:
    NewSensorPopup(SensorHub* sensorHub, QWidget *parent = nullptr);
    void setMainWindow(MainWindow* mainWindow);


private slots:
    void onAddSensorClicked();


private:
    SensorHub* sensorHub;
    QLineEdit* nomePazienteLineEdit;
    QCheckBox* glucosioCheckBox;
    QCheckBox* insulinaCheckBox;
    QCheckBox* pressioneCheckBox;
    QPushButton* addSensorButton;

    MainWindow* mainWindow;

};

#endif // NEWSENSORPOPUP_H
