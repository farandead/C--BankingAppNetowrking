#ifndef BANKOPERATIONS_H
#define BANKOPERATIONS_H

#include <string>
#include <vector>
#include "FileHandler.h"

class BankOperations {
private:
    FileHandler &fileHandler;

public:
    BankOperations(FileHandler &fileHandler);
    bool deposit(const std::string &username, double amount);
    bool withdraw(const std::string &username, double amount);
    double checkBalance(const std::string &username);
    bool transfer(const std::string &fromUser, const std::string &toUser, double amount);
    std::vector<std::string> viewAllAccounts(UserRole role);
    std::string viewAccount(const std::string &username, UserRole role);
};

#endif // BANKOPERATIONS_H