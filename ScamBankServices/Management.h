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

// Management menu function
// Args listed in order:
//      - &targetAccount (Reference to shared ptr. Should be pointing to user's logged in account if user logged in)
//      - &loggedIn (boolean to check if user is logged in or not to continue or return from function)
//      - &accounts (referenced for account storing functions to be able to save updated data)

// This function is the main menu for logged in users and currently contains menthods like deposit and withdraw 
//      which will change user's accounts's accordingly
void management(shared_ptr<Account> &targetAccount, bool &loggedIn, char &option, vector<shared_ptr<Account>> &accounts) {
    if (loggedIn) {
        while (loggedIn) {
            // If date is equal or past the unban date
            if (targetAccount->isBanActive()) { // If true, unbans account
                targetAccount->unbanAccount();
            }

            // Else, display the ban menu
            else {
                cout << "=== Scam Bank Services ===" << endl;
                cout << "\nYour account has been banned" << endl;
                cout << "\n= Reason =" << endl;
                cout << targetAccount->getBanReason() << endl;

                cout << "\nYou will be unbanned on " << targetAccount->getUnbanDate() << endl;

                cout << "\n[l] Log out" << endl;

                while (true) {
                    option = _getch();

                    if (option == 'l') {
                        system("cls");

                        cout << "Logging out..." << endl;
                        targetAccount = nullptr;
                        loggedIn = false;
                        
                        pause(2);
                        system("cls");
                        return;
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
            cout << "[s] Send money" << endl;
            cout << "[h] Transaction history" << endl;

            cout << "\n[l] Log out" << endl;

            // Loop until user inputs correct choices
            while (true) {
                option = _getch();

                if (option == 'd' || option == 'w' || option == 'l' || option == 's' || option == 'h') { break; }
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
                    
                    cout << (depositFunction(*targetAccount, depositAmount) ? "Deposit successful!" : "Deposit failed - error") << endl;

                    pause(2);
                    system("cls");
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
                    cout << (withdrawFunction(*targetAccount, withdrawAmount) ? "Withdraw successful!" : "Withdraw failed - insufficient balance") << endl;

                    pause(2);
                    system("cls");
                }
            }

            // Option -- Send money
            else if (option == 's') {
                shared_ptr<Account> receiver = nullptr;

                cout << "[ESC] Back to main menu" << endl;
                
                cout << "\nUser to send money: ";
                string username = getInput();

                system("cls");

                if (findAccount(username, accounts, receiver)) {
                    double amount = getValidAmount();

                    system("cls");
                    if (amount == -100) { continue; }

                    targetAccount->sendMoney(amount, *receiver);

                    cout << "Sent " << amount << " to " << receiver->getUsername() << endl;

                    pause(2);
                    system("cls");
                }
                
                else {
                    cout << "Account not found" << endl;

                    pause(2);
                    system("cls");
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