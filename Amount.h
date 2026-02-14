#ifndef AMOUNT_H
#define AMOUNT_H

#include <string>

/**
 * Rappresenta un importo finanziario.
 */

class Amount {
private:
    long long cents;

public:
    explicit Amount(double v = 0.0);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] bool isPositive() const { return cents > 0; }
    [[nodiscard]] bool isNegative() const { return cents < 0; }
    [[nodiscard]] bool isZero() const { return cents == 0; }

    [[nodiscard]] double getValue() const { return static_cast<double>(cents) / 100.0; }
    void setValue(double v);

    [[nodiscard]] long long getCents() const { return cents; }

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] bool operator<(const Amount& other) const ;
    [[nodiscard]] bool operator==(const Amount& other) const ;
};

#endif //AMOUNT_H