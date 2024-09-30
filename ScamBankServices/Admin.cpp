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
#include "Admin.h"
#include "AccountStoring.h"

// Constructor
Admin::Admin(const std::string& user, const std::string& pass, const std::string& attempts, const std::string& locked)
: Account{user, pass}, loginAttempts{0}, locked{false}, maxAttempts{3} {
        setBalance(0.0);
        setUniqueId(0);

        if (locked == "true") { lockAccount(); }
        loginAttempts = std::stoi(attempts);
            
}

// Access all accounts data from "accounts" vector in "main.cpp"
void Admin::viewAllAccounts(const std::vector<std::shared_ptr<Account>>& accounts) const {
    std::cout << "Accounts:" << std:: endl;
    for (const auto& account : accounts) {
        std::cout << "User: " << account->getUsername()
                << " | Unique id: " << account->getUniqueId()
                        << " | Balance: " << account->getBalance() << std::endl;
    }
}

// Security functions
void Admin::incrementLoginAttempt() { loginAttempts++; }
void Admin::lockAccount() { locked = true; }
void Admin::resetAttempts() { loginAttempts = 0; }

// Getters
int Admin::getLoginAttempts() { return loginAttempts; }
bool Admin::getAccountStatus() { return locked; }; // Locked or unlocked

// ===== NORMAL FUNCTIONS =====

// Login function
void adminLogin(std::vector<std::shared_ptr<Admin>> &admins, bool &adminLoggedIn, std::shared_ptr<Admin> &targetAdmin) {
    bool accountFound {false};
    std::string password;
    
    std::cout << "[ESC] Back" << std::endl;
    std::cout << "\nUsername: ";
    std::string username = getInput();

    system("cls");
    if (username.empty()) { return; }

    if (admins.size() != 0) {
        // Iterate through all accounts in the vector looking for the username
        for (const auto &admin : admins) {

            // Username matches
            if (admin->getUsername() == username) {
                password = admin->getPassword();
                targetAdmin = admin;
                accountFound = true;
                break;
            }
        }
    }

    // If vector is empty / no accounts found
    if (!accountFound) {
        std::cout << "Username not found";
        pause(1);
        system("cls");
    }

    // ======= PASSWORD SECTION =======
    if (accountFound == true) {
        std::cout << "[ESC] Back to login menu" << std::endl;
        std::cout << "\nPassword: ";
        std::string loginPassword = encryptPassword();

        system("cls");
        if (loginPassword.empty()) { return; }
        
        // Admin account is locked
        if (targetAdmin->getAccountStatus()) {
            std::cout << "Account locked! No access allowed" << std::endl;
            targetAdmin = nullptr;

            pause(2);
            system("cls");
        }

        // Correct password
        else if (loginPassword == password) {
            adminLoggedIn = true;
            std::cout << "Logged in as " << targetAdmin->getUsername() << std::endl;
            targetAdmin->resetAttempts();
            saveAdminsToFile(admins);

            pause(2);
            system("cls");
        }
        
        // Incorrect password
        else {
            std::cout << "Incorrect password" << std::endl;
            targetAdmin->incrementLoginAttempt();
            saveAdminsToFile(admins);

            pause(1);
            system("cls");

            // Too many login attempts detected
            if (targetAdmin->getLoginAttempts() > targetAdmin->maxAttempts) {
                std::cout << "Anomaly detected - Too many login attempts" << std::endl;
                std::cout << "Locking account..." << std::endl;
                targetAdmin->lockAccount();
                targetAdmin = nullptr;
                saveAdminsToFile(admins);

                pause(2);
                system("cls");
            }

            targetAdmin = nullptr;
        }
    }
}