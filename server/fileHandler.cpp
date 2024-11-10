#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Protocol.h"
using namespace std;

class FileHandler {
public:
    bool authenticateUser(const string &username, const string &password, UserRole &role);
    void updateBalance(const string &username, double balance);
    double getBalance(const string &username);
    bool createAccount(const string &username, const string &password, UserRole role);
    string deleteAccount(const string &username, UserRole role);
    vector<string> viewAllAccounts(UserRole role);
    string viewAccount(const string &username, UserRole role);
};

bool FileHandler::authenticateUser(const string &username, const string &password, UserRole &role) {
    ifstream file("credentials.txt");
    if (!file.is_open()) {
        cerr << "Failed to open credentials.txt for reading." << endl;
        return false;
    }

    string line;
    cout<<"Username: "<<username<<endl;
    while (getline(file, line)) {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr) {
            if (user == username && pass == password) {
                role = (roleStr == "MANAGER") ? UserRole::MANAGER : UserRole::USER;
                return true;
            }
        }
    }
    cout<<"User not found"<<endl;
    return false;
}

void FileHandler::updateBalance(const string &username, double balance) {
    ifstream file("credentials.txt");
    ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        cerr << "Error opening file for updateBalance." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string user, pass, roleStr;
        double bal;
        if (iss >> user >> pass >> bal >> roleStr) {
            if (user == username) {
                temp << user << " " << pass << " " << balance << " " << roleStr << endl;
            } else {
                temp << user << " " << pass << " " << bal << " " << roleStr << endl;
            }
        }
    }
    file.close();
    temp.close();
    remove("credentials.txt");
    rename("temp.txt", "credentials.txt");
}

double FileHandler::getBalance(const string &username) {
    ifstream file("credentials.txt");
    if (!file.is_open()) {
        cerr << "Failed to open credentials.txt for reading balance." << endl;
        return -1;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr) {
            if (user == username) {
                return balance;
            }
        }
    }
    return -1;
}

bool FileHandler::createAccount(const string &username, const string &password, UserRole role) {
    ifstream file("credentials.txt");
    if (!file.is_open()) {
        cerr << "Failed to open credentials.txt for reading." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr) {
            if (user == username) {
                file.close();
                return false;
            }
        }
    }
    file.close();

    ofstream file2("credentials.txt", ios::app);
    if (!file2.is_open()) {
        cerr << "Failed to open credentials.txt for appending." << endl;
        return false;
    }

    string roleStr = (role == UserRole::MANAGER) ? "MANAGER" : "USER";
    file2 << username << " " << password << " " << 0.0 << " " << roleStr << endl;
    return true;
}

string FileHandler::deleteAccount(const string &username, UserRole role) {
    if (role != UserRole::MANAGER) {
        return "Access denied. Only managers can delete accounts.";
    }

    ifstream file("credentials.txt");
    ofstream temp("temp.txt");

    if (!file.is_open() || !temp.is_open()) {
        cerr << "Error opening files for deleteAccount." << endl;
        return "Error: Unable to access account data.";
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr) {
            if (user == username) {
                found = true;
                continue;
            }
            temp << user << " " << pass << " " << balance << " " << roleStr << endl;
        }
    }
    file.close();
    temp.close();

    if (!found) {
        remove("temp.txt");
        return "Account not found.";
    } else {
        remove("credentials.txt");
        rename("temp.txt", "credentials.txt");
        return "Account deleted successfully.";
    }
}

vector<string> FileHandler::viewAllAccounts(UserRole role) {
    if (role != UserRole::MANAGER) {
        return {"Access denied. Only managers can view all accounts."};
    }

    ifstream file("credentials.txt");
    if (!file.is_open()) {
        cerr << "Failed to open credentials.txt for viewing accounts." << endl;
        return {"Error: Unable to access account data."};
    }

    vector<string> result;
    string line;
    while (getline(file, line)) {
        result.push_back(line);
    }
    return result;
}

string FileHandler::viewAccount(const string &username, UserRole role) {
    ifstream file("credentials.txt");
    if (!file.is_open()) {
        cerr << "Failed to open credentials.txt for viewing account." << endl;
        return "Error: Unable to access account data.";
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr) {
            if (user == username) {
                return "Account: " + username + ", Balance: " + to_string(balance);
            }
        }
    }
    return "Account not found.";
}
