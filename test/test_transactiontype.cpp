#include <gtest/gtest.h>
#include "../TransactionType.h"
#include <stdexcept>

TEST(TransactionTypeTest, TypeToString) {
    // Verifica che ENTRATA restituisca la stringa corretta
    EXPECT_EQ(typeToString(TransactionType::ENTRATA), "ENTRATA");

    // Verifica che USCITA restituisca la stringa corretta
    EXPECT_EQ(typeToString(TransactionType::USCITA), "USCITA");
}

TEST(TransactionTypeTest, StringToTypeValid) {
    // Test con stringhe tutte maiuscole
    EXPECT_EQ(stringToType("ENTRATA"), TransactionType::ENTRATA);
    EXPECT_EQ(stringToType("USCITA"), TransactionType::USCITA);

    // Test con stringhe tutte minuscole/combinato
    EXPECT_EQ(stringToType("entrata"), TransactionType::ENTRATA);
    EXPECT_EQ(stringToType("Uscita"), TransactionType::USCITA);
}

TEST(TransactionTypeTest, StringToTypeInvalid) {
    // Verifica che una stringa lanci l'eccezione std::invalid_argument
    EXPECT_THROW(stringToType("QUALCOSA_DI_ERRATO"), std::invalid_argument);
    EXPECT_THROW(stringToType(""), std::invalid_argument);
}