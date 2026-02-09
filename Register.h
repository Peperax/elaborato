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

    double computeTotalBalance() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    const std::vector<Transaction>& getTransactions() const { return transactions; }

};



#endif //REGISTER_H
