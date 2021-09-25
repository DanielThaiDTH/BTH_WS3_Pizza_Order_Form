#include "pizzaoptions.h"

PizzaOptions::PizzaOptions(QWidget* parent) : QWidget(parent)
{
    style = "QGroupBox { font-weight: bold }\n";
    style += "QPushButton { background: #7070FF; color: white; font-weight: bold}";
    this->setStyleSheet(style);
    layout = new QVBoxLayout(this);

    QStringList s = {"Small", "Medium", "Large"};
    QStringList t = {"Ham", "Pepperoni", "Green Pepper", "Mushroom",
                     "Pineapple", "Onion", "Black Olives", "Artichokes",
                    "Extra Cheese"};
    sizes = new QStringList(s);
    toppings = new QStringList(t);

    header = new QHBoxLayout;
    option_title = new QLabel("Choose your Pizza");
    QFont title_font = option_title->font();
    title_font.setWeight(QFont::Bold);
    title_font.setPointSize(20);
    option_title->setFont(title_font);
    option_title->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed));
    reset_button = new QPushButton("Reset");
    reset_button->setGeometry(0, 0, 200, 30);
    reset_button->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed));
    header->addWidget(option_title);
    header->addWidget(reset_button);

    size_box = new QComboBox;
    size_box->addItems(*sizes);

    size_form = new QFormLayout;
    size_form->addRow("Size:", size_box);
    QFont font = size_form->itemAt(0, QFormLayout::LabelRole)->widget()->font();
    font.setWeight(QFont::Bold);
    size_form->itemAt(0, QFormLayout::LabelRole)->widget()->setFont(font);

    topping_layout = new QGridLayout;
    topping_layout->setSpacing(0);
    topping_box = new QGroupBox("Toppings");

    for (auto i = 0u; i < toppings->size(); i++) {
        QRadioButton* new_button = new QRadioButton(toppings->at(i));
        new_button->setAutoExclusive(false);
        topping_layout->addWidget(new_button, (int) i/NUM_COLS, i%NUM_COLS);
        connect(new_button, &QRadioButton::clicked, this, &PizzaOptions::validateToppings);
    }

    topping_layout->addWidget(new QLabel("*Extra cheese not available for large pizzas"), 2, 1);

    topping_box->setLayout(topping_layout);
    layout->addLayout(header);
    layout->addLayout(size_form);
    layout->addWidget(topping_box);
    setLayout(layout);

    connect(size_box, &QComboBox::currentTextChanged, this, &PizzaOptions::setCheeseOpt);
    connect(reset_button, &QPushButton::clicked, this, &PizzaOptions::resetOrder);
}


PizzaOptions::~PizzaOptions()
{
//    delete topping_layout;
//    delete topping_box;
//    delete sizes;
//    delete toppings;
}


bool PizzaOptions::cheeseValid(QRadioButton* test) const
{
    return !(size_box->currentText() == "Large" && test->text() == "Extra Cheese");
}


void PizzaOptions::setCheeseOpt(QString text)
{
    for (int i = 0; i < topping_layout->count(); i++) {
        QRadioButton* radio = dynamic_cast<QRadioButton*>(topping_layout->itemAt(i)->widget());
        if (radio && radio->text() == "Extra Cheese" && text == "Large") {
            radio->setDisabled(true);
        } else if (radio && radio->text() == "Extra Cheese" && text != "Large") {
            radio->setEnabled(true);
        }
    }
}


void PizzaOptions::resetOrder()
{
    size_box->setCurrentIndex(0);
    if (size_box->count() < 3)
        size_box->addItem("Large");
    for (int i = 0; i < topping_layout->count(); i++) {
        QRadioButton* radio = dynamic_cast<QRadioButton*>(topping_layout->itemAt(i)->widget());
        if (radio) {
            radio->setEnabled(true);
            radio->setChecked(false);
        }
    }
    toppings_selected = 0;
}


QString PizzaOptions::getSize() const
{
    return size_box->currentText();
}


void PizzaOptions::validateToppings(bool checked)
{
    if (checked && toppings_selected < 2) {
        toppings_selected++;
        setSizeRestrict(sender());
    } else if (checked && toppings_selected == 2) {
        toppings_selected++;
        setSizeRestrict(sender());
        for (int i = 0; i < topping_layout->count(); i++) {
            QRadioButton* radio = dynamic_cast<QRadioButton*>(topping_layout->itemAt(i)->widget());
            if (radio && !radio->isChecked()) {
                radio->setDisabled(true);
            }
        }
    } else if (!checked) {
        toppings_selected--;
        setSizeRestrict(sender());
        if (toppings_selected < 3) {
            for (int i = 0; i < topping_layout->count(); i++) {
                QRadioButton* radio = dynamic_cast<QRadioButton*>(topping_layout->itemAt(i)->widget());
                if (radio && !radio->isChecked() && cheeseValid(radio)) {
                    radio->setEnabled(true);
                }
            }
        }
    }
}


void PizzaOptions::setSizeRestrict(QObject *test)
{
    if (dynamic_cast<QRadioButton*>(test)) {
        QRadioButton* cheeseButton = dynamic_cast<QRadioButton*>(test);
        if (cheeseButton->isChecked() && cheeseButton->text() == "Extra Cheese" && size_box->count() == 3) {
            size_box->removeItem(2);
        } else if (!cheeseButton->isChecked() && cheeseButton->text() == "Extra Cheese" && size_box->count() < 3) {
            size_box->addItem("Large");
        }
    }
}


const PizzaConfig* PizzaOptions::getConfig()
{
    config->toppings->clear();
    for (int i = 0; i < topping_layout->count(); i++) {
        QRadioButton* radio = dynamic_cast<QRadioButton*>(topping_layout->itemAt(i)->widget());
        if (radio && radio->isChecked()) {
            config->toppings->append(radio->text());
        }
    }

    if (size_box->currentText() == "Small")
        config->size = PizzaSize::SMALL;
    else if (size_box->currentText() == "Medium")
        config->size = PizzaSize::MEDIUM;
    else if (size_box->currentText() == "Large")
        config->size = PizzaSize::LARGE;

    return config;
}


PizzaConfig::PizzaConfig(PizzaSize initial)
{
    toppings = new QStringList;
    size = initial;
}


PizzaConfig::~PizzaConfig()
{
    delete toppings;
}
