
#include "schedapaziente.h"
#include "grafo.h"
#include <QDebug>
#include <QHeaderView>
#include <QInputDialog>


SchedaPaziente* SchedaPaziente::istanzaAperta = nullptr;

SchedaPaziente::SchedaPaziente(QString pazienteName, SensorHub* sensorHub, QWidget* parent)
    : QWidget(parent), pazieneName(pazienteName), sensorHub(sensorHub)
{
    if (istanzaAperta) {
        istanzaAperta->close();
        istanzaAperta = nullptr;
    }

    setMinimumSize(800, 600);

    QVBoxLayout* layout = new QVBoxLayout(this);

    // Titolo
    QLabel* titoloLabel = new QLabel("Scheda Paziente", this);
    titoloLabel->setStyleSheet("font-size: 18px; font-weight: bold;");
    layout->addWidget(titoloLabel, 0, Qt::AlignCenter);

    // Nome paziente
    QLabel* nomePazienteLabel = new QLabel("Paziente: " + pazienteName, this);
    nomePazienteLabel->setStyleSheet("font-size: 14px;");
    layout->addWidget(nomePazienteLabel, 0, Qt::AlignLeft);

    // Pulsanti
    QHBoxLayout* pulsantiLayout = new QHBoxLayout();

    QPushButton* mostraGraficoButton = new QPushButton("Mostra grafico sensori", this);
    QPushButton* aggiungiValoreButton = new QPushButton("Aggiungi Valore", this);
    QPushButton* simulaSensoreButton = new QPushButton("Simula Sensore", this);
    QPushButton* eliminaSensoreButton = new QPushButton("Elimina Sensore", this);
    QPushButton* eliminaPazienteButton = new QPushButton("Elimina Paziente", this);
    QPushButton* resettaSensoreButton = new QPushButton("Resetta Sensore", this);

    //metti i pulsanti in un layout orizzontale
    pulsantiLayout->addWidget(aggiungiValoreButton);
    pulsantiLayout->addWidget(mostraGraficoButton);
    pulsantiLayout->addWidget(simulaSensoreButton);
    pulsantiLayout->addWidget(eliminaSensoreButton);
    pulsantiLayout->addWidget(eliminaPazienteButton);
    pulsantiLayout->addWidget(resettaSensoreButton);

    layout->addLayout(pulsantiLayout);

    sensoriComboBox = new QComboBox(this);
    layout->addWidget(sensoriComboBox);

    connect(sensoriComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
        sensorSelezionato(index);
        updateTable();
    });
    connect(aggiungiValoreButton, &QPushButton::clicked, this, &SchedaPaziente::aggiungiValore);
    connect(resettaSensoreButton, &QPushButton::clicked, this, &SchedaPaziente::resetSensore);
    connect(simulaSensoreButton, &QPushButton::clicked, this, &SchedaPaziente::simulaSensore);
    connect(eliminaSensoreButton, &QPushButton::clicked, this, &SchedaPaziente::eliminaSensore);
    connect(eliminaPazienteButton, &QPushButton::clicked, this, &SchedaPaziente::eliminaPaziente);

    connect(mostraGraficoButton, &QPushButton::clicked, this, [this]() {
        if (SensoreVisualizzato) {
            Grafo* grafico = new Grafo(SensoreVisualizzato);
            grafico->show();
            if (istanzaAperta) {
                istanzaAperta->close();
                istanzaAperta = nullptr;
            }
        }
    });

    tabella = new QTableWidget(this);
    tabella->setColumnCount(3);
    tabella->setHorizontalHeaderLabels(QStringList() <<  "Valore" << "Unità di Misura" << "Stato");
    tabella->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tabella->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(tabella);

    connect(tabella, &QTableWidget::itemClicked, this, &SchedaPaziente::cellaTabellaCliccata);


    setLayout(layout);
    istanzaAperta = this;

    // Popola il QComboBox con i tipi di sensori
    for (const auto& sensore : sensoriPaziente) {
        sensoriComboBox->addItem(QString::fromStdString(sensore->getTipo()));

    }

}

void SchedaPaziente::sensorSelezionato(int index)
{
    if (index >= 0 && index < static_cast<int>(sensoriPaziente.size())) {
        SensoreVisualizzato = sensoriPaziente[index];
        qDebug() << "SchedaPaziente::sensorSelezionato() - Sensore selezionato: " << SensoreVisualizzato->getTipo().c_str();
        for (int i = 0; i < SensoreVisualizzato->getNumeroValori(); i++) {
            qDebug() << "Valore " << i << ": " << SensoreVisualizzato->getValore(i);
        }
    }
}

void SchedaPaziente::setSensoriPaziente(const std::vector<Sensor*>& sensori)
{
    sensoriPaziente = sensori;

    sensoriComboBox->clear();
    for (const auto& sensore : sensoriPaziente) {
        sensoriComboBox->addItem(QString::fromStdString(sensore->getTipo()));
    }
}

