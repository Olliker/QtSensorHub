// schedapaziente.cpp

#include "schedapaziente.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>


SchedaPaziente::SchedaPaziente(Sensor* sensor, QWidget *parent)
    : QMainWindow(parent)
{
    // Imposta il titolo della finestra
    setWindowTitle("Scheda Paziente");

    // Imposta il nome del paziente
    nomePaziente = QString::fromStdString(sensor->getPaziente());

    // Imposta il numero di sensori
    numSensori = 1;

    // Crea un layout verticale
    QVBoxLayout *mainLayout = new QVBoxLayout();

    // Crea un pulsante per aggiungere un sensore
    QPushButton *aggiungiSensoreButton = new QPushButton("Aggiungi Sensore");
    connect(aggiungiSensoreButton, &QPushButton::clicked, this, &SchedaPaziente::aggiungiSensore);

    // Crea un pulsante per mostrare i grafici dei sensori
    QPushButton *mostraGraficoButton = new QPushButton("Mostra Grafico");
    connect(mostraGraficoButton, &QPushButton::clicked, this, &SchedaPaziente::mostraGraficoSensore);

    // Aggiungi i pulsanti al layout principale
    mainLayout->addWidget(aggiungiSensoreButton);
    mainLayout->addWidget(mostraGraficoButton);

    // Crea un widget principale e imposta il layout
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void SchedaPaziente::aggiungiSensore()
{
    // Aggiungi qui la logica per aggiungere un sensore al paziente
    QMessageBox::information(this, "Info", "Implementa la logica per aggiungere un sensore al paziente.");
}

void SchedaPaziente::mostraGraficoSensore()
{
    // Aggiungi qui la logica per mostrare i grafici dei sensori
    // (potresti utilizzare QChartView con QLineSeries per ciascun sensore)
    QMessageBox::information(this, "Info", "Implementa la logica per mostrare i grafici dei sensori.");
}
