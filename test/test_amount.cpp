#include <gtest/gtest.h>
#include "../Amount.h"

TEST(AmountTest, ConstructorAndGet) {
    const Amount a(10.50);  //
    EXPECT_DOUBLE_EQ(a.getValue(),10.50);

    const Amount b(10.555);
    EXPECT_DOUBLE_EQ(b.getValue(), 10.56); // arrotondamento eccesso

    const Amount d(10.554);
    EXPECT_DOUBLE_EQ(d.getValue(), 10.55); // arrotondamento per difetto
}

TEST(AmountTest, ValidationRules) {
    Amount a(10.0);

    // Testiamo lo Zero
    EXPECT_NO_THROW(a.setValue(0.0));
    EXPECT_TRUE(a.isZero());
    EXPECT_TRUE(a.isValid());

    // Testiamo input negativo
    a.setValue(-150.5);
    EXPECT_DOUBLE_EQ(a.getValue(), 150.5);
    EXPECT_TRUE(a.isPositive());
    EXPECT_FALSE(a.isNegative());
}

TEST(AmountTest, ThrowsOnInvalidInput) {
    Amount a(100.0);

    EXPECT_THROW(a.setValue(std::numeric_limits<double>::quiet_NaN()), std::invalid_argument);
    EXPECT_THROW(a.setValue(std::numeric_limits<double>::infinity()), std::invalid_argument);
}

TEST(AmountTest, RollbackOnFailure) {
    Amount a(35.5);
    const Amount expected(35.5);

    EXPECT_THROW(a.setValue(std::numeric_limits<double>::infinity()), std::invalid_argument); // Si imposta un valore non valido
    EXPECT_TRUE(a == expected); // Il Valore deve essere del precedente
}

TEST(AmountTest, ToStringFormatting) {
    const Amount a(10.55);
    EXPECT_EQ(a.toString(), "10.55"); // decimale > 10

    const Amount c(10.05);
    EXPECT_EQ(c.toString(), "10.05"); // decimale < 10

    const Amount d(5.0);
    EXPECT_EQ(d.toString(), "5.00"); // cifra tonda
}

TEST(AmountTest, EqualityAndComparison) {
    const Amount a(10.50);
    const Amount b(10.50);
    const Amount c(20.30);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    EXPECT_TRUE(a < c);
    EXPECT_FALSE(c < a);
    EXPECT_FALSE(a < b);
}