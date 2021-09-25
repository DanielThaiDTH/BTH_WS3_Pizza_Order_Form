#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Confirmation : public QWidget
{
    Q_OBJECT
    QLabel* summary;
    QHBoxLayout* button_layout;
    QVBoxLayout* layout;
    QPushButton* confirm_button;
    QPushButton* cancel_button;
public:
    Confirmation(QWidget* parent = nullptr);
    ~Confirmation();
};

#endif // CONFIRMATION_H
