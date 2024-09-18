// Account management section file (Logged in)

#include <iostream>
#include <limits>
#include <cstdlib>
#include <memory>
#include <vector>
#include <conio.h>

// User defined files
#include "Account.h"
#include "Helpers.h"

using namespace std;

void management(shared_ptr<Account> targetAccount, bool &loggedIn, char &option) {
    if (loggedIn) {
        while (loggedIn) {

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
                double depositAmount = getValidAmount("Amount: ");
                    
                // Minimum desposit amount is 200
                if (depositAmount < 200.0) {
                    cout << "Cannot deposit - minimum amount is 200" << endl;

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
                double withdrawAmount = getValidAmount("Amount: ");
                    
                // Withdrawing
                withdrawFunction(*targetAccount, withdrawAmount);
                transactionHistoryFunction(*targetAccount, "-", withdrawAmount);
            }

            // Option -- Transaction history
            else if (option == 'h') {
                targetAccount->showTransactionHistory();

                cout << "\n[q] Back to main menu" << endl;

                while (true) {
                    option = _getch();

                    if (option == 'q') { break; }
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
        }
    }
}