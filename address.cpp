#include "address.h"
#include <cctype>

Address::Address()
{
    street = "";
    city = "";
    postal_code = "";
    street_num = -1;
    apt_num = -1;
}

Address::operator bool() const
{
    return street_num > 0 && street.size() > 0 &&
            city.size() > 0 && validPostalCode(postal_code);
}

//Assuming Canadian Postal Code
bool Address::validPostalCode(QString pcode)
{
    cleanPostalCode(pcode);
    std::string pc = pcode.toStdString();

    if (pc.size() != 6)
        return false;

    for (auto i = 0u; i < pc.size(); i++) {
        if ((i+1)%2 != 0 && !isalpha(static_cast<unsigned char>(pc[i])))
            return false;
        else if ((i+1)%2 == 0 && !isdigit(static_cast<unsigned char>(pc[i])))
            return false;
    }

    return true;
}


void Address::cleanPostalCode(QString& pcode)
{
    std::string pc = pcode.toStdString();
    while (pc.find_first_of(' ') != std::string::npos) {
        pc.erase(pc.find_first_of(' '), 1);
    }

    pcode = QString::fromStdString(pc);
}


//Setters
void Address::setStreet(const QString& new_street)
{
    street = new_street;
}

void Address::setStreetNumber(size_t new_street_number)
{
    street_num = new_street_number;
}

void Address::setAptNumber(int new_apt_number)
{
    apt_num = new_apt_number;
}

void Address::setCity(const QString& new_city)
{
    city = new_city;
}

void Address::setPostalCode(const QString& new_postal_code)
{
    postal_code = new_postal_code;
}


//Getters
QString Address::getStreet() const
{
    return street;
}
int Address::getStreetNumber() const
{
    return street_num;
}

int Address::getAptNumber() const
{
    return apt_num;
}

QString Address::getCity() const
{
    return city;
}

QString Address::getPostalCode() const
{
    return postal_code;
}
