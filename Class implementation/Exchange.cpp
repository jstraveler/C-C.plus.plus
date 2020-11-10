
#include <iostream>
#include "Exchange.hpp"
#include "MString.hpp"
#include <cstring>


Exchange &Exchange::operator=(Exchange const &that) {
    cout << "copy object" << endl;

    delete[] name;
    name = new char[strlen(that.name) + 1];
    strcpy(name, that.name);

    number = that.number;

    delete[] address;
    address = new char[strlen(that.address) + 1];
    strcpy(address, that.address);

    if (!that.currencies.empty()) {
        auto size = that.currencies.size();
        for (int i = 0; i < size; ++i) {
            currencies.push_back(that.currencies[i]);
        }
    }
    return *this;
}

std::ostream &operator<<(std::ostream &ostream1, const Exchange &exchange) {
    int size, i = 0;
    ostream1 << "name: " << exchange.name << endl;
    ostream1 << "number: " << exchange.number << endl;

    ostream1 << "address: " << exchange.address << endl;
    size = static_cast<int>(exchange.currencies.size());
    if (size) {
        ostream1 << "records:" << endl;
        for (; i < size; i++) {
            Currency record = exchange.currencies[i];
            ostream1 << record.curr << " " << record.rate << endl;
        }
        ostream1 << endl;
    }
    return ostream1;
}

const char *Exchange::getName() {
    return name;
}

void Exchange::setName(char *name) {
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

const char *Exchange::getAddress() {
    return address;
}

void Exchange::setAddress(char *address) {
    delete[] this->address;
    this->address = new char[strlen(address) + 1];
    strcpy(this->address, address);
}

int Exchange::getNumber() {
    return number;
}

void Exchange::setNumber(int number) {
    this->number = number;
}

void Exchange::addNewCurrency(Currency currency) {
    this->currencies.emplace_back(currency);
}

void Exchange::updateCurrency(int recordNum, Currency currency){
    currencies[recordNum].curr = currency.curr;
    currencies[recordNum].rate = currency.rate;
}