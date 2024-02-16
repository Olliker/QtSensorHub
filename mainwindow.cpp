
#include "mainwindow.h"
#include "pazienteitemwidget.h"
#include "newsensorpopup.h"
#include "qmessagebox.h"
#include "qscrollarea.h"
#include "sensors/glucosioSensor.h"
#include "sensors/insulinaSensor.h"
#include "sensors/pressioneSensor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sensorHub = SensorHub::getInstance();

    // Creazione dei bottoni
    QPushButton *aggiungiPazienteButton = new QPushButton("Aggiungi paziente");
    QPushButton *salvaSalvataggioButton = new QPushButton("Salva");
    QPushButton *caricaSalvataggioButton = new QPushButton("Carica");
    QPushButton *aggiornaListaButton = new QPushButton("Aggiorna");
    QLineEdit *cercaPazienteLineEdit = new QLineEdit();
    QCheckBox *preoccupantiCheckBox = new QCheckBox("Visualizza Preoccupanti");
    cercaPazienteLineEdit->setPlaceholderText("Cerca Paziente...");
    cercaPazienteLineEdit->setClearButtonEnabled(true);

    // Layout per i bottoni
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(aggiungiPazienteButton);
    buttonLayout->addStretch(); // Aggiunge uno spazio elastico per spostare i pulsanti a destra
    buttonLayout->addWidget(salvaSalvataggioButton);
    buttonLayout->addWidget(caricaSalvataggioButton);
    buttonLayout->addWidget(aggiornaListaButton);
    buttonLayout->addWidget(preoccupantiCheckBox);
    buttonLayout->addWidget(cercaPazienteLineEdit);

    // Widget principale per i bottoni
    QWidget *buttonWidget = new QWidget();
    buttonWidget->setLayout(buttonLayout);

    // Creazione dell'area di scorrimento per la lista pazienti
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    // Widget contenente la lista pazienti
    QWidget *listWidgetContainer = new QWidget();
    QVBoxLayout *listLayout = new QVBoxLayout(listWidgetContainer); // Cambiato da QHBoxLayout a QVBoxLayout

    // Creazione della lista pazienti
    listaPazientiWidget = new QListWidget();
    listLayout->addWidget(listaPazientiWidget);

    // Aggiunta del widget contenente la lista all'area di scorrimento
    scrollArea->setWidget(listWidgetContainer);

    // Layout principale della finestra
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(buttonWidget);
    mainLayout->addWidget(scrollArea); // Aggiunto l'area di scorrimento al layout principale

    // Creazione del widget principale e impostazione del layout
    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(cercaPazienteLineEdit, &QLineEdit::textChanged, this, &MainWindow::cercaPaziente);
    connect(aggiungiPazienteButton, SIGNAL(clicked()), this, SLOT(mostraPopupNuovoSensore()));
    connect(aggiornaListaButton, SIGNAL(clicked()), this, SLOT(aggiornaLista()));
    connect(preoccupantiCheckBox, &QCheckBox::stateChanged, this, &MainWindow::visualizzaSensoriPreoccupanti);
    connect(salvaSalvataggioButton, SIGNAL(clicked()), this, SLOT(salvaSalvataggio()));
    connect(caricaSalvataggioButton, SIGNAL(clicked()), this, SLOT(caricaSalvataggio()));


    aggiornaLista();
}

void MainWindow::aggiornaLista()
{
    listaPazientiWidget->clear();

    for (auto sensor : sensorHub->getSensors())
    {
        //controllo per non aggiungere pazienti duplicati
        bool pazientePresente = false;
        for (int i = 0; i < listaPazientiWidget->count(); i++)
        {
            PazienteItemWidget *pazienteItem = qobject_cast<PazienteItemWidget *>(listaPazientiWidget->itemWidget(listaPazientiWidget->item(i)));
            if (pazienteItem->getSensor()->getPaziente() == sensor->getPaziente())
            {
                pazientePresente = true;
                break;
            }
        }
        if (!pazientePresente)
        {
            aggiungiPazienteAllaLista(sensor, sensorHub);
        }
    }
}

void MainWindow::aggiungiPazienteAllaLista(Sensor *sensor, SensorHub *sensorHub)
{

    PazienteItemWidget *item = new PazienteItemWidget(sensor, sensorHub);
    QListWidgetItem *listItem = new QListWidgetItem();
    listItem->setSizeHint(QSize(0, 200));
    listaPazientiWidget->addItem(listItem);
    listaPazientiWidget->setItemWidget(listItem, item);
}


