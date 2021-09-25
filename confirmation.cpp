#include "confirmation.h"
#include <QApplication>
#include <QFont>

Confirmation::Confirmation(QWidget* parent) : QWidget(parent)
{
    button_layout = new QHBoxLayout;
    layout = new QVBoxLayout;
    summary = new QLabel;
    confirm_button = new QPushButton("Confirm Order");
    confirm_button->setObjectName("confirm");
    cancel_button = new QPushButton("Cancel");
    cancel_button->setObjectName("cancel");

    QFont font = summary->font();
    font.setPointSize(14);
    summary->setFont(font);

    QFont button_font = confirm_button->font();
    button_font.setBold(true);
    confirm_button->setFont(button_font);
    cancel_button->setFont(button_font);

    QString style = "QPushButton#cancel { color: #AA0000 }\n";
    style += "QPushButton#confirm { color: #00AA00 }";
    this->setStyleSheet(style);

    button_layout->addWidget(confirm_button);
    button_layout->addWidget(cancel_button);

    layout->addWidget(summary);
    layout->addLayout(button_layout);
    setLayout(layout);

    connect(confirm_button, &QPushButton::clicked, qApp, &QApplication::exit);
    connect(cancel_button, &QPushButton::clicked, this, &QWidget::hide);
    connect(cancel_button, &QPushButton::clicked, this, &Confirmation::cancel);
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

    if (options->toppings->size() > 0)
        text += " pizza with the toppings:\n";
    else
        text += " pizza with no toppings.\n";

    for (int i = 0; i < options->toppings->size(); i++) {
        text += options->toppings->at(i);
        if (i+2 == options->toppings->size())
            text += " and ";
        else if (i+1 != options->toppings->size())
            text += ", ";
        else
            text += "\n\n";
    }

    text += "Your pizza will be delivered to ";
    text += QString::number(addr->getStreetNumber());
    text += " " + addr->getStreet() + " ";

    if (addr->getAptNumber() != -1)
        text += "Apartment #" + QString::number(addr->getAptNumber());

    text += ", " + addr->getCity() + " " + addr->getPostalCode();
    summary->setText(text);
}


void Confirmation::cancel()
{
    emit switchWindow();
}
