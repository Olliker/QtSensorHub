// pazienteitemwidget.h

#ifndef PAZIENTEITEMWIDGET_H
#define PAZIENTEITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class PazienteItemWidget : public QWidget
{
    Q_OBJECT

public:
    PazienteItemWidget(const QString& nome, bool almenoUnoPreoccupante, int numSensori, QWidget* parent = nullptr);

    QString getNomePaziente() const;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel* infoLabel;
};

#endif // PAZIENTEITEMWIDGET_H
