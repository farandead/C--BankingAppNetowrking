#include "UserInterface.h"
#include<iostream>
#include<limits>
using namespace std;
int UserInterface::showMainMenu(UserRole role){
    cout << "=== Banking System Menu ===\n";

    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Check Balance\n";
    cout << "4. Transfer Funds\n";
    cout << "5. View All Accounts\n";
    cout << "6. View Account\n";
    cout << "7. Exit\n";
    cout << "8. Create Account\n";
    return getIntInput("Enter your choice: ");
}

LoginDetails UserInterface::getLoginDetails(){
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    return {username, password};
}

double UserInterface::getTransactionAmount(const string &transactionType){
    return getDoubleInput("Enter the amount to " + transactionType + ": ");
}

void UserInterface::displayMessage(const string &message){
    cout << message << endl;
}

void UserInterface::displayBalance(double balance){
    cout << "Current balance: " << balance << endl;
}

bool UserInterface::createAccount(const string &username, const string &password, UserRole role){
    return "Account created successfully.";
}


std::pair<string,double> UserInterface::getTransferDetails(){
    string username;
    double amount;
    cout << "Enter the username to transfer to: ";
    cin >> username;
    amount = getDoubleInput("Enter the amount to transfer: ");
    return {username, amount};
}

void UserInterface::displayAllAccounts(const vector<string> &accounts){
    cout << "=== All Accounts ===\n";
    for (const auto &account : accounts)
    {
        cout << account << endl;
    }
}

void UserInterface::displayAccountDetails(const string &accountDetails){
    cout << "=== Account Details ===\n";
    cout << accountDetails << endl;
}

std::string UserInterface::getUsernameForAccountView() {
    std::string username;
    std::cout << "Enter username to view account details: ";
    std::cin >> username;
    return username;
}

int UserInterface::getIntInput(const string &prompt){
    int input;
    cout << prompt;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

double UserInterface::getDoubleInput(const string &prompt){
    double input;
    cout << prompt;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

