#ifndef BANK_H
#define BANK_H

#include <vector>
#include <atomic>
#include <memory>
#include "BankAccount.h"

class Bank {
public:
    std::vector<std::unique_ptr<BankAccount>> accounts;
    std::atomic<int> successCount{0};
    std::atomic<int> failureCount{0};

    Bank(int numAccounts);
    void transfer(int from, int to, int amount);
};

#endif
