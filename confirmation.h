#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "pizzaoptions.h"
#include "address.h"

class Confirmation : public QWidget
{
    Q_OBJECT
    QLabel* summary;
    QHBoxLayout* button_layout;
    QVBoxLayout* layout;
    QPushButton* confirm_button;
    QPushButton* cancel_button;
    PizzaSize size;
public:
    Confirmation(QWidget* parent = nullptr);
    ~Confirmation();
    void setSummary(QString name, const Address* addr, const PizzaConfig* options);
public slots:
    void cancel();
signals:
    void switchWindow();
};

#endif // CONFIRMATION_H
