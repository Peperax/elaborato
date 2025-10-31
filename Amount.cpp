#include "Amount.h"
#include <stdexcept>
#include <cmath>

Amount::Amount(double v) {
    if (!isValid()) {
        throw std::invalid_argument("L'importo non è valido");
    }
}

bool Amount::isValid() const {
    return !std::isnan(value) && !std::isinf(value);
}

void Amount::setValue(double v) {
    double oldValue = value;
    value = v;
    if (!isValid()) {
        value = oldValue;
        throw std::invalid_argument("L'importo non è valido");
    }
}
