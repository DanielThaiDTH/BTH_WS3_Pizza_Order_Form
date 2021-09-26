#include "pizzaorder.h"
#include <QFont>
#include <QLine>
#include <QSizePolicy>
#include <QApplication>

PizzaOrder::PizzaOrder(Confirmation* c, QWidget* parent) : QWidget(parent)
{
    button_style = "* { color: white; background: green; font-weight: bold; width: 150}\n";
    button_style += "*:pressed { background: #A0BB50 }\n";
    button_style += "*:disabled { background: #A0C0A0 }";
    cancel_style = "* { color: white; background: #990000; font-weight: bold; width: 100 }\n";
    cancel_style += "*:hover { background: #DD2000 }";
    error_style = "* { background: pink }";

    layout = new QVBoxLayout(this);
    layout->setGeometry(QRect(70, 70, 580, 300));
    top_layout = new QHBoxLayout;

    posIntValid = new QIntValidator(this);
    posIntValid->setBottom(0);
    numberValid = dynamic_cast<const QValidator*>(posIntValid);

    //Aggregate confirm screen
    confirm_screen = c;

    title = new QLabel("Pizza Order");
    title->setGeometry(0, 0, 200, 60);
    title->setMargin(10);
    QFont title_font = title->font();
    title_font.setPointSize(25);
    title_font.setWeight(QFont::Bold);
    title->setFont(title_font);
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); //Standard behaviour is fixed

    cancel = new QPushButton("Cancel");
    cancel->setStyleSheet(cancel_style);

    top_layout->addWidget(title);
    top_layout->addWidget(cancel);

    //Name field
    name_form = new QFormLayout();
    name_field = new QLineEdit;
    name_form->addRow("Name: ", name_field);
    QFont font = name_form->itemAt(0, QFormLayout::LabelRole)->widget()->font();
    font.setWeight(QFont::Bold);
    name_form->itemAt(0, QFormLayout::LabelRole)->widget()->setFont(font);

    addr_layout_top = new QHBoxLayout;
    addr_layout_bot = new QHBoxLayout;
    addr_layout = new QGridLayout;
    addr_header = new QLabel("Delivery Address");
    addr_header->setFont(font);
    addr_header->setContentsMargins(0, 5, 0, 0);

    addr = new Address;

    //Address input
    street_field = new QLineEdit;
    street_form = new QFormLayout;
    street_field->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    street_form->addRow("Street: ", street_field);


    street_num_field = new QLineEdit;
    street_num_field->setMaxLength(9);
    street_num_field->setValidator(numberValid);
    street_num_field->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    street_num_form = new QFormLayout;
    street_num_form->addRow("Street#: ", street_num_field);
    //street_num_form->setSizeConstraint(QLayout::SetFixedSize);

    apt_num_field = new QLineEdit;
    apt_num_field->setMaxLength(9);
    apt_num_field->setValidator(numberValid);
    apt_num_field->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    apt_num_form = new QFormLayout;
    apt_num_form->addRow("Apt#: ", apt_num_field);

    city_field = new QLineEdit;
    city_field->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    city_form = new QFormLayout;
    city_form->addRow("City:    ", city_field);

    postal_field = new QLineEdit;
    postal_field->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    pcValid = new PostalCodeValidator;
    postal_field->setValidator(pcValid);
    postal_field->setPlaceholderText("e.g. A1C2G3");
    postal_form = new QFormLayout;
    postal_form->addRow("Postal Code: ", postal_field);

    addr_layout->addLayout(street_form, 0, 0);
    addr_layout->addLayout(street_num_form, 0, 2);
    addr_layout->addLayout(apt_num_form, 0, 3);
    addr_layout->addLayout(city_form, 2, 0);
    addr_layout->addLayout(postal_form, 2, 2);
    addr_layout->addWidget(new QLabel("Apartment number is optional"), 2, 3);
    addr_layout->setColumnMinimumWidth(0, 300);
    addr_layout->setColumnMinimumWidth(1, 20);
    addr_layout->setRowMinimumHeight(1, 5);

    //Options
    options = new PizzaOptions();

    //End
    end = new QHBoxLayout;
    finish_button = new QPushButton("Finish Order");
    finish_button->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed));
    err_msg = new QLabel;
    err_msg->setStyleSheet("* { color: #990000; font-weight: bold }");
    end->setAlignment(Qt::AlignRight);
    end->setSizeConstraint(QLayout::SetNoConstraint);
    end->addWidget(err_msg);
    end->addWidget(finish_button);

    //Insert into root layout
    layout->addLayout(top_layout);
    layout->addLayout(name_form);
    layout->addWidget(addr_header);
    layout->addLayout(addr_layout);
    layout->addWidget(options);
    layout->addLayout(end);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    finish_button->setStyleSheet(button_style);
    finish_button->setDisabled(true);
    setLayout(layout);

    connect(cancel, &QPushButton::clicked, qApp, &QApplication::exit);
    connect(finish_button, &QPushButton::clicked, this, &PizzaOrder::finishOrder);
    connect(name_field, &QLineEdit::textChanged, this, &PizzaOrder::verifyDeliveryFields);
    connect(street_field, &QLineEdit::textChanged, this, &PizzaOrder::verifyDeliveryFields);
    connect(street_num_field, &QLineEdit::textChanged, this, &PizzaOrder::verifyDeliveryFields);
    connect(apt_num_field, &QLineEdit::textChanged, this, &PizzaOrder::verifyDeliveryFields);
    connect(city_field, &QLineEdit::textChanged, this, &PizzaOrder::verifyDeliveryFields);
    connect(postal_field, &QLineEdit::textChanged, this, &PizzaOrder::verifyDeliveryFields);
    connect(postal_field, &QLineEdit::textChanged, this, &PizzaOrder::checkPostalField);
    connect(confirm_screen, &Confirmation::switchWindow, this, &QWidget::show);
}


