#ifndef ADMIN_PAGE_H
#define ADMIN_PAGE_H

#include <memory>
#include <vector>
#include <conio.h>

// User defined files
#include "Account.h"
#include "Functions.h"
#include "AccountStoring.h"
#include "Admin.h"

using namespace std;

// Admin management function
// Args listed in order:
//      - &targetAdmin (shared ptr of Admin class. Should be pointing to user's logged in account after login)
//      - &adminLoggedIn (boolean to check wether logged in or not to continue or return from function)
//      - &accounts (accounts vector from main.cpp to be able to modify the different accounts)

// This function serves as a menu for administrators and contains sensitive admin features which only admin accounts have access to
void adminManagement(shared_ptr<Admin> &targetAdmin, bool &adminLoggedIn, char &option, vector<shared_ptr<Account>> &accounts) {
    if (adminLoggedIn) {
        while (adminLoggedIn) {
            cout << "=== SCAM BANK ADMINISTRATION ===" << endl;
            cout << "= " << targetAdmin->getUsername() << " =" << endl;

            cout << "\n[1] View all accounts in system" << endl;
            cout << "[2] Freeze account" << endl;

            cout << "\n[l] Log out" << endl;

            // Loop until user inputs correct choices
            while (true) {
                option = _getch();

                if (option == '1' || option == '2' || option == 'l') { break; }
            }

            system("cls");

            // Option 1 -- View all accounts
            if (option == '1') {
                targetAdmin->viewAllAccounts(accounts);

                while (true) {
                    option = _getch();

                    if (option == 27) { break; }
                }
                system("cls");
            }

            // Option 2 -- Freeze accounts
            else if (option == '2') {
                shared_ptr<Account> target = nullptr;
                bool accountFound = false;

                cout << "Username: ";
                string user = getInput();

                system("cls");
                if (user.empty()) { continue; }

                // Check if vector is empty
                if (accounts.size() != 0) {
                    // Iterate through all accounts in the vector looking for the username
                    for (const auto &acc : accounts) {

                        // Username matches
                        if (acc->getUsername() == user) {
                            target = acc;
                            accountFound = true;
                            break;
                        }
                    }
                }

                // If vector is empty / no accounts found
                if (!accountFound) {
                    cout << "No users with username " << user << " found";
                    pause(1);
                    system("cls");
                }

                // Freeze message
                if (accountFound) {
                    cout << "== Freeze message ==" << endl;
                    string message = getInput();
                    target->banAccount(message);

                    cout << "User " << target->getUsername() << " has been frozen" << endl;
                    saveAccountsToFile(accounts);
                    
                    pause(1);
                    system("cls");
                }
            }

            else if (option == 'l') {
                cout << "Logging out..." << endl;
                adminLoggedIn = false;
                targetAdmin = nullptr;

                pause(2);
                system("cls");
            }
        }
    }
}

#endif