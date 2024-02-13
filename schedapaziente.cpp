// schedapaziente.cpp

#include "schedapaziente.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>


SchedaPaziente::SchedaPaziente(const QString& nomePaziente, int numSensori, QWidget *parent)
    : QMainWindow(parent), nomePaziente(nomePaziente), numSensori(numSensori)
{
    setWindowTitle(nomePaziente);
    setMinimumSize(800, 600);

    // Creazione del layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // Aggiungi pulsante per mostrare i grafici dei sensori
    QPushButton* mostraGraficoButton = new QPushButton("Mostra Grafico Sensori");
    connect(mostraGraficoButton, &QPushButton::clicked, this, &SchedaPaziente::mostraGraficoSensori);

    mainLayout->addWidget(mostraGraficoButton);

    // Imposta il layout principale della finestra
    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void SchedaPaziente::aggiungiSensore(const QString& nomeSensore, double ultimoValore, const QString& unitaMisura)
{
    // Aggiungi qui la logica per visualizzare le informazioni del sensore
    // (potresti usare QLabel, QTableWidget, ecc.)
    qDebug() << "Sensore aggiunto: " << nomeSensore << ", Ultimo Valore: " << ultimoValore << " " << unitaMisura;
}

void SchedaPaziente::mostraGraficoSensori()
{
    // Aggiungi qui la logica per mostrare i grafici dei sensori
    // (potresti utilizzare QChartView con QLineSeries per ciascun sensore)
    QMessageBox::information(this, "Info", "Implementa la logica per mostrare i grafici dei sensori.");
}
