#include "mainwindow.h"
#include "pizzaorder.h"
#include "confirmation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PizzaOrder po;
    //Confirmation c;

    po.show();
    //c.show();
    return a.exec();
}
