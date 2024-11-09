#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "fileHandler.h"
#include "BankOperations.h"
using namespace std;



BankOperations::BankOperations(FileHandler& fileHandler) : fileHandler(fileHandler){};


bool BankOperations::authenticateUser(const string& username, const string& password, UserRole& role){
    UserRole userRole;
    if (fileHandler.authenticateUser(username, password, userRole)){
        session.username = username;
        session.role = userRole;
        session.isAuthenticated = true;
        cout<<"Login Successful."<<endl;
        return true;
    }else{
        cout<<"Login Failed."<<endl;
        return false;
    }
    
}

void BankOperations::logout() {
    session = Session();  // Reset the session
    std::cout << "Logged out successfully." << std::endl;
}
bool BankOperations::deposit(const string& username, double amount)
{
    if (!session.isAuthenticated) {
        std::cout << "Please login first." << std::endl;
        return false;
    }
    if ( amount < 0)
    {
        cout << "Invalid amount. Please enter a positive value." << endl;
        return false;
    }
    double balance = fileHandler.getBalance(username);

    if (balance == -1)
    {
        cout << "User not found." << endl;
        return false;
    }else{
        balance += amount;
        fileHandler.updateBalance(username, balance);
        cout << "Deposit Successful. New Balance: "<< balance << endl;
        return true;
    }
};

bool BankOperations::withdraw(const string &username, double amount)
{
    if (!session.isAuthenticated) {
        std::cout << "Please login first." << std::endl;
        return false;
    }
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

double BankOperations::checkBalance(const string &username){
    if (!session.isAuthenticated) {
        std::cout << "Please login first." << std::endl;
        return -1;
    }
    if (fileHandler.getBalance(username) == -1)
    {
        cout << "User not found." << endl;
        return -1;
    }
    else{
        return fileHandler.getBalance(username);
    }
};

vector<string> BankOperations::viewAllAccounts(UserRole role){
    if (!session.isAuthenticated || session.role != UserRole::MANAGER ) {
        std::cout << "Access denied. Only managers can view all accounts." << std::endl;
        return {};
    }
    return fileHandler.viewAllAccounts(role);
}

string BankOperations::viewAccount(const string &username, UserRole role){
    if (!session.isAuthenticated || (session.role != UserRole::MANAGER && session.username != username)) {
        std::cout << "Access denied. Only managers or the account owner can view an account." << std::endl;
        return "";
    }
    return fileHandler.viewAccount(username, role);
};

bool BankOperations::transfer(const string &fromUser , const string &toUser, double amount){
    if (!session.isAuthenticated) {
        std::cout << "Please login first." << std::endl;
        return false;
    }
    if (amount < 0){
        cout << "Invalid amount. Please enter a positive value." << endl;
        return false;
    }
    double fromUserbalance = fileHandler.getBalance(fromUser);
    double toUserbalance = fileHandler.getBalance(toUser);
    if (fromUserbalance == -1 || toUserbalance == -1){
        cout << "User not found." << endl;
        return false;
    
    }else if ( fromUserbalance < amount){
        cout << "Insufficient funds." << endl;
        return false;

    }else{
        fromUserbalance -= amount;
        toUserbalance += amount;
        fileHandler.updateBalance(fromUser, fromUserbalance);
        fileHandler.updateBalance(toUser, toUserbalance);
        cout << "Transfer Successful. New Balance: "<< fromUserbalance << endl;

        return true;

    
};
};



