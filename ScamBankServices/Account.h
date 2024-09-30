/*
Account class file

This file is the declaration of "Account" class
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include <string>

class Account {
private:
    int uniqueId;
    double balance;
    bool accountFrozen;

    std::vector<std::string> transactionHistory;

protected:
    std::string username;
    std::string password;

    std::string reasonForFreeze;

public:
    Account();
    Account(const std::string user, const std::string pass, const std::string accountStatus = "false", const std::string reason = "");
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

    const std::vector<std::string>& getTransactionHistory() const;

    bool getAccountStatus() const;
    std::string getFreezeReason() const;

    // Setters

    // For account storing functions
    void setUniqueId(int id);
    void setBalance(double amount);
    void setFreezeReason(const std::string reason);

    // For mainstream functions
    void freezeAccount(const std::string &reason);
};

#endif