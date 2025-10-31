#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Date.h"
#include "TransactionType.h"
#include "Amount.h"


class Transaction {

private:
    Date date;
    Amount amount;
    TransactionType type;
    std::string description;

public:
    Transaction(const Date& date, const Amount& amount, TransactionType type, const std::string& description);

    bool isValid() const;

    [[nodiscard]] Date getData() const{ return date; };
    [[nodiscard]] Amount getImport() const{ return amount; }
    [[nodiscard]] TransactionType getType() const{ return type; };
    [[nodiscard]] std::string getDescription() const{ return description; };

    void setDate(const Date& d);
    void setAmount(const Amount& amt);
    void setType(TransactionType t);
    void setDescription(const std::string& desc);
};



#endif //TRANSACTION_H
