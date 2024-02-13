#include "newsensorpopup.h"
#include "sensors/sensorHub.h"
#include <QVBoxLayout>
#include <QFormLayout>

NewSensorPopup::NewSensorPopup(SensorHub* sensorHub, QWidget *parent)
    : QDialog(parent),
    sensorHub(sensorHub),
    nomePazienteLineEdit(new QLineEdit(this)),
    glucosioCheckBox(new QCheckBox("Glucosio", this)),
    insulinaCheckBox(new QCheckBox("Insulina", this)),
    pressioneCheckBox(new QCheckBox("Pressione", this)),
    addSensorButton(new QPushButton("Aggiungi", this)),
    mainWindow(nullptr)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("Nome Paziente:", nomePazienteLineEdit);
    formLayout->addRow("Tipo di Sensore:", glucosioCheckBox);
    formLayout->addRow("", insulinaCheckBox);
    formLayout->addRow("", pressioneCheckBox);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(addSensorButton);

    addSensorButton->setStyleSheet("background-color: #4CAF50; color: white;");
    addSensorButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(addSensorButton, SIGNAL(clicked()), this, SLOT(onAddSensorClicked()));
}

void NewSensorPopup::setMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
}

void NewSensorPopup::onAddSensorClicked() {
    QString nomePaziente = nomePazienteLineEdit->text();

    if (nomePaziente.isEmpty()) {
        return;
    }

    if (glucosioCheckBox->isChecked()) {
        sensorHub->addSensor(nomePaziente.toStdString(), "glucosio");
    }
    if (insulinaCheckBox->isChecked()) {
        sensorHub->addSensor(nomePaziente.toStdString(), "insulina");
    }
    if (pressioneCheckBox->isChecked()) {
        sensorHub->addSensor(nomePaziente.toStdString(), "pressione");
    }

    accept();  // Chiudi il pop-up
    if (mainWindow) {
        mainWindow->aggiornaLista();
    }

}
