/*
Account management section file

This file exists to create a logged in function that gets called in 'main.cpp' instead
    of implementing the code in 'main.cpp' to make code maintenance easier
*/

#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>
#include <vector>
#include <conio.h>

// User defined files
#include "Account.h"
#include "Functions.h"
#include "AccountStoring.h"

using namespace std;

void management(shared_ptr<Account> &targetAccount, bool &loggedIn, char &option, vector<shared_ptr<Account>> &accounts) {
    if (loggedIn) {
        while (loggedIn) {
            if (targetAccount->getAccountStatus()) {
                cout << "=== Scam Bank Services ===" << endl;
                cout << "\nYour account has been frozen" << endl;
                cout << "\n= Reason =" << endl;
                cout << targetAccount->getFreezeReason() << endl;;

                cout << "\n[l] Log out" << endl;

                while (true) {
                    option = _getch();

                    if (option == 'l') {
                        cout << "Logging out..." << endl;
                        pause(2);

                        targetAccount = nullptr;
                        loggedIn = false;
                        system("cls");
                        break;
                    }
                }
            }

            // Account management menu
            cout << "=== Scam Bank Services ===" << endl;
            cout << "\nUsername: " << targetAccount->getUsername() << endl;
            cout << "Unique id: " << targetAccount->getUniqueId() << endl;
            cout << "\nBalance: " << targetAccount->getBalance() << endl;

            cout << "\n[d] Deposit" << endl;
            cout << "[w] Withdraw" << endl;
            cout << "[h] Transaction history" << endl;

            cout << "\n[l] Log out" << endl;

            // Loop until user inputs correct choices
            while (true) {
                option = _getch();

                if (option == 'd' || option == 'w' || option == 'l' || option == 'h') { break; }
            }

            system("cls");

            // Option -- Deposit
            if (option == 'd') {
                double depositAmount = getValidAmount();
                system("cls");

                // "Ignore" function if user presses ESC key so function below doesn't activate
                if (depositAmount == -100) { continue; }

                // Minimum desposit amount is 200
                else if (depositAmount < 200.0) {
                    cout << "Cannot deposit - minimum amount is 200" << endl;

                    pause(2);
                    system("cls");
                }

                else if (depositAmount > 30000.0) {
                    cout << "Cannot deposit - maximum amount is 30000" << endl;

                    pause(2);
                    system("cls");
                }

                // Depositing
                else {
                    depositFunction(*targetAccount, depositAmount);
                    transactionHistoryFunction(*targetAccount, "+", depositAmount);
                }
            }

            // Option -- Withdraw
            else if (option == 'w') {
                double withdrawAmount = getValidAmount();
                system("cls");

                // "Ignore" function if user presses ESC key so function below doesn't activate
                if (withdrawAmount == -100) { continue; }

                // Withdrawing
                else {
                    withdrawFunction(*targetAccount, withdrawAmount);
                }
            }

            // Option -- Transaction history
            else if (option == 'h') {
                targetAccount->showTransactionHistory();

                cout << "\n[ESC] Back to main menu" << endl;

                while (true) {
                    option = _getch();

                    if (option == 27) { break; }
                }
                system("cls");
            }

            // Option -- Log out
            else if (option == 'l') {
                cout << "Logging out..." << endl;
                pause(2);

                targetAccount = nullptr;
                loggedIn = false;
                system("cls");
            }

            saveAccountsToFile(accounts);
        }
    }
}

#endif