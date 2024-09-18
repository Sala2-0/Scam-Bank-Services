// Helper functions file

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <sstream>

#include "Account.h"

// Pause console for certain seconds
void pause(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// Deposit helper function
void depositFunction(Account &acc, double amount) {
    if (acc.deposit(amount)) {
        std::cout << "Deposit successful!" << std::endl;

        pause(2);
        system("cls");
    }
}

// Withdraw helper function
void withdrawFunction(Account &acc, double amount) {
    if (acc.withdraw(amount)) {
        std::cout << "Withdraw successful!" << std::endl;

        pause(2);
        system("cls");
    }

    else {
        std::cout << "Cannot withdraw - insufficient balance" << std::endl;
        pause(2);
        system("cls");
    }
}

// Encrypt password with asterisks
std::string encryptPassword() {
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') {  // '\r' is Enter key
        if (ch == 27) { return ""; } // 27 is ASCII code for ESC key , ESC key pressed, return empty string

        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                std::cout << "\b \b"; // Erase character from console
                password.pop_back();
            }
        }
        
        else {
            password.push_back(ch);
            std::cout << '*';  // Hide password input with '*'
        }
    }
    std::cout << std::endl;
    return password;
}

// Fail check function for deposit and withdraw
double getValidAmount(const std::string &prompt) {
    double amount;
    while (true) {
        std::cout << prompt;
        std::cin >> amount;
        if (std::cin.fail()) {
            std::cout << "Incorrect format" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pause(1);
            system("cls");
        }
        
        else {
            break;
        }
    }
    return amount;
}

// Check if username is duplicate
bool isUsernameUnique(const std::string& username, const std::vector<std::shared_ptr<Account>> &accounts) {
    for (const auto& acc : accounts) {
        if (acc->getUsername() == username) {
            return false;
        }
    }
    return true;
}

// Add transaction history function
void transactionHistoryFunction(Account &acc, const std::string &x, double amount) {
    std::ostringstream stream;
    stream.precision(2);
    stream << std::fixed << amount;
    std::string str = x + stream.str();

    acc.addTransactionHistory(str);
}

// Cancel username input? function
std::string getUsernameInput() {
    std::string username;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' is Enter key
        if (ch == 27) { return ""; } // 27 is ASCII code for ESC key , ESC key pressed, return empty string

        if (ch == '\b') { // Handle backspace
            if (!username.empty()) {
                std::cout << "\b \b"; // Erase character from console
                username.pop_back();
            }
        }

        else {
            username.push_back(ch);
            std::cout << ch;
        }
    }

    std::cout << std::endl;
    return username;
}

// Cancel password input? function
std::string getPasswordInput() {
    std::string password;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' is Enter key
        if (ch == 27) { return ""; } // 27 is ASCII code for ESC key , ESC key pressed, return empty string

        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                std::cout << "\b \b"; // Erase character from console
                password.pop_back();
            }
        }

        else {
            password.push_back(ch);
            std::cout << ch;
        }
    }

    std::cout << std::endl;
    return password;
}

// Cancel unique id input? function
std::string getUniqueIdInput() {
    std::string uniqueId;
    char ch;

    while ((ch = _getch()) != '\r') { // '\r' is Enter key
        if (ch == 27) { return ""; } // ESC key pressed, return empty string
        
        if (ch == '\b') { // Handle backspace
            if (!uniqueId.empty()) {
                std::cout << "\b \b"; // Erase character from console
                uniqueId.pop_back();
            }
        }
        
        else if (isdigit(ch)) {  // Only allow numeric input
            uniqueId.push_back(ch);
            std::cout << ch;
        }
    }

    std::cout << std::endl;
    return uniqueId;
}

#endif