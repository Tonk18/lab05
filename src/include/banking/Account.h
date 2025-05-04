#pragma once
#include <string>
#include <vector>

namespace banking {
    class Account {
    private:
        std::string id;
        double balance;
    public:
        explicit Account(std::string id, double balance = 0);
        std::string getId() const;
        double getBalance() const;
        void credit(double amount);
        bool debit(double amount);
    };
}