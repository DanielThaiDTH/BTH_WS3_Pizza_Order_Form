#ifndef PIZZAORDER_H
#define PIZZAORDER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QValidator>
#include <QIntValidator>

#include "pizzaoptions.h"
#include "confirmation.h"

class PostalCodeValidator : public QValidator
{
    Q_OBJECT
public:
    PostalCodeValidator(QWidget* parent = nullptr);
    ~PostalCodeValidator();
    QValidator::State validate(QString& input, int& pos) const;
};

class PizzaOrder : public QWidget
{
    Q_OBJECT
    QString name;
    Address* addr = nullptr;
    QString button_style;
    QVBoxLayout* layout = nullptr;
    QHBoxLayout* addr_layout_top = nullptr;
    QHBoxLayout* addr_layout_bot = nullptr;
    QGridLayout* addr_layout = nullptr;
    QHBoxLayout* end = nullptr;
    QLabel* title = nullptr;
    QLabel* addr_header = nullptr;
    //Forms
    QLineEdit* name_field = nullptr;
    QFormLayout* name_form = nullptr;
    QLineEdit* street_field = nullptr;
    QFormLayout* street_form = nullptr;
    QLineEdit* street_num_field = nullptr;
    QFormLayout* street_num_form = nullptr;
    QLineEdit* apt_num_field = nullptr;
    QFormLayout* apt_num_form = nullptr;
    QLineEdit* city_field = nullptr;
    QFormLayout* city_form = nullptr;
    QLineEdit* postal_field = nullptr;
    QFormLayout* postal_form = nullptr;
    //Options
    PizzaOptions* options = nullptr;
    //End
    QPushButton* finish_button = nullptr;
    const PizzaConfig* order_config = nullptr;
    //Validators
    PostalCodeValidator* pcValid;
    QIntValidator* posIntValid;
    const QValidator* numberValid;
    Confirmation* confirm_screen;
public:
    PizzaOrder(Confirmation* c, QWidget* parent = nullptr);
    ~PizzaOrder();
public slots:
    void finishOrder();
    void verifyDeliveryFields();
private:
    void openConfirmation();
};

#endif // PIZZAORDER_H
