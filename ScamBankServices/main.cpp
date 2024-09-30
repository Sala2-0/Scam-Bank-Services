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
#include <string>

// User defined files
#include "Account.h"
#include "Functions.h"
#include "Management.h"
#include "AccountCreation.h"
#include "Login.h"
#include "AccountStoring.h"
#include "Admin.h"
#include "AdminPage.h"

using namespace std;

int main() {
    char option;
    bool loggedIn {false};
    bool adminLoggedIn {false};

    // Vector of smart pointers containing Accounts class
    vector<shared_ptr<Account>> accounts;

    // Vector of smart pointers containing admin accounts
    vector<shared_ptr<Admin>> admins;

    // Load accounts from file when the program starts
    loadAccountsFromFile(accounts);
    loadAdminsFromFile(admins);

    // Shared pointer will point to account when logged in for full access
    shared_ptr<Account> targetAccount = nullptr;
    shared_ptr<Admin> targetAdmin = nullptr;

    // admins.push_back(make_shared<Admin>("Yurizono_Seia", "Void"));
    // saveAdminsToFile(admins);

    pause(2);
    system("cls"); // Clean console after loading data from "accounts.txt"

    do {
        // Logged in functions
        management(targetAccount, loggedIn, option, accounts);
        adminManagement(targetAdmin, adminLoggedIn, option, accounts);

        // Main menu
        cout << "=== Welcome to Scam Bank Services! ===\n" << endl;
        cout << "[1] Log in to exising account" << endl;
        cout << "[2] Create a new account" << endl;
        cout << "[3] Administrator" << endl;

        cout << "\n[q] Quit" << endl;

        // Special input so user doesnt have to press ENTER every time
        while (true) {
            option = _getch();

            if (option == '1' || option == '2' || option == '3' || option == 'q') { break; }
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

        // Option 3 -- Admin
        else if (option == '3') {
            adminLogin(admins, adminLoggedIn, targetAdmin);
        }
    }
    // Quit condition
    while (option != 'q');

    return 0;
}