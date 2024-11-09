#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <string>
#include <vector>
enum class requestType {
    LOGIN,
    DEPOSIT,
    WITHDRAW,
    TRANSFER,
    CHECK_BALANCE,
    VIEW_ACCOUNT,
    VIEW_ALL_ACCOUNTS,
    CREATE_ACCOUNT,
    DELETE_ACCOUNT,
    LOGOUT
};

enum class responseType {
    SUCCESS,
    FAILURE
};

enum class UserRole {
    USER,
    MANAGER
};

struct Response
{
    responseType type;
    std::string message;
    double balance;
    std::vector<std::string> accounts;
    std::string account;
};





#endif // PROTOCOL_H