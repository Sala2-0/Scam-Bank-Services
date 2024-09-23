/*
Main file

NOTE:
-   use _getch() from conio.h library when prompting user to input option
    involving multiple choice
*/ 

#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>
#include <vector>
#include <conio.h>

// User defined files
#include "Account.h"
#include "Functions.h"
#include "Management.h"
#include "AccountCreation.h"
#include "Login.h"

using namespace std;

int main() {
    char option;
    bool loggedIn {false};

    // Vector of smart pointers containing Accounts class
    vector<shared_ptr<Account>> accounts;

    // Shared pointer will point to account when logged in for full access
    shared_ptr<Account> targetAccount = nullptr;

    do {
        // Logged in function
        management(targetAccount, loggedIn, option);

        // Main menu
        cout << "=== Welcome to Scam Bank Services! ===\n" << endl;
        cout << "[1] Log in to exising account" << endl;
        cout << "[2] Create a new account" << endl;
        cout << "[q] Quit" << endl;

        // Special input so user doesnt have to press ENTER every time
        while (true) {
            option = _getch();

            if (option == '1' || option == '2' || option == 'q') { break; }
        }

        system("cls");

        // Option 1 -- Login to existing account
        if (option == '1') {
            login(accounts, targetAccount, loggedIn, option);
        }

        // Option 2 -- Create account
        else if (option == '2') {
            accountCreation(accounts);
        }
    }
    // Quit condition
    while (option != 'q');

    return 0;
}