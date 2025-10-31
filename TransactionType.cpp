#include "TransactionType.h"
#include <stdexcept>

std::string typeToString(TransactionType type) {
    switch (type) {
        case TransactionType::ENTRATA: return "ENTRATA";
        case TransactionType::USCITA: return "USCITA";
        default: throw std::invalid_argument("Il tipo di transazione non è valido");
    }
}

TransactionType stringToType(const std::string& str) {
    if (str == "ENTRATA" || str == "Entrata" || str == "entrata") return TransactionType::ENTRATA;
    if (str == "USCITA" || str == "Uscita" || str == "uscita") return TransactionType::USCITA;
    throw std::invalid_argument("Il tipo di transazione non è riconosciuto: " + str);
}