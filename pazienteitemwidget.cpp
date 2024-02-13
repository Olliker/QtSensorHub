
#include "pazienteitemwidget.h"
#include <QVBoxLayout>
#include <QMouseEvent>

PazienteItemWidget::PazienteItemWidget(Sensor* sensor, SensorHub* sensorHub, QWidget* parent)
    : QWidget(parent), sensor(sensor) {
    // Label unica che contiene tutte le informazioni
    infoLabel = new QLabel(this);

    QString labelText = "<div style='margin: 10px;'><b>%1</b><br/><br/>Stato: <font color='%2'><b>%3</b></font><br/><br/>Sensori: %4</div>";
    labelText = labelText.arg(sensor->getPaziente().c_str(),
                              sensor->isPreoccupante() ? "red" : "green",
                              sensor->isPreoccupante() ? "PREOCCUPANTE" : "NORMALE",
                              QString::number(sensorHub->TipiSensoriPerPaziente(sensor->getPaziente(), sensorHub->getSensors())).toStdString().c_str());

    infoLabel->setText(labelText);

    // Layout verticale senza spazi aggiuntivi
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(infoLabel);
    layout->setSpacing(0);  // Imposta la distanza tra le etichette a 0

    // Imposta l'allineamento del testo al centro
    infoLabel->setAlignment(Qt::AlignCenter);

    // Imposta lo stile del widget con sfondo bianco e bordo nero rotondo
    setStyleSheet("background-color: white; border: 2px solid black; border-radius: 10px;");

    // Connessione del segnale al click dell'oggetto
    connect(this, &PazienteItemWidget::clicked, this, &PazienteItemWidget::mostraDettagliSensore);
}

void PazienteItemWidget::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    emit clicked();
}

void PazienteItemWidget::mostraDettagliSensore() {
    // Aggiungi qui la logica per mostrare i dettagli del sensore usando la SCHEDA PAZIENTE
    qDebug() << "Mostra dettagli sensore: " << sensor->getPaziente().c_str();
}

QString PazienteItemWidget::getNomePaziente() const {
    return QString::fromStdString(sensor->getPaziente());
}

Sensor* PazienteItemWidget::getSensor() const {
    return sensor;
}
