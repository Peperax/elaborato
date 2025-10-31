#include "Date.h"
#include <stdexcept>

Date::Date(int d, int m, int y) {
    if (!isValid()) {
        throw std::invalid_argument("La data non è valida");
    }
}

bool Date::isValid() const {
    if (year < 1925 || year > 2125) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    int daysForMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDays = daysForMonth[month - 1];

    if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
        maxDays = 29;
    }
    return day <= maxDays;
}

void Date::setDay(int d) {
    int oldDay = day;
    day = d;
    if (!isValid()) {
        day = oldDay;
        throw std::invalid_argument("Il giorno non è valido");
    }
}

void Date::setMonth(int m) {
    int oldMonth = month;
    month = m;
    if (!isValid()) {
        month = oldMonth;
        throw std::invalid_argument("Il mese non è valido");
    }
}

void Date::setYear(int y) {
    year = y;
    if (!isValid()) {
        year = 2000;
        throw std::invalid_argument("L'anno non è valido");
    }
}
