#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <Protocol.h>

class FileHandler {
public:
    bool authenticateUser(const std::string &username, const std::string &password, UserRole &role);
    void updateBalance(const std::string &username, double balance);
    double getBalance(const std::string &username);
    bool createAccount(const std::string &username, const std::string &password, UserRole role);
    std::string deleteAccount(const std::string &username, UserRole role);
    std::vector<std::string> viewAllAccounts(UserRole role);
    std::string viewAccount(const std::string &username, UserRole role);
    bool sendLoginRequest(const std::string &username, const std::string &password);
};

#endif // FILEHANDLER_H