#include "Amount.h"
#include <stdexcept>
#include <cmath>

Amount::Amount(double v): cents(static_cast<long long>(std::round(std::abs(v) * 100))) {
    if (!isValid()) {
        throw std::invalid_argument("L'importo non è valido");
    }
}

bool Amount::isValid() const {
    return cents>=0;
}

void Amount::setValue(double v) {
    long long oldCents = cents;
    cents = static_cast<long long>(std::round(std::abs(v) * 100));
    if (!isValid()) {
        cents = oldCents;
        throw std::invalid_argument("L'importo non è valido");
    }
}

std::string Amount::toString() const {
    long long absoluteCents = std::abs(cents);
    std::string s = std::to_string(cents / 100) + ".";

    long long decimalPart = absoluteCents % 100;
    if (decimalPart < 10) s += "0";

    s += std::to_string(decimalPart);
    return s;
}