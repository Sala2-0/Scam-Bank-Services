#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>
#include <vector>
#include <conio.h>
#include <string>

// User defined files
#include "Account.h"
#include "Functions.h"

// Admin class
class Admin : public Account {
private:
    int loginAttempt {0}; // Login attempts. If max attempt is reached, will lock account
    bool locked {false}; // Lock account when max login attempt is reached
public:
    const int maxAttempts {3}; // Max login attempts accepted

    // Constructor
    Admin(const std::string& user, const std::string& pass);

    // Access all accounts data from "accounts" vector in "main.cpp"
    void viewAllAccounts(const std::vector<std::shared_ptr<Account>>& accounts) const;

    // Security functions
    void incrementLoginAttempt();
    void lockAccount();
    void resetAttempts();

    // Getters
    int getLoginAttempt();
    bool getAccountStatus(); // Locked or unlocked
};

// Login function
void adminLogin(std::vector<std::shared_ptr<Admin>>& admins, bool adminLoggedIn, std::shared_ptr<Admin> targetAdmin);

#endif