void MainWindow::visualizzaSensoriPreoccupanti()
{


    for (int i = 0; i < listaPazientiWidget->count(); i++)
    {
        PazienteItemWidget *pazienteItem = qobject_cast<PazienteItemWidget *>(listaPazientiWidget->itemWidget(listaPazientiWidget->item(i)));

        if (pazienteItem && ( pazienteItem->getSensor()->isPreoccupante()))
        {
            listaPazientiWidget->item(i)->setHidden(false);
        }
        else
        {
            listaPazientiWidget->item(i)->setHidden(true);
        }
    }
}

void MainWindow::cercaPaziente(const QString &searchText)
{
    for (int i = 0; i < listaPazientiWidget->count(); i++)
    {
        PazienteItemWidget *pazienteItem = qobject_cast<PazienteItemWidget *>(listaPazientiWidget->itemWidget(listaPazientiWidget->item(i)));

        if (pazienteItem)
        {
            QString pazienteQString = QString::fromStdString(pazienteItem->getSensor()->getPaziente());
            if (!pazienteQString.contains(searchText, Qt::CaseInsensitive))
            {
                listaPazientiWidget->item(i)->setHidden(true);
            }
            else
            {
                listaPazientiWidget->item(i)->setHidden(false);
            }
        }
    }
}


void MainWindow::aggiungiPaziente()
{
    NewSensorPopup *popup = new NewSensorPopup(sensorHub, this);
    connect(popup, &NewSensorPopup::accepted, this, &MainWindow::aggiornaLista);
    popup->exec();
}

void MainWindow::mostraPopupNuovoSensore()
{
    aggiungiPaziente();
}

void MainWindow::salvaSalvataggio()
{
    // Crea un oggetto JSON per rappresentare lo stato dell'applicazione
    QJsonArray sensoriArray;
    for (int i = 0; i < sensorHub->getSensors().size(); i++)
    {
        auto sensor = sensorHub->getSensors().at(i);

        QJsonObject sensoreObject;
        sensoreObject["paziente"] = QString::fromStdString(sensor->getPaziente());
        sensoreObject["Tipo"] = QString::fromStdString(sensor->getTipo());

        // Crea un array JSON per i valori del sensore
        QJsonArray valoriArray;
        for (int j = 0; j < (int)sensor->getValori().size(); j++)
        {
            valoriArray.append(sensor->getValori().at(j));
        }

        // Aggiunge l'array di valori all'oggetto JSON del sensore
        sensoreObject["valori"] = valoriArray;

        sensoriArray.append(sensoreObject);
    }
    QJsonObject statoObject;
    statoObject["sensori"] = sensoriArray;
    QJsonDocument document(statoObject);

    // Apre una finestra di dialogo per selezionare il percorso del file
    QString filePath = QFileDialog::getSaveFileName(this, "Salva Salvataggio", "", "JSON Files (*.json)");
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(document.toJson());
    file.close();
}

void MainWindow::caricaSalvataggio()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Carica Salvataggio", "", "JSON Files (*.json)");
    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(fileData);
    QJsonObject statoObject = document.object();
    QJsonArray sensoriArray = statoObject["sensori"].toArray();

    // Rimuove tutti i sensori esistenti
    sensorHub->clearSensor();
    for (int i = 0; i < sensoriArray.size(); i++)
    {
        QJsonObject sensoreObject = sensoriArray[i].toObject();
        QString paziente = sensoreObject["paziente"].toString();
        QString tipo = sensoreObject["Tipo"].toString();

        sensorHub->addSensor(paziente.toStdString(), tipo.toStdString());

        // Recupera l'array di valori dal sensoreObject
        QJsonArray valoriArray = sensoreObject["valori"].toArray();
        for (int j = 0; j < valoriArray.size(); j++)
        {
            // Aggiunge ogni valore all'array di valori del sensore
            sensorHub->getSensors().back()->addValore(valoriArray.at(j).toDouble());
        }
    }

    aggiornaLista();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Salvataggio", "Vuoi salvare prima di chiudere?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        // Chiamare la funzione di salvataggio qui
        salvaSalvataggio();
        event->accept();
    } else if (reply == QMessageBox::No) {
        event->accept();
    } else {
        event->ignore();
    }
}
