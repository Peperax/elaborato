#ifndef TRANSACTIONTYPE_H
#define TRANSACTIONTYPE_H

#include <string>

/**
 * Definisce la natura della transazione (Entrata o Uscita).
 */

enum class TransactionType {
ENTRATA,
USCITA
};

std::string typeToString(TransactionType type);
TransactionType stringToType(const std::string& str);

#endif //TRANSACTIONTYPE_H