#include "banking/Account.h"

namespace banking {
    Account::Account(std::string id, double balance) : id(std::move(id)), balance(balance) {}

    std::string Account::getId() const { return id; }

    double Account::getBalance() const { return balance; }

    void Account::credit(double amount) { balance += amount; }

    bool Account::debit(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
}