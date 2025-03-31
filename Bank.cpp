#include "Bank.h"
#include <mutex>
#include <stdexcept>

Bank::Bank(int numAccounts) {
    for (int i = 0; i < numAccounts; ++i) {
        accounts.emplace_back(std::make_unique<BankAccount>());
    }
}

void Bank::transfer(int from, int to, int amount) {
    if (from == to) return;

    try {
        std::unique_lock<std::mutex> lock1(accounts[from]->mtx, std::defer_lock);
        std::unique_lock<std::mutex> lock2(accounts[to]->mtx, std::defer_lock);
        std::lock(lock1, lock2);

        if (accounts[from]->balance < amount)
            throw std::runtime_error("Insufficient funds for transfer");

        accounts[from]->balance -= amount;
        accounts[to]->balance += amount;
        successCount++;
    } catch (...) {
        failureCount++;
    }
}
