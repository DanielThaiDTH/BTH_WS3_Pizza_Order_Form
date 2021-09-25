#include "confirmation.h"

Confirmation::Confirmation(QWidget* parent) : QWidget(parent)
{
    button_layout = new QHBoxLayout;
    layout = new QVBoxLayout;
    summary = new QLabel;
    confirm_button = new QPushButton("Confirm Order");
    cancel_button = new QPushButton("Cancel");

    button_layout->addWidget(confirm_button);
    button_layout->addWidget(cancel_button);

    layout->addWidget(summary);
    layout->addLayout(button_layout);
    setLayout(layout);
}

Confirmation::~Confirmation()
{

}


void Confirmation::setSummary(QString name, const Address* addr, const PizzaConfig* options)
{
    QString text = name;
    text += ", your order is a ";

    if (options->size == PizzaSize::SMALL)
        text += "small";
    else if (options->size == PizzaSize::MEDIUM)
        text += "medium";
    else if (options->size == PizzaSize::LARGE)
        text += "large";

    text += " pizza with the toppings:\n";

    for (int i = 0; i < options->toppings->size(); i++) {
        text += options->toppings->at(i);
        if (i+2 == options->toppings->size())
            text += " and ";
        else if (i+1 != options->toppings->size())
            text += ", ";
        else
            text += "\n";
    }

    text += "Your pizza will be delivered to ";
    text += QString::number(addr->getStreetNumber());
    text += " " + addr->getStreet() + " ";

    if (addr->getAptNumber() != -1)
        text += "Apartment #" + QString::number(addr->getAptNumber());

    text += ", " + addr->getCity() + " " + addr->getPostalCode();
    summary->setText(text);
}
