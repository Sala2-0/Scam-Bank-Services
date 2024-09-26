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

void adminManagement(shared_ptr<Admin> &targetAdmin, bool &adminLoggedIn, char &option, vector<shared_ptr<Account>> &accounts) {
    if (adminLoggedIn) {
        while (adminLoggedIn) {
            cout << "=== SCAM BANK ADMINISTRATION ===" << endl;
            cout << "= " << targetAdmin->getUsername() << " =" << endl;

            cout << "\n[1] View all accounts in system" << endl;

            cout << "\n[l] Log out" << endl;

            // Loop until user inputs correct choices
            while (true) {
                option = _getch();

                if (option == '1' ||  option == 'l') { break; }
            }

            // Option 1 -- View all accounts
            if (option == '1') {
                targetAdmin->viewAllAccounts(accounts);
            }
        }
    }
}

#endif