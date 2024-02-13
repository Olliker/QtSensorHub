// schedapaziente.h
#ifndef SCHEDAPAZIENTE_H
#define SCHEDAPAZIENTE_H

#include <QMainWindow>


class SchedaPaziente : public QMainWindow
{
    Q_OBJECT

public:
    SchedaPaziente(const QString& nomePaziente, int numSensori, QWidget *parent = nullptr);

    void aggiungiSensore(const QString& nomeSensore, double ultimoValore, const QString& unitaMisura);

private:
    QString nomePaziente;
    int numSensori;

private slots:
    void mostraGraficoSensori();
};

#endif // SCHEDAPAZIENTE_H
