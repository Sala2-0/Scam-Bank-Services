// Account creation file

#ifndef ACCOUNT_CREATION_H
#define ACCOUNT_CREATION_H

#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>
#include <vector>
#include <conio.h>

// User defined files
#include "Account.h"
#include "Functions.h"

using namespace std;

void accountCreation(vector<shared_ptr<Account>> &accounts) {
    string username;

    // Check if username is duplicate
    while (true) {
        cout << "[ESC] Back to login menu" << endl;
        cout << "\nCreate a username: ";
        username = getUsernameInput();
        
        if (!isUsernameUnique(username, accounts)) {
            cout << "Username already exists" << endl;

            pause(2);
            system("cls");
            continue;
        }
        break;
    }

    system("cls");
    if (username.empty()) { return; }

    cout << "[ESC] Back to login menu" << endl;
    cout << "\nCreate a password: ";
    string password = getPasswordInput();

    system("cls");
    if (password.empty()) { return; }

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
    accounts.push_back(make_unique<Account>(username, password));

    pause(2);
    system("cls");
}

#endif