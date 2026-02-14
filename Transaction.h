#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Date.h"
#include "TransactionType.h"
#include "Amount.h"

/**
 * Rappresenta una singola operazione del registro finanziario.
 */

class Transaction {

private:
    Date date;
    Amount amount;
    TransactionType type;
    std::string description;

public:
    Transaction(const Date& date, const Amount& amount, TransactionType type, const std::string& description);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] Date getDate() const{ return date; };
    [[nodiscard]] Amount getImport() const{ return amount; }
    [[nodiscard]] TransactionType getType() const{ return type; };
    [[nodiscard]] std::string getDescription() const{ return description; };

    void setDate(const Date& d);
    void setAmount(const Amount& amt);
    void setType(TransactionType t);
    void setDescription(const std::string& desc);

    [[nodiscard]] std::string toCSV() const;
    static Transaction fromCSV(const std::string& csvLine);

    bool operator<(const Transaction& other) const;
};

#endif //TRANSACTION_H
