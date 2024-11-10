#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "fileHandler.h"
#include "BankOperations.h"

using namespace std;

BankOperations::BankOperations(FileHandler& fileHandler) : fileHandler(fileHandler) {}

bool BankOperations::createAccount(const string& username, const string& password, UserRole role) {
    if (fileHandler.createAccount(username, password, role)) {
        cout << "Account created successfully." << endl;
        return true;
    } else {
        cout << "Account creation failed." << endl;
        return false;
    }
}

bool BankOperations::deposit(const string& username, double amount) {
    if (amount < 0) {
        cout << "Invalid amount. Please enter a positive value." << endl;
        return false;
    }
    double balance = fileHandler.getBalance(username);

    if (balance == -1) {
        cout << "User not found." << endl;
        return false;
    } else {
        balance += amount;
        fileHandler.updateBalance(username, balance);
        cout << "Deposit Successful. New Balance: " << balance << endl;
        return true;
    }
}

bool BankOperations::withdraw(const string &username, double amount) {
    if (amount < 0) {
        cout << "Invalid amount. Please enter a positive value." << endl;
        return false;
    }

    double balance = fileHandler.getBalance(username);
    if (balance == -1) {
        cout << "User not found." << endl;
        return false;
    } else if (balance < amount) {
        cout << "Insufficient funds." << endl;
        return false;
    } else {
        balance -= amount;
        fileHandler.updateBalance(username, balance);
        cout << "Withdrawal Successful. New Balance: " << balance << endl;
        return true;
    }
}

double BankOperations::checkBalance(const string &username) {
    double balance = fileHandler.getBalance(username);
    if (balance == -1) {
        cout << "User not found." << endl;
        return -1;
    } else {
        return balance;
    }
}

vector<string> BankOperations::viewAllAccounts(UserRole role) {
    if (role != UserRole::MANAGER) {
        cout << "Access denied. Only managers can view all accounts." << endl;
        return {};
    }
    return fileHandler.viewAllAccounts(role);
}

string BankOperations::viewAccount(const string &username, UserRole role) {
    return fileHandler.viewAccount(username, role);
}

bool BankOperations::transfer(const string &fromUser, const string &toUser, double amount) {
    if (amount < 0) {
        cout << "Invalid amount. Please enter a positive value." << endl;
        return false;
    }

    double fromUserBalance = fileHandler.getBalance(fromUser);
    double toUserBalance = fileHandler.getBalance(toUser);

    if (fromUserBalance == -1 || toUserBalance == -1) {
        cout << "User not found." << endl;
        return false;
    } else if (fromUserBalance < amount) {
        cout << "Insufficient funds." << endl;
        return false;
    } else {
        fromUserBalance -= amount;
        toUserBalance += amount;
        fileHandler.updateBalance(fromUser, fromUserBalance);
        fileHandler.updateBalance(toUser, toUserBalance);
        cout << "Transfer Successful. New Balance for " << fromUser << ": " << fromUserBalance << endl;
        return true;
    }
}
