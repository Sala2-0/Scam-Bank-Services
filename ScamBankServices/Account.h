// Account header file

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
    private:
    std::string username;
    std::string password;
    int uniqueId;
    double balance;

    bool locked;

    public:
    Account(const std::string user, const std::string pass);

    std::string getUsername() const;
    int getUniqueId() const;
    std::string getPassword() const;
};

#endif