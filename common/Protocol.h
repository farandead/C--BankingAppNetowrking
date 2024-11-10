#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>
#include <experimental/optional>
using std::experimental::optional;
using std::experimental::nullopt;

enum class RequestType {
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

enum class ResponseType {
    SUCCESS,
    FAILURE
};


enum class UserRole {
    USER,
    MANAGER
};

struct Response {
    ResponseType type;                      
    std::string message;                    
    optional<double> balance = nullopt;          
    std::vector<std::string> accounts;      
    optional<std::string> account;    
};

struct Request {
    RequestType type;                       
    std::string username;                  
    optional<std::string> password;    
    optional<std::string> targetUser;  
    optional<double> amount;           
    optional<UserRole> role;           
};

#endif // PROTOCOL_H