void SchedaPaziente::updateTable()
{
    tabella->clearContents();

    if (SensoreVisualizzato) {
        tabella->setRowCount(SensoreVisualizzato->getNumeroValori());

        for (int i = 0; i < SensoreVisualizzato->getNumeroValori(); i++) {
            QTableWidgetItem* valoreItem = new QTableWidgetItem(QString::number(SensoreVisualizzato->getValore(i)));
            QTableWidgetItem* unitaMisuraItem = new QTableWidgetItem(QString::fromStdString(SensoreVisualizzato->getUnitaMisura()));
            QTableWidgetItem* statoItem = new QTableWidgetItem(
                (SensoreVisualizzato->getValore(i) < SensoreVisualizzato->getMinAccettabile() ||
                 SensoreVisualizzato->getValore(i) > SensoreVisualizzato->getMaxAccettabile())
                    ? QString("PREOCCUPANTE")
                    : QString("NORMALE")
                );

            if (statoItem->text() == "PREOCCUPANTE") {
                statoItem->setForeground(QBrush(QColor(Qt::red)));
            } else {
                statoItem->setForeground(QBrush(QColor(Qt::darkGreen)));
            }
            tabella->setItem(i, 0, valoreItem);  // Set "Valore" in column index 0
            tabella->setItem(i, 1, unitaMisuraItem);  // Set "Unità di Misura" in column index 1
            tabella->setItem(i, 2, statoItem);  // Set "Stato" in column index 2

        }
    }
}

void SchedaPaziente::aggiungiValore()
{
    if (SensoreVisualizzato) {
        bool ok;
        double valore = QInputDialog::getDouble(this, tr("Modifica Valore"), tr("Inserisci il nuovo valore:"), 0, -1000, 1000, 2, &ok);
        if (ok) {
            SensoreVisualizzato->addValore(valore);
            updateTable();
        }
    }
}

void SchedaPaziente::simulaSensore()
{
    bool ok;
    int numeroValori = QInputDialog::getInt(this, tr("Simula Sensore"), tr("Inserisci il numero di valori da simulare:"), 1, 1, 100, 1, &ok);
    if (ok) {
        if (SensoreVisualizzato) {
            SensoreVisualizzato->simulaValori(numeroValori);
            updateTable();
        }
    }
}

void SchedaPaziente::eliminaSensore()
{
    if (SensoreVisualizzato) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Elimina Sensore", "Sei sicuro di voler eliminare il sensore selezionato?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            sensorHub->removeSensor(SensoreVisualizzato);
            sensoriPaziente.erase(std::remove(sensoriPaziente.begin(), sensoriPaziente.end(), SensoreVisualizzato), sensoriPaziente.end());
            sensoriComboBox->removeItem(sensoriComboBox->currentIndex());
            updateTable();
        }
    }
}

void SchedaPaziente::eliminaPaziente()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Elimina Paziente", "Sei sicuro di voler eliminare il paziente?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //elimno da sensorhub tutti i sensorti del paziente
        for (const auto& sensore : sensoriPaziente) {
            sensorHub->removeSensor(sensore);
        }

        close();
        if (istanzaAperta) {
            istanzaAperta = nullptr;
        }
    }
}

void SchedaPaziente::cellaTabellaCliccata(QTableWidgetItem* item)
{
    if (item) {
        int riga = item->row();
        modificaValore(riga);
    }
}

void SchedaPaziente::modificaValore(int riga)
{
    if (SensoreVisualizzato) {
        // Creo una lista di opzioni da mostrare nella finestra di dialogo
        QStringList opzioni;
        opzioni << "Modifica Valore" << "Elimina Valore";

        // Mostro la finestra di dialogo con le opzioni
        bool ok;
        QString scelta = QInputDialog::getItem(this, tr("Modifica o Elimina Valore"), tr("Scegli un'opzione:"), opzioni, 0, false, &ok);

        if (ok && !scelta.isEmpty()) {
            if (scelta == "Modifica Valore") {
                // Modifica il valore del sensore
                double nuovoValore = QInputDialog::getDouble(this, tr("Modifica Valore"), tr("Inserisci il nuovo valore:"), SensoreVisualizzato->getValore(riga), SensoreVisualizzato->getMinAccettabile()-50, SensoreVisualizzato->getMaxAccettabile()+50, 2, &ok);
                if (ok) {
                    SensoreVisualizzato->setValore(riga, nuovoValore);
                    updateTable();
                }
                else {
                    QMessageBox::warning(this, "Errore", "Il valore inserito non è valido. Riprova.");
                }
            }
            else if (scelta == "Elimina Valore") {
                // Rimuovi il valore dal sensore
                SensoreVisualizzato->eliminaValore(riga);
                updateTable();
            }
        }
    }
}

void SchedaPaziente::resetSensore()
{
    if (SensoreVisualizzato) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Resetta Sensore", "Sei sicuro di voler resettare il sensore selezionato?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            SensoreVisualizzato->resetValori();
            updateTable();
        }
    }
}
