#include "BankAccount.h"
#include <stdexcept>

BankAccount::BankAccount() : balance(0) {}

void BankAccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    balance += amount;
}

void BankAccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (balance < amount)
        throw std::runtime_error("Insufficient funds");
    balance -= amount;
}

int BankAccount::getBalance() const {
    std::lock_guard<std::mutex> lock(mtx);
    return balance;
}
