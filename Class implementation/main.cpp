/** Задание Класс "Обменный пункт (ОП)"
	Должно быть выполнено то, что написано в предисловии к заданиям.
    Кроме того:
    Должны быть перегружены операции: =, <<.
    Объект данного класса должны содержать: название банка, номер, адрес, перечень валют с указанием курсов
    покупки-продажи произвольной длины.
    Должен быть написан метод(ы) корректировки.
    Должны быть написаны методы, приведенные после строки
*/

#include <iostream>
#include "Exchange.hpp"


//using namespace std;

int main() {
    Currency currency{};
    currency.curr = "EUR/RUB";
    currency.rate = 75.98;
    Exchange sber = Exchange("Sber", 123, "Box, 1", currency);
    std::cout << sber;

    sber.getName();
    sber.getNumber();
    sber.getAddress();
    sber.setName("MSB");
    sber.setAddress("Line, 4");
    sber.setNumber(55);
    std::cout << sber;

    Exchange bank = Exchange("VTB", 357, "Steel, 5", currency);
    Currency currencyupdate{};
    currencyupdate.curr = "USD/RUB";
    currencyupdate.rate = 63.32;
    bank.addNewCurrency(currencyupdate);
    std::cout << bank;
    currencyupdate.rate = 68.71;
    bank.updateCurrency(1, currencyupdate);
    std::cout << bank;
    sber = bank;
    return 0;
}