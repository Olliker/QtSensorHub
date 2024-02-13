
#include "mainwindow.h"
#include "pazienteitemwidget.h"
#include "newsensorpopup.h"
#include "qscrollarea.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sensorHub = SensorHub::getInstance();

    // Creazione dei bottoni
    QPushButton *aggiungiPazienteButton = new QPushButton("Aggiungi paziente");
    QPushButton *salvaSalvataggioButton = new QPushButton("Salva");
    QPushButton *caricaSalvataggioButton = new QPushButton("Carica");
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
    connect(listaPazientiWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
        PazienteItemWidget *pazienteItem = qobject_cast<PazienteItemWidget *>(listaPazientiWidget->itemWidget(item));
        visualizzaSensoriPaziente(pazienteItem->getSensor());
    });
    connect(preoccupantiCheckBox, &QCheckBox::stateChanged, this, [=](int state) {
        if (state == Qt::Checked)
        {
            visualizzaSensoriPreoccupanti();
        }
        else
        {
            aggiornaLista();
        }
    });

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

void MainWindow::visualizzaSensoriPaziente(Sensor* sensor)
{
    qDebug() << "Visualizza sensori paziente";
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


#include <QString>

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


void MainWindow::salvaSalvataggio() {
    // Implementa la logica per salvare il tuo stato o dati
    qDebug() << "Salvataggio effettuato";
}

void MainWindow::caricaSalvataggio() {
    // Implementa la logica per caricare il tuo stato o dati salvati
    qDebug() << "Salvataggio caricato";
}
