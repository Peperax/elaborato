#include "Register.h"
#include <fstream>
#include <algorithm> // Necessario per std::sort

void Register::addTransaction(const Transaction& t) {
    transactions.push_back(t);
    std::sort(transactions.begin(), transactions.end());
}

void Register::removeTransaction(const int index) {
    if (index >= 0 && index < transactions.size()) {
        transactions.erase(transactions.begin() + index);
    }
}

double Register::computeTotalBalance() const {
    long long totalCents = 0;
    for (const auto& t : transactions) {
        const long long val = t.getImport().getCents();

        if (t.getType() == TransactionType::ENTRATA) {
            totalCents += val;
        } else {
            // Se è USCITA, si sottrae
            totalCents -= val;
        }
    }
    return static_cast<double>(totalCents) / 100.0;
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
    else{
        throw std::runtime_error("Impossibile aprire il file per il caricamento");
    }

    // Dopo il caricamento, deve essere ordinato
    std::sort(transactions.begin(), transactions.end());
}

std::vector<Transaction> Register::getTransactionsInDateRange(const Date& start, const Date& end) const {
    std::vector<Transaction> filtered;

    for (const auto& t : transactions) {
        if (!(t.getDate() < start) && !(end < t.getDate())) {
            filtered.push_back(t);
        }
    }
    return filtered;
}