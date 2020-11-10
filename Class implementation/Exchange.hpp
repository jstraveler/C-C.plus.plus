#pragma once // Исключить повторное включение

#include <vector>
//#include "MString.hpp"
#include <cstring>

//using namespace std;

struct Currency { // Структура для хранения данных о валютном курсе
    char *curr;
    double rate;
};

class Exchange { // Класс обменный пункт
    char *name{new char[80]};
    int number{0};
    char *address{new char[80]};
    std::vector<Currency> currencies;
public:
    Exchange() { // Конструктор по умолчанию
        name = new char[1];
        number = 0;
        address = new char[1];
    }

    Exchange(char const *name, int number, char const *address, Currency record) { // Конструктор пользовательских данных
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->number = number;
        this->address = new char[strlen(address) + 1];
        strcpy(this->address, address);
        currencies.emplace_back(record);
    }

    Exchange(Exchange const &exchange) { // Конструтор копии
        delete[] name;
        name = new char[strlen(exchange.name) + 1];
        strcpy(name, exchange.name);
        number = exchange.number;
        delete[] address;
        address = new char[strlen(exchange.address) + 1];
        strcpy(address, exchange.address);
        if (!exchange.currencies.empty()) {
            auto size = exchange.currencies.size();
            for (int i = 0; i < size; ++i) {
                currencies.push_back(exchange.currencies[i]);
            }
        }
    }

    Exchange &operator=(Exchange const &that);
    friend std::ostream &operator<<(std::ostream &ostream1, const Exchange &exchange);
    const char *getName();
    void setName(char *name);
    const char *getAddress();
    void setAddress(char *address);
    int getNumber();
    void setNumber(int number);
    void addNewCurrency(Currency currency);
    void updateCurrency(int recordNum, Currency currency);
};