#include <gtest/gtest.h>
#include "../Date.h"
#include <stdexcept>

TEST(DateTest, ValidDate) {
    EXPECT_NO_THROW(Date d(15, 6, 2023));
    const Date d(1, 1, 2024);
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
    const Date original(10, 10, 2023);

    EXPECT_THROW(d.setDay(40), std::invalid_argument); // Si Imposta un giorno non valido
    EXPECT_TRUE(d == original); // Il Valore deve essere del precedente
}

TEST(DateTest, Serialization) {
    const Date original(5, 2, 2024);

    // Verifichiamo l' inserimento dello zero
    const std::string s = original.toString();
    EXPECT_EQ(s, "05/02/2024");

    // Verifichiamo che fromString ricostruisca l'oggetto identico
    const Date reconstructed = Date::fromString(s);
    EXPECT_TRUE(original == reconstructed);
}

TEST(DateTest, EqualityandComparison) {
    const Date d1(15, 6, 2023);
    const Date d2(15, 6, 2023);
    const Date d3(16, 6, 2023);

    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 == d3);
    EXPECT_TRUE(d1 < d3);
    EXPECT_FALSE(d3 < d2);
}