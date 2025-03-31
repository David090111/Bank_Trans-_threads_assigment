#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <mutex>

class BankAccount {
private:
    int balance;
    mutable std::mutex mtx;

public:
    BankAccount();
    void deposit(int amount);
    void withdraw(int amount);
    int getBalance() const;

    BankAccount(const BankAccount&) = delete;
    BankAccount& operator=(const BankAccount&) = delete;

    friend class Bank;
};

#endif
