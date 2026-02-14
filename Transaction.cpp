#include "Transaction.h"
#include <sstream>

Transaction::Transaction(const Date &d,const Amount &amt, TransactionType t,
    const std::string &desc): date(d), amount(amt), type(t), description(desc) {
    if (!isValid()) {
        throw std::invalid_argument("La transazione non è valida");
    }
}

bool Transaction::isValid() const {
    if (amount.isZero()) {
        return false;
    }
    return !description.empty();
}

void Transaction::setDate(const Date &d) {
    const Date oldDate = date;
    date = d;
    if (!isValid()) {
        date = oldDate;
        throw std::invalid_argument("La data non è valida per la transazione");
    }
}

void Transaction::setAmount(const Amount &amt) {
    const Amount oldAmount = amt;
    amount = amt;
    if (!isValid()) {
        amount = oldAmount;
        throw std::invalid_argument("L'importo non valido per il tipo di transazione");
    }
}

void Transaction::setType(const TransactionType t) {
    const TransactionType oldType = t;
    type = t;
    if (!isValid()) {
        type = oldType;
        throw std::invalid_argument("Il tipo di transazione non è valido per l'importo");
    }
}

void Transaction::setDescription(const std::string &desc) {
    const std::string oldDesc = description;
    description = desc;
    if (!isValid()) {
        description = oldDesc;
        throw std::invalid_argument("La descrizione non può essere vuota");
    }
    description = desc;
}

std::string Transaction::toCSV() const {
    std::stringstream ss;
    ss << date.toString() << ";"
       << amount.getValue() << ";"
       << typeToString(type) << ";"
       << description;
    return ss.str();
}

Transaction Transaction::fromCSV(const std::string &csvLine) {
    std::stringstream ss(csvLine);
    std::string dateStr, typeStr, description;
    double amountValue;

    std::getline(ss, dateStr, ';');
    ss >> amountValue;
    ss.ignore();
    std::getline(ss, typeStr, ';');
    std::getline(ss, description);

    Date date = Date::fromString(dateStr);
    Amount amount(amountValue);
    TransactionType type = stringToType(typeStr);

    return {date, amount, type, description};
}

bool Transaction::operator<(const Transaction& other) const {
    return date < other.date;
}

bool Transaction::operator==(const Transaction& other) const {
    return date == other.date &&
           amount == other.amount &&
           type == other.type &&
           description == other.description;
}