#include "mainwindow.h"
#include "pazienteitemwidget.h"
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sensorHub = SensorHub::getInstance();

    listaPazientiWidget = new QListWidget();
    aggiungiPazienteButton = new QPushButton("Aggiungi paziente");
    vediSensoriButton = new QPushButton("Vedi tutti i sensori");
    cercaPazienteLineEdit = new QLineEdit();
    preoccupantiButton = new QPushButton("Sensori preoccupanti");

    connect(preoccupantiButton, SIGNAL(clicked()), this, SLOT(visualizzaSensoriPreoccupanti()));

    QLabel *searchIconLabel = new QLabel(this);

    cercaPazienteLineEdit->setPlaceholderText("Cerca Paziente...");
    cercaPazienteLineEdit->setClearButtonEnabled(true);
    cercaPazienteLineEdit->setMaximumWidth(200);

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchIconLabel);
    searchLayout->addWidget(cercaPazienteLineEdit);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(aggiungiPazienteButton, 0, 0, Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(vediSensoriButton, 1, 0, Qt::AlignTop | Qt::AlignLeft);
    layout->addLayout(searchLayout, 0, 1, Qt::AlignTop | Qt::AlignRight);
    layout->addWidget(preoccupantiButton, 1, 1, Qt::AlignTop | Qt::AlignRight);
    layout->addWidget(listaPazientiWidget, 2, 0, 1, 2);

    // Imposta il margine inferiore a 10 pixel
    layout->setContentsMargins(10, 0, 10, 10);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    aggiornaLista();
    connect(listaPazientiWidget, &QListWidget::itemClicked, [=](QListWidgetItem *item) {
        PazienteItemWidget *pazienteItem = dynamic_cast<PazienteItemWidget*>(listaPazientiWidget->itemWidget(item));
        if (pazienteItem) {
            visualizzaSensoriPaziente(pazienteItem);
        }
    });
}

void MainWindow::aggiornaLista() {
    listaPazientiWidget->clear();

    const int numColonneDesiderate = 5;
    QGridLayout *layout = new QGridLayout();

    int rowIndex = 0;
    int colIndex = 0;

    for (auto paziente : sensorHub->getPazienti()) {
        auto sensors = sensorHub->getSensorsByPaziente(paziente);
        bool almenoUnoPreoccupante = sensorHub->hasPreoccupante(sensors);

        PazienteItemWidget *item = new PazienteItemWidget(QString::fromStdString(paziente), almenoUnoPreoccupante, sensors.size());
        layout->addWidget(item, rowIndex, colIndex);

        colIndex++;
        if (colIndex >= numColonneDesiderate) {
            colIndex = 0;
            rowIndex++;
        }
    }

    // Aggiungi uno stretch verticale all'ultimo elemento del layout
    layout->setRowStretch(rowIndex, 1);

    listaPazientiWidget->setLayout(layout);
}
void MainWindow::visualizzaSensoriPaziente(PazienteItemWidget *pazienteItem)
{
    if (pazienteItem) {
        QString nomePaziente = pazienteItem->getNomePaziente();
        qDebug() << "Visualizza sensori per paziente: " << nomePaziente;
    }
}

void MainWindow::visualizzaSensoriPreoccupanti()
{
    for (auto sensor : sensorHub->getValoriPreoccupanti(sensorHub->getSensors())) {
        sensor->generaValore();
    }
}
