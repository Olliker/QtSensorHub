#include "pazienteitemwidget.h"
#include <QVBoxLayout>
#include <QMouseEvent>

PazienteItemWidget::PazienteItemWidget(const QString& nome, bool almenoUnoPreoccupante, int numSensori, QWidget* parent)
    : QWidget(parent) {
    // Label unica che contiene tutte le informazioni
    infoLabel = new QLabel(this);

    // Formatta il testo con maggiore spaziatura
    QString labelText = QString("<div style='margin: 10px;'><b>%1</b><br/><br/>Stato: <font color='%2'><b>%3</b></font><br/><br/>Sensori: %4</div>")
                            .arg(nome.toUpper())
                            .arg(almenoUnoPreoccupante ? "red" : "green")
                            .arg(almenoUnoPreoccupante ? "PREOCCUPANTE" : "NORMALE")
                            .arg(numSensori);

    infoLabel->setText(labelText);

    // Layout verticale senza spazi aggiuntivi
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(infoLabel);
    layout->setSpacing(0);  // Imposta la distanza tra le etichette a 0

    // Imposta l'allineamento del testo al centro
    infoLabel->setAlignment(Qt::AlignCenter);

    // Imposta lo stile del widget con sfondo bianco e bordo nero rotondo
    setStyleSheet("background-color: white; border: 2px solid black; border-radius: 10px;");

    // Imposta la dimensione massima del widget
    setFixedSize(200, 200);  // Sostituisci con le dimensioni desiderate
}

void PazienteItemWidget::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    emit clicked();
}

QString PazienteItemWidget::getNomePaziente() const {
    // Estrae il nome dal testo dell'etichetta
    QString labelText = infoLabel->text();
    int startIndex = labelText.indexOf("<b>") + 3;
    int endIndex = labelText.indexOf("</b>");
    return labelText.mid(startIndex, endIndex - startIndex);
}
