#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "banking/Account.h"

using namespace banking;
using namespace testing;

class MockAccount : public Account {
public:
    explicit MockAccount(std::string id, double balance = 0)
        : Account(std::move(id), balance) {
    }
    MOCK_CONST_METHOD0(getId, std::string());
    MOCK_CONST_METHOD0(getBalance, double());
    MOCK_METHOD1(credit, void(double));
    MOCK_METHOD1(debit, bool(double));
};

TEST(AccountTest, ConstructorAndGetters) {
    Account acc("acc123", 100.0);
    EXPECT_EQ(acc.getId(), "acc123");
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, CreditIncreasesBalance) {
    Account acc("acc123", 100.0);
    acc.credit(50.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 150.0);
}

TEST(AccountTest, DebitDecreasesBalanceWhenSufficient) {
    Account acc("acc123", 100.0);
    EXPECT_TRUE(acc.debit(30.0));
    EXPECT_DOUBLE_EQ(acc.getBalance(), 70.0);
}

TEST(AccountTest, DebitFailsWhenInsufficient) {
    Account acc("acc123", 100.0);
    EXPECT_FALSE(acc.debit(150.0));
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}
TEST(AccountTest, CreditWithZero) {
    Account acc("acc123", 100.0);
    acc.credit(0.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, DebitExactBalance) {
    Account acc("acc123", 100.0);
    EXPECT_TRUE(acc.debit(100.0));
    EXPECT_DOUBLE_EQ(acc.getBalance(), 0.0);
}
TEST(AccountTest, CreditZeroAmount) {
    Account acc("acc123", 100.0);
    acc.credit(0.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}

TEST(AccountTest, DebitAllBalance) {
    Account acc("acc123", 100.0);
    EXPECT_TRUE(acc.debit(100.0));
    EXPECT_DOUBLE_EQ(acc.getBalance(), 0.0);
}
TEST(AccountTest, CreditNegativeAmount) {
    Account acc("acc123", 100.0);
    EXPECT_THROW(acc.credit(-50.0), std::invalid_argument);
}

TEST(AccountTest, DebitToNegative) {
    Account acc("acc123", 50.0);
    EXPECT_FALSE(acc.debit(100.0));
    EXPECT_DOUBLE_EQ(acc.getBalance(), 50.0);
}