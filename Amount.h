#ifndef AMOUNT_H
#define AMOUNT_H

#include <string>

/**
 * Rappresenta un importo finanziario.
 */

class Amount {
private:
    double value;

public:
    explicit Amount(double v = 0.0);

    bool isValid() const;

    bool isPositive() const { return value > 0; }
    bool isNegative() const { return value < 0; }
    bool isZero() const { return value == 0; }

    double getValue() const { return value; }
    void setValue(double v);

    std::string toString() const;
};

#endif //AMOUNT_H