#include "banking/Transaction.h"
#include <stdexcept>

namespace banking {
    bool Transaction::transfer(Account& from, Account& to, double amount) {
        if (amount < 0) {
            throw std::invalid_argument("Transfer amount cannot be negative");
        }
        if (amount == 0) {
            return true; // Нулевой перевод считается успешным
        }
        if (from.debit(amount)) {
            to.credit(amount);
            return true;
        }
        return false;
    }
}