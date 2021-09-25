#ifndef PIZZAOPTIONS_H
#define PIZZAOPTIONS_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QStringList>
#include <QRadioButton>
#include <QGroupBox>
#include <QPushButton>
#include <string>

enum PizzaSize { SMALL, MEDIUM, LARGE };

class PizzaConfig
{
public:
    QStringList* toppings;
    PizzaSize size;
    PizzaConfig(PizzaSize inital = PizzaSize::SMALL);
    ~PizzaConfig();
};

class PizzaOptions : public QWidget
{
    Q_OBJECT
    QLabel* size_label = nullptr;
    QComboBox* size_box = nullptr;
    QStringList* sizes;
    QStringList* toppings;
    QVBoxLayout* layout = nullptr;
    QHBoxLayout* header = nullptr;
    QPushButton* reset_button = nullptr;
    QFormLayout* size_form = nullptr;
    QGridLayout* topping_layout = nullptr;
    QGroupBox* topping_box = nullptr;
    QLabel* option_title = nullptr;
    const size_t NUM_ROWS = 3;
    const size_t NUM_COLS = 4;
    int toppings_selected = 0;
    QString style;
    PizzaConfig* config;
public:
    PizzaOptions(QWidget* parent = nullptr);
    ~PizzaOptions();
    QString getSize() const;
    const PizzaConfig* getConfig();
public slots:
    void validateToppings(bool checked);
    void setCheeseOpt(QString text);
    void resetOrder();
private:
    bool cheeseValid(QRadioButton* test) const;
    void setSizeRestrict(QObject* test);
};

#endif // PIZZAOPTIONS_H
