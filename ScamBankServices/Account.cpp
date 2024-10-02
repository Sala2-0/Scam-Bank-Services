/*
Account implementation file

This file is the implementation of "Account" class member methods
*/

#define _CRT_SECURE_NO_WARNINGS // Avoid error for "localtime()"

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

// User defined files
#include "Account.h"
#include "Functions.h"

// Random unique id generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> id(000000, 999999);

// Constructor
// Constructs an "Account" object that takes username (user) and password (pass) as arguments
// Initializes userame and password with arguments, balance to default which is 10000.0
// Unique id initialized by random id generator above with "id(gen)""
// Outputs account information after construction
Account::Account(const std::string user, const std::string pass, const std::string accountStatus, const std::string reason,
        const std::string unbanDate)
: uniqueId{id(gen)}, balance{10000.0}, banned{false}, username{user}, password{pass}, reasonForBan{""}, dateOfUnban{unbanDate} {
    if (accountStatus == "true") { banAccount(reason); }
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
    // Fetch current time using <chrono>
    auto now = std::chrono::system_clock::now();

    // Convert to time_t for formatting
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert to tm structure for local time
    std::tm* localTime = localtime(&currentTime);

    // Create a string stream to format the time
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");  // Format the timestamp as YYYY-MM-DD HH:MM:SS

    // Combine the transaction history with the formatted timestamp
    std::string transaction = history + " - " + oss.str(); // The final string to be pushed back to "transactionHistory"

    // Ensure transactionHistory size is limited to 5 entries
    if (transactionHistory.size() == 5) {
        transactionHistory.erase(transactionHistory.begin()); // Remove the oldest transaction
    }

    // Add the new transaction with the timestamp to the history
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

// Administration getters
// Administration methods are functions and methods used by admin accounts for administrative
//      stuff like banning, resetting balances etc
bool Account::getAccountStatus() const { return banned; }
std::string Account::getBanReason() const { return reasonForBan; }
std::string Account::getUnbanDate() const { return dateOfUnban; }

// --- Setters ---
// For account storing functions
void Account::setUniqueId(int id) { uniqueId = id; }
void Account::setBalance(double amount) { balance = amount; }
void Account::setBanReason(const std::string reason) { reasonForBan = reason; }
void Account::setUnbanDate(const std::string date, const std::string time) {
    dateOfUnban = date +  " " + time;
}

// For mainstream functions (mostly administration involved)
void Account::banAccount(const std::string &reason, int days) {
    if (days == 0) {
        banned = true;
        reasonForBan = reason;
    }
    
    else {
        banned = true;
        reasonForBan = reason;

        dateOfUnban = convertTime(days);
    }
}

// Unban account function
void Account::unbanAccount() {
    banned = false;
    reasonForBan = "";
    dateOfUnban = "none";
}

// Check if ban is still active function
bool Account::isBanActive() {
    return compareWithCurrentDateTime(dateOfUnban);
}