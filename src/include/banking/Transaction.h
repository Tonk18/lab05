#pragma once
#include "Account.h"
#include <string>

namespace banking {
    class Transaction {
    public:
        static bool transfer(Account& from, Account& to, double amount);
    };
}