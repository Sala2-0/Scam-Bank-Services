/*
Account class file

This file is the declaration of "Account" class
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account {
    private:
    std::string username;
    std::string password;
    int uniqueId;
    double balance;

    bool locked;

    std::vector<std::string> transactionHistory;

    public:
    Account(const std::string user, const std::string pass);
    ~Account();

    // Deposit
    bool deposit(double amount);

    // Withdraw
    bool withdraw(double amount);
    
    // Add transaction history
    void addTransactionHistory(const std::string &history);

    // Show transaction history
    void showTransactionHistory() const;
    
    // Getters
    std::string getUsername() const;
    int getUniqueId() const;
    std::string getPassword() const;
    double getBalance() const;
};

#endif