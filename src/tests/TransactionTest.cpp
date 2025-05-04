#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "banking/Transaction.h"
#include "banking/Account.h"

using namespace banking;
using namespace testing;

class MockAccount : public Account {
public:
    explicit MockAccount(std::string id, double balance = 0)
        : Account(std::move(id), balance) {
    }
    MOCK_METHOD(bool, debit, (double), (override));
    MOCK_METHOD(void, credit, (double), (override));
};

TEST(TransactionTest, SuccessfulTransfer) {
    Account from("from", 200.0);
    Account to("to", 50.0);

    EXPECT_TRUE(Transaction::transfer(from, to, 100.0));
    EXPECT_DOUBLE_EQ(from.getBalance(), 100.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 150.0);
}

TEST(TransactionTest, FailedTransferInsufficientFunds) {
    Account from("from", 50.0);
    Account to("to", 200.0);

    EXPECT_FALSE(Transaction::transfer(from, to, 100.0));
    EXPECT_DOUBLE_EQ(from.getBalance(), 50.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 200.0);
}

TEST(TransactionTest, TransferZeroAmount) {
    Account from("from", 200.0);
    Account to("to", 50.0);

    EXPECT_TRUE(Transaction::transfer(from, to, 0.0));
    EXPECT_DOUBLE_EQ(from.getBalance(), 200.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 50.0);
}

TEST(TransactionTest, TransferNegativeAmountThrows) {
    Account from("from", 200.0);
    Account to("to", 50.0);

    EXPECT_THROW(Transaction::transfer(from, to, -50.0), std::invalid_argument);
    EXPECT_DOUBLE_EQ(from.getBalance(), 200.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 50.0);
}

TEST(TransactionTest, TransferWithMocks) {
    MockAccount from("from", 200.0);
    MockAccount to("to", 50.0);

    EXPECT_CALL(from, debit(100.0)).WillOnce(Return(true));
    EXPECT_CALL(to, credit(100.0)).Times(1);

    EXPECT_TRUE(Transaction::transfer(from, to, 100.0));
}

TEST(TransactionTest, FailedTransferWithMocks) {
    MockAccount from("from", 50.0);
    MockAccount to("to", 200.0);

    EXPECT_CALL(from, debit(100.0)).WillOnce(Return(false));
    EXPECT_CALL(to, credit(_)).Times(0);

    EXPECT_FALSE(Transaction::transfer(from, to, 100.0));
}