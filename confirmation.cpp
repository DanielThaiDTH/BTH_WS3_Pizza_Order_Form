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
