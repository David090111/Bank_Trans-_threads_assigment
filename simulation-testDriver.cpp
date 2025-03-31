#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "Bank.h"
#include "BankAccount.h"
using namespace std;

// Simulate deposit/withdraw for one account
void simulateTransactions(Bank& bank, int index) {
    for (int i = 0; i < 100; ++i) {
        int amount = rand() % 200 + 1;
        int action = rand() % 2;

        try {
            if (action == 0) {
                bank.accounts[index]->deposit(amount);
                bank.successCount++;
            }
            else {
                bank.accounts[index]->withdraw(amount);
                bank.successCount++;
            }
        }
        catch (...) {
            bank.failureCount++;
        }
    }
}

// Simulate transfers between random accounts
void simulateTransfers(Bank& bank, int numAccounts) {
    for (int i = 0; i < 100; ++i) {
        int from = rand() % numAccounts;
        int to = rand() % numAccounts;
        int amount = rand() % 300 + 1;
        bank.transfer(from, to, amount);
    }
}

// Function to test deposit functionality
void testDeposit(BankAccount& account) {
    account.deposit(500);
    std::cout << "Deposit Test Passed: Current Balance = " << account.getBalance() << std::endl;
}

// Function to test withdrawal functionality
void testWithdraw(BankAccount& account) {
    try {
        account.withdraw(200);
        std::cout << "Withdrawal Test Passed: Current Balance = " << account.getBalance() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Withdrawal Test Failed: " << e.what() << std::endl;
    }
}

// Function to test transfer functionality between accounts
void testTransfer(Bank& bank, int from, int to, int amount) {
    bank.transfer(from, to, amount);
    std::cout << "Transfer Test Passed: Account " << from << " = " << bank.accounts[from]->getBalance()
        << ", Account " << to << " = " << bank.accounts[to]->getBalance() << std::endl;
}

// Test driver for BankAccount and Bank functionalities
void testDriver() {
    // Create Bank with 2 accounts for simplicity
    Bank bank(2);

    // Initialize account balances
    bank.accounts[0]->deposit(1000);
    bank.accounts[1]->deposit(500);

    std::cout << "Initial Balances:\n";
    std::cout << "Account 0: $" << bank.accounts[0]->getBalance() << "\n";
    std::cout << "Account 1: $" << bank.accounts[1]->getBalance() << "\n";

    // Test deposit functionality
    testDeposit(*bank.accounts[0]);

    // Test withdrawal functionality
    testWithdraw(*bank.accounts[1]);

    // Test transfer functionality
    testTransfer(bank, 0, 1, 300);

    // Final balances
    std::cout << "Final Balances:\n";
    std::cout << "Account 0: $" << bank.accounts[0]->getBalance() << "\n";
    std::cout << "Account 1: $" << bank.accounts[1]->getBalance() << "\n";
}

int main()
  while(true){
    cout << "Choose 1 is testDriver, 2 is simulation: ";
    int choose;
    cin >> choose;
    if (choose == 2) {
    srand(static_cast<unsigned>(time(nullptr)));
    const int NUM_ACCOUNTS = 5;

    Bank bank(NUM_ACCOUNTS);

    // Initialize each account with $1000
    for (int i = 0; i < NUM_ACCOUNTS; ++i) {
        bank.accounts[i]->deposit(1000);
    }

    // 5 threads for deposit/withdraw, 5 for transfer
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_ACCOUNTS; ++i) {
        threads.emplace_back(simulateTransactions, std::ref(bank), i);
    }

    for (int i = 0; i < NUM_ACCOUNTS; ++i) {
        threads.emplace_back(simulateTransfers, std::ref(bank), NUM_ACCOUNTS);
    }

    for (auto& t : threads) {
        t.join();
    }

    // Output final balances
    std::cout << "\nFinal Account Balances:\n";
    for (int i = 0; i < NUM_ACCOUNTS; ++i) {
        std::cout << "Account " << i + 1 << " Final Balance: $" << bank.accounts[i]->getBalance() << "\n";
    }

    // Output transaction log
    std::cout << "\nTotal Successful Transactions: " << bank.successCount << std::endl;
    std::cout << "Total Failed Transactions: " << bank.failureCount << std::endl;
}
    else if (choose == 1) {
        try {
            testDriver();
        }
        catch (const std::exception& e) {
            std::cerr << "Test driver error: " << e.what() << std::endl;
        }
    }
	else {
		cout << "Invalid input!";
	}}

    return 0;
}
