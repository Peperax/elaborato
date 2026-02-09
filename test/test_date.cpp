#include <gtest/gtest.h>
#include "../Date.h"
#include <stdexcept>

TEST(DateTest, ValidDate) {
    EXPECT_NO_THROW(Date d(15, 6, 2023));
    Date d(1, 1, 2024);
    EXPECT_EQ(d.getDay(), 1);
    EXPECT_EQ(d.getMonth(), 1);
    EXPECT_EQ(d.getYear(), 2024);
}

TEST(DateTest, InvalidDatesThrow) {
    EXPECT_THROW(Date d(32, 1, 2023), std::invalid_argument); // Giorno impossibile
    EXPECT_THROW(Date d(15, 13, 2023), std::invalid_argument); // Mese impossibile
    EXPECT_THROW(Date d(31, 4, 2023), std::invalid_argument); // Aprile ha 30 giorni
}

TEST(DateTest, LeapYearLogic) {
    // 2024 è bisestile -> 29 Febbraio OK
    EXPECT_NO_THROW(Date d(29, 2, 2024));

    // 2023 NON è bisestile -> 29 Febbraio ERRORE
    EXPECT_THROW(Date d(29, 2, 2023), std::invalid_argument);

    // Test casi particolari (1900 non bisestile)
    EXPECT_THROW(Date d(29, 2, 1900), std::invalid_argument);
    // (2100 non è bisestile)
    EXPECT_THROW(Date d(29, 2, 2100), std::invalid_argument);
}

TEST(DateTest, SetterRollback) {
    Date d(10, 10, 2023);
    // Si Imposta un giorno non valido
    try {
        d.setDay(40);
    } catch (...) {}
    EXPECT_EQ(d.getDay(), 10); // Il Valore deve essere del precedente
}

TEST(DateTest, ComparisonOperator) {
    Date d1(1, 1, 2023);
    Date d2(1, 1, 2024);
    EXPECT_TRUE(d1 < d2);
    EXPECT_FALSE(d2 < d1);
}