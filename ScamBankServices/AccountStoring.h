/*
Account storage system file

This file has functions for account storing and loading
*/

#ifndef ACCOUNT_STORING_H
#define ACCOUNT_STORING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>

// User defined files
#include "Account.h"

// Save account data to "accounts.txt"
void saveAccountsToFile(const std::vector<std::shared_ptr<Account>>& accounts) {
    std::ofstream outFile("accounts.txt");

    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    for (const auto& account : accounts) {
        // Write account details in the following format: username password uniqueId balance
        outFile << account->getUsername() << " "
                << account->getPassword() << " "
                << account->getUniqueId() << " "
                << account->getBalance() << "\n";

        // Write transaction history
        for (const auto& transaction : account->getTransactionHistory()) {
            outFile << transaction << "\n";
        }

        outFile << "END\n";  // Mark the end of the account's transaction history
    }

    outFile.close();
}

// Load account data from "accounts.txt"
void loadAccountsFromFile(std::vector<std::shared_ptr<Account>>& accounts) {
    std::ifstream inFile("accounts.txt");

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

        // Read account data
        ss >> username >> password >> uniqueId >> balance;

        // Create a new account and set its data
        std::shared_ptr<Account> account = std::make_shared<Account>(username, password);
        account->setUniqueId(uniqueId);  // Need to add setter for UniqueID in Account class
        account->setBalance(balance);    // Need to add setter for Balance in Account class

        // Read transaction history
        while (std::getline(inFile, line) && line != "END") {
            account->addTransactionHistory(line);  // Add transaction to the account
        }

        // Add the account to the vector
        accounts.push_back(account);
    }

    inFile.close();
}

#endif