#ifndef LOGIN_H
#define LOGIN_H

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

void login(vector<shared_ptr<Account>> &accounts, shared_ptr<Account> &targetAccount, bool &loggedIn, char &option) {
    cout << "[1] Login with username" << endl;
    cout << "[2] Login with unique id" << endl;
    cout << "[m] Back to main menu" << endl;
    while (true) {
        option = _getch();

        if (option == '1' || option == '2' || option == 'm') { break; }
    }

    system("cls");
    
    string password;
    bool accountFound = false;

    // Option 1 -- Login with username
    if (option == '1') {
        cout << "[ESC] Back to login menu" << endl;
        cout << "\nUsername: ";
        string loginUsername = getUsernameInput();

        system("cls");
        if (loginUsername.empty()) { return; }

        // Check if vector is empty
        if (accounts.size() != 0) {
            // Iterate through all accounts in the vector looking for the username
            for (const auto &acc : accounts) {

                // Username matches
                if (acc->getUsername() == loginUsername) {
                    password = acc->getPassword();
                    targetAccount = acc;
                    accountFound = true;
                    break;
                }
            }
        }

        // If vector is empty / no accounts found
        if (!accountFound) {
            cout << "Username not found";
            pause(1);
            system("cls");
        }

        // Password section
        if (accountFound == true) {
            cout << "[ESC] Back to login menu" << endl;
            cout << "\nPassword: ";
            string loginPassword = encryptPassword();

            system("cls");
            if (loginPassword.empty()) { return; }

            // Correct password
            if (loginPassword == password) {
                loggedIn = true;
                cout << "Welcome " << targetAccount->getUsername() << "!"
                << " Redirecting you to account management shortly" << endl;
                
                pause(2);
                system("cls");
            }
            
            // Incorrect password
            else {
                cout << "Incorrect password" << endl;
                pause(1);
                system("cls");
            }
        }
    }

    // Option 2 -- Login with unique id
    else if (option == '2') {
        cout << "[ESC] Back to login menu" << endl;
        cout << "\nUnique id: ";
        string temp = getUniqueIdInput();

        system("cls");
        if (temp.empty()) { return; }

        int loginId = stoi(temp);

        // Check if vector is empty
        if (accounts.size() != 0) {
            // Iterate through all accounts in the vector looking for the username
            for (const auto &acc : accounts) {

                // Unique id matches
                if (acc->getUniqueId() == loginId) {
                    password = acc->getPassword();
                    targetAccount = acc;
                    accountFound = true;
                    break;
                }
            }
        }

        // If vector is empty / no accounts found
        if (!accountFound) {
            cout << "Unique id not found";
            pause(1);
            system("cls");
        }

        system("cls");

        // Password section
        if (accountFound == true) {
            cout << "[ESC] Back to login menu" << endl;
            cout << "\nPassword: ";
            string loginPassword = encryptPassword();

            system("cls");
            if (loginPassword.empty()) { return; }
            
            // Correct password
            if (loginPassword == password) {
                loggedIn = true;
                cout << "Welcome " << targetAccount->getUsername() << "!"
                << " Redirecting you to account management shortly" << endl;
                
                pause(2);
                system("cls");
            }
            
            // Incorrect password
            else {
                targetAccount = nullptr;
                cout << "Incorrect password" << endl;
                pause(1);
                system("cls");
            }
        }
    }
}

#endif