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
#include "Helpers.h"
#include "Management.h"

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
                cout << "Username: ";
                string loginUsername; cin >> loginUsername;

                system("cls");

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

                system("cls");

                // Password section
                if (accountFound == true) {
                    cout << "Password: ";
                    string loginPassword = getPasswordInput();

                    system("cls");

                    // Correct password
                    if (loginPassword == password) {
                        loggedIn = true;
                        cout << "Welcome " << targetAccount->getUsername() << "!"
                        << " Redirecting you to account management shortly" << endl;
                        
                        pause(3);
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
                cout << "Unique id: ";
                int loginId; cin >> loginId;

                system("cls");

                // If user inputs everything other than integers
                if (cin.fail()) {
                    cout << "Incorrect format" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    pause(1);
                    system("cls");
                }

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
                    cout << "Password: ";
                    string loginPassword = getPasswordInput();

                    system("cls");

                    // Correct password
                    if (loginPassword == password) {
                        loggedIn = true;
                        cout << "Welcome " << targetAccount->getUsername() << "!"
                        << " Redirecting you to account management shortly" << endl;
                        
                        pause(3);
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
        }

        // Option 2 -- Create account
        else if (option == '2') {
            string username;

            // Fail check username
            while (true) {
                cout << "Create a username: ";
                cin >> username;

                if (!isUsernameUnique(username, accounts)) {
                    cout << "Username already exists" << endl;

                    pause(2);
                    system("cls");
                    continue;
                }
                break;
            }

            cout << "\nCreate a password: ";
            string password;

            // Fail check password
            while (true) {
                cin >> password;
                if (cin.fail()) {
                    cout << "Incorrect format" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    pause(1);
                    system("cls");
                    continue;
                }
                break;
            }

            system("cls");

            string confirmPassword;
            do {
                cout << "\nConfirm password: ";
                confirmPassword = getPasswordInput();

                if (confirmPassword != password) {
                    cout << "Password does not match: ";
                    pause(1);
                    system("cls");
                }
            }
            while (confirmPassword != password);

            system("cls");

            // Constructor when account created
            accounts.push_back(make_unique<Account>(username, password));

            pause(3);
            system("cls");
        }
    }
    // Quit condition
    while (option != 'q');

    return 0;
}