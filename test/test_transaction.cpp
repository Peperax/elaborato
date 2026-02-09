#include <gtest/gtest.h>
#include "../Transaction.h"

TEST(TransactionTest, ValidationSuccess) {
    Date d(10, 2, 2024);
    Amount a(100.0);
    Transaction t(d, a, TransactionType::ENTRATA, "Stipendio");
    EXPECT_TRUE(t.isValid());
}


TEST(TransactionTest, CSVSerialization) {
    Date d(15, 3, 2024);
    Amount a(200.0);
    Transaction t1(d, a, TransactionType::ENTRATA, "Regalo");

    // Trasforma in stringa
    std::string csv = t1.toCSV();

    // Ricostruisce l'oggetto dalla stringa
    Transaction t2 = Transaction::fromCSV(csv);

    // Verifica che i dati sono identici
    EXPECT_EQ(t1.getDescription(), t2.getDescription());
    EXPECT_DOUBLE_EQ(t1.getImport().getValue(), t2.getImport().getValue());
    EXPECT_EQ(t1.getData().toString(), t2.getData().toString());
}

TEST(TransactionTest, Comparison) {
    Date d1(1, 1, 2024);
    Date d2(2, 1, 2024);
    Transaction t1(d1, Amount(10.0), TransactionType::ENTRATA, "Prima");
    Transaction t2(d2, Amount(10.0), TransactionType::ENTRATA, "Seconda");

    EXPECT_TRUE(t1 < t2);
    EXPECT_FALSE(t2 < t1);
}