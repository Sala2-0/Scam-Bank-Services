/*
Account storage system file

This file has function declarations for account storing and loading in "AccountStoring.cpp"
*/

#ifndef ACCOUNT_STORING_H
#define ACCOUNT_STORING_H

#include <vector>
#include <memory>

// User defined files
#include "Account.h"
#include "Admin.h"

// Function declarations
void saveAccountsToFile(const std::vector<std::shared_ptr<Account>>& accounts);
void loadAccountsFromFile(std::vector<std::shared_ptr<Account>>& accounts);
void saveAdminsToFile(std::vector<std::shared_ptr<Admin>>& admins);
void loadAdminsFromFile(std::vector<std::shared_ptr<Admin>>& admins);

#endif