PizzaOrder::~PizzaOrder()
{
    delete addr;
}


void PizzaOrder::finishOrder()
{
    order_config = options->getConfig();
    name = name_field->text();
    addr->setStreet(street_field->text());
    addr->setStreetNumber(street_num_field->text().toInt());

    if (apt_num_field->hasAcceptableInput())
        addr->setAptNumber(apt_num_field->text().toInt());
    else
        addr->setAptNumber(-1);

    addr->setCity(city_field->text());
    addr->setPostalCode(postal_field->text());
    openConfirmation();
}


void PizzaOrder::openConfirmation()
{

    confirm_screen->setSummary(name, addr, order_config);
    this->hide();
    confirm_screen->show();
}


void PizzaOrder::verifyDeliveryFields()
{
    bool all_good = true;

    if (name_field->text().size() == 0)
        all_good = false;

    if (city_field->text().size() == 0)
        all_good = false;

    if (street_field->text().size() == 0)
        all_good = false;

    if (!street_num_field->hasAcceptableInput())
        all_good = false;

    if (!postal_field->hasAcceptableInput())
        all_good = false;

    if (all_good) {
        err_msg->setText("");
        finish_button->setEnabled(true);
    } else {
        err_msg->setText("Missing or incorrect information.");
        finish_button->setDisabled(true);
    }
}


void PizzaOrder::checkPostalField()
{
    if (postal_field->hasAcceptableInput())
        postal_field->setStyleSheet("");
    else
        postal_field->setStyleSheet(error_style);
}

//PostalCodeValidator
PostalCodeValidator::PostalCodeValidator(QWidget* parent) : QValidator(parent)
{
}


QValidator::State PostalCodeValidator::validate(QString& input, int& pos) const
{
    if (Address::validPostalCode(input))
        return QValidator::Acceptable;

    QString copy = input;
    Address::cleanPostalCode(copy);

    if (copy.size() <= 6)
        return QValidator::Intermediate;

    return QValidator::Invalid;
}

PostalCodeValidator::~PostalCodeValidator()
{
}
