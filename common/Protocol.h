#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>
#include <experimental/optional>
using std::experimental::optional;


// Define types for request and response
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

// Define user roles
enum class UserRole {
    USER,
    MANAGER
};

// Structure for a response from the server
struct Response {
    ResponseType type;                      // Success or failure of the operation
    std::string message;                    // Message detailing response
    optional<double> balance;          // Account balance if applicable
    std::vector<std::string> accounts;      // List of all accounts for managers
    optional<std::string> account;     // Single account info (like username)
};

// Structure for a request from the client
struct Request {
    RequestType type;                       // Type of the request
    std::string username;                   // Username of the client
    optional<std::string> password;    // Password for authentication
    optional<std::string> targetUser;  // Target user for transfers or account operations
    optional<double> amount;           // Amount for deposit, withdraw, transfer
    optional<UserRole> role;           // Role of the user (e.g., USER or MANAGER)
};

#endif // PROTOCOL_H