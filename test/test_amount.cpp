#include <gtest/gtest.h>
#include "../Amount.h"

TEST(AmountTest, ConstructorAndGet) {
    Amount a(10.5);
    EXPECT_DOUBLE_EQ(a.getValue(),10.5);
}

TEST(AmountTest, ValidationRules) {
    Amount a(10.0);

    // Testiamo lo Zero
    EXPECT_NO_THROW(a.setValue(0.0));
    EXPECT_TRUE(a.isZero());

    // Testiamo valori positivi/negativi
    a.setValue(150.0);
    EXPECT_TRUE(a.isPositive());
    EXPECT_FALSE(a.isNegative());
}

TEST(AmountTest, ThrowsOnInvalidInput) {
    Amount a(100.0);

    EXPECT_THROW(a.setValue(std::numeric_limits<double>::quiet_NaN()), std::invalid_argument);
}

TEST(AmountTest, RollbackOnFailure) {
    Amount a(35.5);
    // Si Imposta un valore non valido
    try {
        a.setValue(std::numeric_limits<double>::infinity());
    } catch (...) {}

    EXPECT_EQ(a.getValue(), 35.5); // Il Valore deve essere del precedente
}