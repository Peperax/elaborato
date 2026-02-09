#include "Register.h"
#include <fstream>
#include <algorithm> // Necessario per std::sort

void Register::addTransaction(const Transaction& t) {
    transactions.push_back(t);
    std::sort(transactions.begin(), transactions.end());
}

void Register::removeTransaction(int index) {
    if (index >= 0 && index < transactions.size()) {
        transactions.erase(transactions.begin() + index);
    }
}

double Register::computeTotalBalance() const {
    double total = 0.0;
    for (const auto& t : transactions) {
        // Si ha il valore numerico puro
        double val = std::abs(t.getImport().getValue());

        if (t.getType() == TransactionType::ENTRATA) {
            total += val;
        } else {
            // Se è USCITA, si sottrae
            total -= val;
        }
    }
    return total;
}

void Register::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& t : transactions) {
            file << t.toCSV() << "\n";
        }
        file.close();
    }
}

void Register::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    transactions.clear(); // Pulisce il registro attuale prima del caricamento

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (!line.empty()) {
                transactions.push_back(Transaction::fromCSV(line));
            }
        }
        file.close();
    }

    // Dopo il caricamento, deve essere ordinato
    std::sort(transactions.begin(), transactions.end());
}