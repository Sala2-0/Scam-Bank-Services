// Account implementation file

#include <iostream>
#include <string>
#include <random>

#include "Account.h"

// Random unique id generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> id(000000, 999999);

// Constructor
Account::Account(const std::string user, const std::string pass)
: username{user}, password{pass}, uniqueId{id(gen)}, balance{10000.0} {
    std::cout << "Account: " << username << " has been created." << std::endl;
    std::cout << "Unique user ID: " << uniqueId << std::endl;
    std::cout << "Balance: " << balance << std::endl;
}

// Deposit
bool Account::deposit(double amount) {
    balance += amount;
    return true;
}

// Withdraw
bool Account::withdraw(double amount) {
    if (balance - amount >= 0) {
        balance -= amount;
        return true;
    }

    return false;
}

// Add transaction history
void Account::addTransactionHistory(const std::string &history) {
    if (transactionHistory.size() == 5) {
        transactionHistory.erase(transactionHistory.begin());
    }

    transactionHistory.push_back(history);
}

// Show transaction history
void Account::showTransactionHistory() const {
    if (transactionHistory.size() == 0) {
        std::cout << "No recent transactions on this account" << std::endl;
    }

    // Reverse loop for vector
    else {
        std::cout << "== Recent transactions ==" << std::endl;
        for (auto it = transactionHistory.rbegin(); it != transactionHistory.rend(); it++) {
            std::cout << *it << std::endl;
        }
    }
}

// Getters
std::string Account::getUsername() const { return username; }
int Account::getUniqueId() const { return uniqueId; }
std::string Account::getPassword() const { return password; }
double Account::getBalance() const { return balance; }