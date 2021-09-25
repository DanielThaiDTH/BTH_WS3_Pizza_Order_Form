#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>
#include <string>

/*Stores address. All string getters will return an empty string if the field
 * has no value. Get apt number and street number will return -1 if no apartment number.
 * Object is valid only if every field (excluding apt number) is filled apropriately
 * */
class Address
{
    QString street;
    QString city;
    QString postal_code;
    int street_num, apt_num;
public:
    Address();
    //Setters
    void setStreet(const QString& new_street);
    void setStreetNumber(size_t new_street_number);
    void setAptNumber(size_t new_apt_number);
    void setCity(const QString& new_city);
    void setPostalCode(const QString& new_postal_code);
    //Getters
    QString getStreet() const;
    int getStreetNumber() const;
    int getAptNumber() const;
    QString getCity() const;
    QString getPostalCode() const;

    static bool validStreetOrAptNumber(int number);
    static bool validPostalCode(QString pcode);
    static void cleanPostalCode(QString& pcode);
    operator bool() const;
};

#endif // ADDRESS_H
