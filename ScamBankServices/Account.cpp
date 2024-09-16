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

std::string Account::getUsername() const { return username; }
int Account::getUniqueId() const { return uniqueId; }
std::string Account::getPassword() const { return password; }