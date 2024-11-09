#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "fileHandler.h"
#include "BankOperations.h"
using namespace std;


BankOperations::BankOperations(FileHandler& fileHandler) : fileHandler(fileHandler){};

bool BankOperations::deposit(const string& username, double amount)
{
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
    return fileHandler.viewAllAccounts(role);
}

string BankOperations::viewAccount(const string &username, UserRole role){
    return fileHandler.viewAccount(username, role);
};

bool BankOperations::transfer(const string &fromUser , const string &toUser, double amount){
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



