/*
Account implementation file

This file is the implementation of "Account" class member methods
*/

#include <iostream>
#include <string>
#include <random>
#include <ctime>

// User defined files
#include "Account.h"

// Random unique id generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> id(000000, 999999);

// Constructor
// Constructs an "Account" object that takes username (user) and password (pass) as arguments
// Initializes userame and password with arguments, balance to default which is 10000.0
// Unique id initialized by random id generator above with "id(gen)""
// Outputs account information after construction
Account::Account(const std::string user, const std::string pass, const std::string accountStatus, const std::string reason)
: uniqueId{id(gen)}, balance{10000.0}, accountFrozen{false}, username{user}, password{pass}, reasonForFreeze{""} {
    if (accountStatus == "true") { freezeAccount(reason); }
}

// Destructor
// Destroys an account object when it goes out of scope
Account::~Account() {}

// Deposit
// Simple deposit method
// Takes "amount" as argument and adds to balance
// Then returns "true" to indicare successful deposit
bool Account::deposit(double amount) {
    balance += amount;
    return true;
}

// Withdraw
// Simple withdraw method
// Works same way as Deposit method
// Difference is cannot withdraw if balance after withdrawal is negative and returns false
bool Account::withdraw(double amount) {
    if (balance - amount >= 0) {
        balance -= amount;
        return true;
    }

    return false;
}

// Add transaction history
// Method for adding transaction history to "transactionHistory" vector after deposit or withdrawaö
// Adds current time of deposit or withdrawal to history
// If "transactionHistory"'s size is bigger than 5, method will delete index 0 (oldest recent transaction)
void Account::addTransactionHistory(const std::string &history) {

    time_t now = time(&now);                    // Fetch current time on computer
    std::string timestamp = ctime(&now);        // Convert to human readable form
    timestamp.pop_back();                       // Remove newline character at the end

    std::string transaction = history + " - " + timestamp; // The final string to be pushed back to "transactionHistory"

    if (transactionHistory.size() == 5) {
        transactionHistory.erase(transactionHistory.begin());   // Remove oldest recent transaction if bigger than 5
    }

    transactionHistory.push_back(transaction);
}

// Show transaction history
// Method for displaying recent transaction histories
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

const std::vector<std::string>& Account::getTransactionHistory() const { return transactionHistory; }

bool Account::getAccountStatus() const { return accountFrozen; }
std::string Account::getFreezeReason() const { return reasonForFreeze; }

// Setters
void Account::setUniqueId(int id) { uniqueId = id; }
void Account::setBalance(double amount) { balance = amount; }
void Account::freezeAccount(const std::string &reason) {
    accountFrozen = true;
    reasonForFreeze = reason;
}