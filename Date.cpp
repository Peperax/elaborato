#include "Date.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

Date::Date(const int d = 1, const int m = 1, const int y = 2026): day(d), month(m), year(y) {
    if (!isValid()) {
        throw std::invalid_argument("La data non è valida");
    }
}

bool Date::isValid() const {
    if (year < 1925 || year > 2125) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    const int daysForMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDays = daysForMonth[month - 1];

    if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
        maxDays = 29;
    }
    return day <= maxDays;
}

void Date::setDay(const int d) {
    const int oldDay = day;
    day = d;
    if (!isValid()) {
        day = oldDay;
        throw std::invalid_argument("Il giorno non è valido");
    }
}

void Date::setMonth(const int m) {
    const int oldMonth = month;
    month = m;
    if (!isValid()) {
        month = oldMonth;
        throw std::invalid_argument("Il mese non è valido");
    }
}

void Date::setYear(const int y) {
    const int oldYear = year;
    year = y;
    if (!isValid()) {
        year = oldYear;
        throw std::invalid_argument("L'anno non è valido");
    }
}

bool Date::operator<(const Date& other) const {
    if (year != other.year)
        return year < other.year;
    if (month != other.month)
        return month < other.month;
    return day < other.day;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

std::string Date::toString() const {
    std::stringstream ss;
    // Impostiamo con il formato GG/MM/AAAA (es: 01/05/2023)
    ss << std::setfill('0') << std::setw(2) << day << "/"
       << std::setfill('0') << std::setw(2) << month << "/"
       << year;
    return ss.str();
}

Date Date::fromString(const std::string &dateStr) {
    int d, m, y;
    char s1, s2;
    std::stringstream ss(dateStr);

    if (!(ss >> d >> s1 >> m >> s2 >> y) || s1 != '/' || s2 != '/') {
        throw std::invalid_argument("Il formato della data non è valido. Usa GG/MM/AAAA");
    }

    return {d, m, y};
}