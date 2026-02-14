#include <gtest/gtest.h>
#include "../Register.h"
#include <fstream>

TEST(RegisterTest, SortingTransactions) {
    Register reg;
    const Date d_vecchia(5, 5, 2023);
    const Date d_nuova(14, 6, 2024);

    reg.addTransaction(Transaction(d_nuova, Amount(100.0), TransactionType::ENTRATA, "Nuova"));
    reg.addTransaction(Transaction(d_vecchia, Amount(50.0), TransactionType::ENTRATA, "Vecchia"));

    // Verifica che nel vettore sono state ordinate (la vecchia deve essere al primo posto)
    const auto transactions = reg.getTransactions();
    EXPECT_EQ(transactions[0].getDescription(), "Vecchia");
    EXPECT_EQ(transactions[1].getDescription(), "Nuova");
}

TEST(RegisterTest, BalanceCalculation) {
    Register reg;

    reg.addTransaction(Transaction(Date(15,4,2024), Amount(100.0), TransactionType::ENTRATA, "Stipendio"));// Entrata di 100
    reg.addTransaction(Transaction(Date(2,5,2024), Amount(40.0), TransactionType::USCITA, "Pizza"));// Uscita di 40

    EXPECT_DOUBLE_EQ(reg.computeTotalBalance(), 60.0);
}

TEST(RegisterTest, FilePersistence) {
    Register regSalva;
    regSalva.addTransaction(Transaction(Date(10,5,2024), Amount(20.0), TransactionType::USCITA, "Caffè"));

    // Salva su un file di test
    const std::string testFile = "test_data.csv";
    regSalva.saveToFile(testFile);

    // Carica in un altro oggetto Register
    Register regCarica;
    regCarica.loadFromFile(testFile);

    // Verifica che i dati siano gli stessi
    EXPECT_EQ(regCarica.getTransactions().size(), 1);
    EXPECT_EQ(regCarica.getTransactions()[0].getDescription(), "Caffè");
    EXPECT_DOUBLE_EQ(regCarica.computeTotalBalance(), -20.0);

    // Pulizia: cancella il file di test creato
    std::remove(testFile.c_str());
}

TEST(RegisterTest, DateRangeFilter) {
    Register reg;
    reg.addTransaction(Transaction(Date(31, 12, 2024), Amount(30.0), TransactionType::ENTRATA, "Dicembre"));
    reg.addTransaction(Transaction(Date(1, 1, 2024), Amount(10.0), TransactionType::ENTRATA, "Gennaio"));
    reg.addTransaction(Transaction(Date(15, 6, 2024), Amount(20.0), TransactionType::ENTRATA, "Giugno"));


    // Filtra solo il periodo centrale
    const auto filtered = reg.getTransactionsInDateRange(Date(1, 2, 2024), Date(1, 7, 2024));

    ASSERT_EQ(filtered.size(), 1);
    EXPECT_EQ(filtered[0].getDescription(), "Giugno");
}