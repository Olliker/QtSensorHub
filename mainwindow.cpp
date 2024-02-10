#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    sensorHub = SensorHub::getInstance(); // Assicurati che il SensorHub sia un singleton

    // Inizializza i widget e i layout
    nomePazienteLineEdit = new QLineEdit(this);
    aggiungiPazienteButton = new QPushButton("Aggiungi Paziente", this);
    visualizzaGrafoButton = new QPushButton("Visualizza Grafo", this);
    grafoView = new QGraphicsView(this);
    grafoScene = new QGraphicsScene(this);

    // Connetti i pulsanti alle rispettive slot
    connect(aggiungiPazienteButton, &QPushButton::clicked, this, &MainWindow::aggiungiPaziente);
    connect(visualizzaGrafoButton, &QPushButton::clicked, this, &MainWindow::visualizzaGrafo);

    // Configura il layout della finestra principale
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(nomePazienteLineEdit);
    mainLayout->addWidget(aggiungiPazienteButton);
    mainLayout->addWidget(visualizzaGrafoButton);
    mainLayout->addWidget(grafoView);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::aggiungiPaziente() {
   sensorHub->addPaziente(nomePazienteLineEdit->text().toStdString());
}

void MainWindow::visualizzaGrafo() {
    // Implementa la logica per visualizzare il grafo dei sensori
}
