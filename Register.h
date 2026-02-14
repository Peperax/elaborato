#ifndef REGISTER_H
#define REGISTER_H

#include <vector>
#include <string>
#include "Transaction.h"

/**
 * Rappresenta un registro finanziario per la gestione delle transazioni.
 */

class Register {
private:
    std::vector<Transaction> transactions;

public:
    void addTransaction(const Transaction& t);
    void removeTransaction(int index);

    [[nodiscard]] double computeTotalBalance() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    [[nodiscard]] const std::vector<Transaction>& getTransactions() const { return transactions; }

    [[nodiscard]] std::vector<Transaction> getTransactionsInDateRange(const Date& start, const Date& end) const;
};



#endif //REGISTER_H
