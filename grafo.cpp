#include "grafo.h"
#include <QPainter>
#include <QPalette>
#include <QLabel>
#include <QVBoxLayout>

Grafo* Grafo::istanzaAperta = nullptr;

Grafo::Grafo(Sensor* sensore, QWidget* parent) : QWidget(parent), sensore(sensore) {

    if (istanzaAperta) {
        istanzaAperta->close();
        istanzaAperta = nullptr;
    }

    if (sensore->getNumeroValori() <= 1) {
        QLabel* erroreLabel = new QLabel("Il sensore non ha ancora registrato abbstanza dati", this);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(erroreLabel);
        setLayout(layout);
        return;
    }

    setMinimumSize(800, 600);

    QLineSeries* serie = new QLineSeries();
    QLineSeries* serieMin = new QLineSeries();
    QLineSeries* serieMax = new QLineSeries();

    //dati del paziente di cui nome ultima misura tipo di sensore unita di misura un label per ogni dato
    QLabel* titoloLabel = new QLabel("Informazioni del Paziente", this);
    QLabel* nomePazienteLabel = new QLabel("Nome Paziente:   " + QString::fromStdString(sensore->getPaziente()), this);
    QLabel* tipoSensoreLabel = new QLabel("Tipo Sensore:   " + QString::fromStdString(sensore->getTipo()), this);
    QLabel* unitaMisuraLabel = new QLabel("Unità di Misura:   " + QString::fromStdString(sensore->getUnitaMisura()), this);
    QLabel* ultimaMisuraLabel = new QLabel("Ultima Misura:   " + QString::number(sensore->getUltimoValore()), this);
    QLabel* minAccettabileLabel = new QLabel("Minimo Accettabile:   " + QString::number(sensore->getMinAccettabile()), this);
    QLabel* maxAccettabileLabel = new QLabel("Massimo Accettabile:   " + QString::number(sensore->getMaxAccettabile()), this);
    QLabel *preoccupanteLabel = new QLabel("Stato:   " + QString::fromStdString(sensore->isPreoccupante()? "PREOCCUPANTE" : "NORMALE" ), this);

    if(sensore->isPreoccupante()){
        preoccupanteLabel->setStyleSheet("color: red");
    }else{
        preoccupanteLabel->setStyleSheet("color: green");
    }

    titoloLabel->setStyleSheet("font-size: 15px; font-weight: bold");


    //se preccupante metti in maiuscolo e rosso se normale metti in maiuscolo e verde

    // Layout a griglia per organizzare le etichette
    QGridLayout* infoLayout = new QGridLayout();
    infoLayout->addWidget(titoloLabel, 0, 0, 1, 2, Qt::AlignCenter);  // Titolo centrato su due colonne
    infoLayout->addWidget(nomePazienteLabel, 1, 0, 1, 1, Qt::AlignLeft);
    infoLayout->addWidget(tipoSensoreLabel, 1, 1, 1, 1, Qt::AlignRight);
    infoLayout->addWidget(unitaMisuraLabel, 2, 0, 1, 1, Qt::AlignLeft);
    infoLayout->addWidget(ultimaMisuraLabel, 2, 1, 1, 1, Qt::AlignRight);
    infoLayout->addWidget(minAccettabileLabel, 3, 0, 1, 1, Qt::AlignLeft);
    infoLayout->addWidget(maxAccettabileLabel, 3, 1, 1, 1, Qt::AlignRight);
    infoLayout->addWidget(preoccupanteLabel, 4, 0, 1, 2, Qt::AlignCenter);  // Stato centrato su due colonne



    grafico = new QChart();
    vistaGrafico = new QChartView(grafico);
    vistaGrafico->setRenderHint(QPainter::Antialiasing);

    //dimesione e posizione centrale fisse della finestra
    vistaGrafico->setGeometry(200, 200, 500, 500);

    // Impostare l'asse y con i valori di sensore.getValori()
    QValueAxis* asseY = new QValueAxis();
    asseY->setTickCount(10);  // Numero di tick sull'asse y
    asseY->setRange(sensore->getMinAccettabile()-15, sensore->getMaxAccettabile()+15);

    QValueAxis* asseX = new QValueAxis();
    asseX->setTickCount(5);
    asseX->setRange(0, sensore->getNumeroValori());


    grafico->addAxis(asseY, Qt::AlignLeft);
    grafico->addAxis(asseX, Qt::AlignBottom);

    // Impostare l'asse x con i valori di sensore.getValori()
    for (int i = 0; i < sensore->getNumeroValori(); i++) {
        serie->append(i, sensore->getValore(i));
        serieMin->append(i, sensore->getMinAccettabile());
        serieMax->append(i, sensore->getMaxAccettabile());
    }

    serie->setName(QString::fromStdString(sensore->getPaziente() + " - " + sensore->getTipo()));
    serieMin->setName("Minimo accettabile");
    serieMax->setName("Massimo accettabile");

    grafico->addSeries(serie);
    grafico->addSeries(serieMin);
    grafico->addSeries(serieMax);

    serieMin->attachAxis(asseY);
    serieMin->attachAxis(asseX);
    serieMax->attachAxis(asseY);
    serieMax->attachAxis(asseX);
    serie->attachAxis(asseY);
    serie->attachAxis(asseX);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(vistaGrafico);
    layout->addLayout(infoLayout);

    setLayout(layout);
    istanzaAperta = this;

}
