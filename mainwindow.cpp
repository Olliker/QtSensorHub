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
    listaPazientiWidget = new QListWidget(this);
    mainLayout = new QVBoxLayout;


    // Connetti i pulsanti alle rispettive slot
    connect(aggiungiPazienteButton, &QPushButton::clicked, this, &MainWindow::aggiungiPaziente);
    connect(visualizzaGrafoButton, &QPushButton::clicked, this, &MainWindow::visualizzaGrafo);
    connect(listaPazientiWidget, &QListWidget::itemClicked, this, &MainWindow::visualizzaSensoriPaziente);

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
   aggiornaLista();
}

void MainWindow::visualizzaGrafo() {
    // Implementa la logica per visualizzare il grafo dei sensori
}

void MainWindow::aggiornaLista() {
    listaPazientiWidget->clear();
    for (const auto& paziente : sensorHub->getSensors()) {
        QString nomePaziente = QString::fromStdString(paziente->getPaziente());
        QListWidgetItem *item = new QListWidgetItem(nomePaziente);
        listaPazientiWidget->addItem(item);
    }
}

void MainWindow::visualizzaSensoriPaziente(QListWidgetItem *item) {
    // Implementa la logica per visualizzare i sensori del paziente selezionato

    // Esempio:
    QString nomePaziente = item->text();
    for (const auto& paziente : sensorHub->getSensors()) {
        if (nomePaziente == QString::fromStdString(paziente->getPaziente())) {
            for (int i = 0; i < paziente->getNumeroValori(); i++) {
                double valore = paziente->getValore(i);
                qDebug() << valore;
            }
        }
    }

}
