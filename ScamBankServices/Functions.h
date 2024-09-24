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
// acc - reference to Account object
// amount - amount input from user

// This function calls acc's member method "deposit" to deposit "amount"
// depposit will return true or false depending on if deposit is successfull
void depositFunction(Account &acc, double amount) {
    if (acc.deposit(amount)) {
        std::cout << "Deposit successful!" << std::endl;

        pause(2);
        system("cls");
    }
}

// Withdraw helper function
// acc - reference to Account object
// amount - amount input from user

// This function does the same as "depositFunction()" from above but with the differece that it deducts
//      from acc instead of addition
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
// password - the password user inputs and will return to function caller once user presses ENTER
// ch - variable to store and delete user input based on their actions

// This function encrypts the password user types in and replaces it with asterisks
std::string encryptPassword() {
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') {   // '\r' is Enter key
        if (ch == 27) { return ""; }    // 27 is ASCII code for ESC key , ESC key pressed, return empty string

        if (ch == '\b') {               // Handle backspace
            if (!password.empty()) {
                std::cout << "\b \b";   // Erase character from console
                password.pop_back();
            }
        }
        
        else {
            password.push_back(ch);
            std::cout << '*';           // Hide password input with '*'
        }
    }
    std::cout << std::endl;
    return password;
}

// Cancel input? function
// input - varaible to store whatever input user inputs then returns to caller once function is done
// ch - variable to store and delete user input based on their actions

// This function is basically the same as "cin >> input" but is implemented to let the user
//      cancel the prompt if they regret choosing this option
std::string getInput() {
    std::string input;
    char ch;

    while ((ch = _getch()) != '\r') {   // '\r' is Enter key
        if (ch == 27) { return ""; }    // 27 is ASCII code for ESC key , ESC key pressed, return empty string

        if (ch == '\b') {               // Handle backspace
            if (!input.empty()) {
                std::cout << "\b \b";   // Erase character from console
                input.pop_back();
            }
        }

        else {
            input.push_back(ch);
            std::cout << ch;
        }
    }

    std::cout << std::endl;
    return input;
}

// Helper function for "getValidAmount()"
// hasDecimal - boolean to store true or false if "input" has decimals

// This function is a helper function for "getValidAmount()" and checks if the inputted string is a legit digit or
//      letters or a mix of both
bool isValidNumber(const std::string& input) {
    bool hasDecimal = false;

    for (size_t i = 0; i < input.length(); ++i) {
        // Check if character is a digit or decimal point
        if (std::isdigit(input[i])) { continue; }

        // Allow only one decimal point
        if (input[i] == '.' && !hasDecimal) { hasDecimal = true; }

        // If it's the first character, allow a negative sign
        else if (input[i] == '-' && i == 0) { continue; }

        // If any other character is not valid
        else { return false; }
    }

    return !input.empty(); // Ensure input is not empty
}

// Fail check function for deposit and withdraw
// input - the string input user inputs to later be converted to "amount" if it's legal
// amount - the variable that stores users amount and returns to caller

// This function is used when a variable storing amount user inputs calls this function that fail checks
//      until user types in a legal datatype (double for this case)
double getValidAmount() {
    std::string input;
    double amount;

    // Exits this loop once user correctly enters amount
    while (true) {
        std::cout << "[ESC] Return" << std::endl;
        std::cout << " \nAmount: ";
        input = getInput();

        if (input.empty()) { return -100; }

        // Check if the input is a valid number
        if (!isValidNumber(input)) {
            std::cout << "Incorrect format" << std::endl;

            pause(2);
            system("cls");
            continue;
        }

        // Convert the valid input string to a double
        try {
            amount = std::stod(input); // std::stod converts string to double
        }
        catch (const std::exception&) {
            std::cout << "Conversion error" << std::endl;
            
            pause(2);
            system("cls");
            continue;
        }

        // Check if amount is valid (non-negative)
        if (amount <= 0) {
            std::cout << "Cannot input negative numbers or 0" << std::endl;

            pause(2);
            system("cls");
        }
        else { return amount; } // returns amount to caller
    }
}

// Check if username is duplicate
// username - reference to a username string inputted from user
// accounts - reference to a vector of shared pointers pointing to Account objects

// This function checks if username user inputs is duplicate by using the "accounts" vector declared in 'main.cpp',
//      loops through each account in the vector and gets their member method "getUsername()" to compare with "username"
bool isUsernameUnique(const std::string& username, const std::vector<std::shared_ptr<Account>> &accounts) {

    // Loops through the vector to get Account objects member method "getUsername()"
    for (const auto& acc : accounts) {
        if (acc->getUsername() == username) { // If called member method returned values is the same as username
            return false;
        }
    }
    return true;
}

// Add transaction history function
// acc - reference to Account object
// x - reference to a string that will either contain "+" or "-" depending on
//      if "depositFunction()" or "withdrawFunction()" calls
// amount - the value in question user wants to deposit or withdraw from Account object

// This function adds "acc"'s transaction history every time user deposits or withdraws by modifying "acc"'s
//      vector "transactionHistory"
// if "transactionHistory"'s size is 5, function will delete value at index 0 (indicates that its the oldest out of the 5)
//      and replace with the most recent transaction (the one user is currently doing)
void transactionHistoryFunction(Account &acc, const std::string &x, double amount) {
    std::ostringstream stream;
    stream.precision(2);                // Sets precision to 2 decimals
    stream << std::fixed << amount;     // Converts amount (which is a double) to string
    std::string str = x + stream.str(); // Concatenates x (+ or -) and the converted double

    acc.addTransactionHistory(str);     // Calls member method for acc to add this transaction history to vector "transactionHisory"
}

#endif