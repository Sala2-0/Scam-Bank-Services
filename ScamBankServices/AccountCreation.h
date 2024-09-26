/*
Account creation file

This file exists to create an account creation function that gets called in 'main.cpp' instead
    of implementing the code in 'main.cpp' to make code maintenance easier
*/

#ifndef ACCOUNT_CREATION_H
#define ACCOUNT_CREATION_H

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
#include "AccountStoring.h"

using namespace std;

// accounts - reference to "accounts" vector from 'main.cpp'
// Referenced to be able to modify the vector once account is created
void accountCreation(vector<shared_ptr<Account>> &accounts) {
    string username;

    // Loop that promps user to enter a username
    // If prompted username is duplicate whithin "accounts", loop will continue
    while (true) {
        cout << "[ESC] Back to login menu" << endl;
        cout << "\nCreate a username: ";
        username = getInput();
        
        if (!isUsernameUnique(username, accounts)) {
            cout << "Username already exists" << endl;

            pause(2);
            system("cls");
            continue;
        }
        break;
    }

    system("cls");
    if (username.empty()) { return; } // If ESC is pressed

    // Password creation
    cout << "[ESC] Back to login menu" << endl;
    cout << "\nCreate a password: ";
    string password = getInput();

    system("cls");
    if (password.empty()) { return; }


    // Confirm password
    string confirmPassword;
    do {
        cout << "[ESC] Back to login menu" << endl;
        cout << "\nConfirm password: ";
        confirmPassword = encryptPassword();

        system("cls");
        if (confirmPassword.empty()) { break; }

        if (confirmPassword != password) {
            cout << "Password does not match";
            pause(1);
            system("cls");
        }
    }
    while (confirmPassword != password);

    if (confirmPassword.empty()) { return; }

    // Constructor when account created
    accounts.push_back(make_shared<Account>(username, password));
    saveAccountsToFile(accounts);

    pause(2);
    system("cls");
}

#endif