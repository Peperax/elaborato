#include "Transaction.h"
#include <sstream>

Transaction::Transaction(const Date &d,const Amount &amt, TransactionType t,
    const std::string &desc): date(d), amount(amt), type(t), description(desc) {
    if (!isValid()) {
        throw std::invalid_argument("La transazione non è valida");
    }
}


bool Transaction::isValid() const {
    if (type == TransactionType::ENTRATA && amount.isNegative()) {
        return false;
    }
    if (type == TransactionType::USCITA && amount.isPositive()) {
        return false;
    }
    return !description.empty();
}

void Transaction::setDate(const Date &d) {
    date = d;
    if (!isValid()) {
        throw std::invalid_argument("La data non è valida per la transazione");
    }
}

void Transaction::setAmount(const Amount &amt) {
    amount = amt;
    if (!isValid()) {
        throw std::invalid_argument("L'importo non valido per il tipo di transazione");
    }
}

void Transaction::setType(TransactionType t) {
    type = t;
    if (!isValid()) {
        throw std::invalid_argument("Il tipo di transazione non è valido per l'importo");
    }
}

void Transaction::setDescription(const std::string &desc) {
    if (desc.empty()) {
        throw std::invalid_argument("La descrizione non può essere vuota");
    }
    description = desc;
}
