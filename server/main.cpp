#include "fileHandler.h"
#include "BankOperations.h"
#include <iostream>
using namespace std;

int main(){
    FileHandler fileHandler;
    BankOperations bankOperations(fileHandler);
    string username = "user1";
    
    fileHandler.createAccount(username, "password", USER);
    fileHandler.updateBalance(username, 100);
    double balance = bankOperations.checkBalance(username);
    if (balance == -1)
    {
        cout << "User not found." << endl;
        return 1;
    }
    cout << "Balance: " << balance << endl;
    return 0;

}