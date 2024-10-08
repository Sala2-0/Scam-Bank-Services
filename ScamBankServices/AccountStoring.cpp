/*
Account storage system implementation file

This file has function definitions for account storing and loading
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>

// User defined files
#include "Account.h"
#include "Admin.h"
#include "AccountStoring.h"

// Save account data to "accounts.txt"
void saveAccountsToFile(const std::vector<std::shared_ptr<Account>>& accounts) {
    std::ofstream outFile("C:/Users/idgnu/Documents/GitHub/Scam-Bank-Services/ScamBankServices/Account storage/accounts.txt");

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Loop through each account to store data
    for (const auto& account : accounts) {
        outFile << std::boolalpha; // text file displays true/false instead of 1/0
        // Write account details in the following format: username password uniqueId balance
        outFile << account->getUsername() << " "
                << account->getPassword() << " "
                << account->getUniqueId() << " "
                << account->getBalance() << " "
                << account->getAccountStatus() << " "
                << account->getUnbanDate() << "\n";

        // Get freeze reason
        outFile << account->getBanReason() << "\n";
        outFile << "CLOSE\n"; 

        // Write transaction history
        if (account->getTransactionHistory().size() != 0) {
            for (const auto& transaction : account->getTransactionHistory()) {
                outFile << transaction << "\n";
            }
        }

        outFile << "END\n";  // Mark the end of the account's transaction history
    }

    outFile.close();
}

// Load account data from "accounts.txt"
void loadAccountsFromFile(std::vector<std::shared_ptr<Account>>& accounts) {
    std::ifstream inFile("C:/Users/idgnu/Documents/GitHub/Scam-Bank-Services/ScamBankServices/Account storage/accounts.txt");

    if (!inFile) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string username, password;
        int uniqueId;
        double balance;
        std::string banned;
        std::string unbanDate;
        std::string unbanTime;

        // Read account data
        ss >> username >> password >> uniqueId >> balance >> banned >> unbanDate >> unbanTime;

        // Create a new account and set its data
        std::shared_ptr<Account> account = std::make_shared<Account>(username, password, banned);
        account->setUniqueId(uniqueId);
        account->setBalance(balance);
        account->setUnbanDate(unbanDate, unbanTime);

        // Read freeze message
        while (std::getline(inFile, line) && line != "CLOSE") {
            account->setBanReason(line); // Set freeze reason to "reasonForFreeze"
        }

        // Read transaction history
        while (std::getline(inFile, line) && line != "END") {
            account->addTransactionHistory(line);  // Add transaction to the account
        }

        // Add the account to the vector
        accounts.push_back(account);
    }

    inFile.close();
}



// ================= FOR ADMIN ACCOUNTS  =================

// Save admin account data to file
void saveAdminsToFile(std::vector<std::shared_ptr<Admin>>& admins) {
    std::ofstream outFile("C:/Users/idgnu/Documents/GitHub/Scam-Bank-Services/ScamBankServices/Account storage/admins.txt");

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Loop through each admin account to store data
    for (const auto& account : admins) {
        outFile << std::boolalpha; // text file displays true/false instead of 1/0
        // Write account details in the following format: username password uniqueId balance
        outFile << account->getUsername() << " "
                << account->getPassword() << " "
                << account->getLoginAttempts() << " "
                << account->getAccountStatus() << "\n";
    }

    outFile.close();
}

// Load admin account data from file
void loadAdminsFromFile(std::vector<std::shared_ptr<Admin>>& admins) {
    std::ifstream inFile("C:/Users/idgnu/Documents/GitHub/Scam-Bank-Services/ScamBankServices/Account storage/admins.txt");

    if (!inFile) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string username, password, attempts, locked;

        // Read account data
        ss >> username >> password >> attempts >> locked;

        // Create a new admin and set its data
        std::shared_ptr<Admin> admin = std::make_shared<Admin>(username, password, attempts, locked);

        // Add the admin account to the vector
        admins.push_back(admin);
    }

    inFile.close();
}