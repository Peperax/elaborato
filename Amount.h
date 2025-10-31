#ifndef AMOUNT_H
#define AMOUNT_H

#include <string>

class Amount {
private:
    double value;

public:
    Amount(double v = 0.0);

    bool isValid() const;

    bool isPositive() const { return value > 0; }
    bool isNegative() const { return value < 0; }
    bool isZero() const { return value == 0; }

    double getValue() const { return value; }
    void setValue(double v);

};



#endif //AMOUNT_H
