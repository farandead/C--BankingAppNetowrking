#ifndef BANKOPERATIONS_H
#define BANKOPERATIONS_H

#include <string>
#include <vector>
#include "FileHandler.h"
#include "Protocol.h"
struct Session {
    std::string username;
    UserRole role;
    bool isAuthenticated = false;
};
class BankOperations {
private:
    FileHandler &fileHandler;
    Session session; 

public:
    BankOperations(FileHandler &fileHandler);
    bool createAccount(const std::string &username, const std::string &password, UserRole role);
  
    bool deposit(const std::string &username, double amount);
    bool withdraw(const std::string &username, double amount);
    double checkBalance(const std::string &username);
    bool transfer(const std::string &fromUser, const std::string &toUser, double amount);
    std::vector<std::string> viewAllAccounts(UserRole role);
    std::string viewAccount(const std::string &username, UserRole role);
};

#endif // BANKOPERATIONS_H