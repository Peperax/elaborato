#include <gtest/gtest.h>
#include "../Transaction.h"

TEST(TransactionTest, ValidationSuccess) {
    const Date d(10, 2, 2024);
    const Amount a(100.0);
    const Transaction t(d, a, TransactionType::ENTRATA, "Stipendio");
    EXPECT_TRUE(t.isValid());
}

TEST(TransactionTest, ValidationFailure) {
    const Date d(10, 2, 2024);
    const Amount a(100.0);

    EXPECT_THROW({
        Transaction t(d, a, TransactionType::ENTRATA, ""); // Descrizione vuota
    }, std::invalid_argument);
}

TEST(TransactionTest, SetterRollback) {
    Transaction t(Date(1, 1, 2024), Amount(10.0), TransactionType::ENTRATA, "Valido");

    // Si prova a mettere una descrizione non valida
    EXPECT_THROW(t.setDescription(""), std::invalid_argument);

    // Verifichiamo che la descrizione è quello di prima
    EXPECT_EQ(t.getDescription(), "Valido");
}
TEST(TransactionTest, CSVSerialization) {
    const Date d(15, 3, 2024);
    const Amount a(200.0);
    const Transaction t1(d, a, TransactionType::ENTRATA, "Regalo");

    // Trasforma in stringa
    const std::string csv = t1.toCSV();

    // Ricostruisce l'oggetto dalla stringa
    const Transaction t2 = Transaction::fromCSV(csv);

    // Verifica che i dati sono identici
    EXPECT_EQ(t1.getDescription(), t2.getDescription());
    EXPECT_EQ(t1.getImport().getCents(), t2.getImport().getCents());
    EXPECT_EQ(t1.getDate().toString(), t2.getDate().toString());
    EXPECT_EQ(t1.getType(), t2.getType());
}

TEST(TransactionTest, Comparison) {
    const Date d1(1, 1, 2024);
    const Date d2(2, 1, 2024);
    const Transaction t1(d1, Amount(10.0), TransactionType::ENTRATA, "Prima");
    const Transaction t2(d2, Amount(10.0), TransactionType::ENTRATA, "Seconda");

    EXPECT_TRUE(t1 < t2);
    EXPECT_FALSE(t2 < t1);
}