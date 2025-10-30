//
// Created by pablo on 10/30/25.
//

#include "Transaction.h"
#include <sstream>

Transaction::Transaction(const std::string &d, double i, const std::string &t,
    const std::string &desc): data(d), import(i), type(t), description(desc) {
}

std::string Transaction::getData() const {
    return data;
}

double Transaction::getImport() const {
    return import;
}

std::string Transaction::getType() const {
    return type;
}

std::string Transaction::getDescription() const {
    return description;
}
