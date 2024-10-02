/*
Functions file

This file has function declarations for common functions in "Functions.cpp"
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include <memory>
#include <ctime>

#include "Account.h"

void pause(int seconds);
void depositFunction(Account &acc, double amount);
void withdrawFunction(Account &acc, double amount);
std::string encryptPassword();
std::string getInput();
bool isValidNumber(const std::string& input);
double getValidAmount();
int getValidAmountInt();
bool isUsernameUnique(const std::string& username, const std::vector<std::shared_ptr<Account>> &accounts);
void transactionHistoryFunction(Account &acc, const std::string &x, double amount);
std::string convertTime(int days);
bool convertStringToTime(const std::string& dateTimeStr, std::tm& timeStruct);
bool compareWithCurrentDateTime(const std::string& inputDateTime);

#endif