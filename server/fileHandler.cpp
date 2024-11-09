#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


enum UserRole {
    USER,
    MANAGER
};

class FileHandler
{
public:
    bool authenticateUser(const string &username, const string &password, UserRole &role);
    void updateBalance(const string &username, double balance);
    double getBalance(const string &username);
    bool createAccount(const string &username, const string &password, UserRole role);
    string deleteAccount(const string &username, UserRole role);
    vector<string> viewAllAccounts(UserRole role);
    string viewAccount(const string &username, UserRole role);
};


bool FileHandler::authenticateUser(const string &username, const string &password, UserRole &role)
{
    ifstream file("credentials.txt");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr)
        {
            if (user == username && pass == password)
            {
                role = (roleStr == "MANAGER") ? MANAGER : USER;
                return true;
            }
        }
    }
    return false;
}

void FileHandler::updateBalance(const string &username, double balance)
{
    ifstream file("credentials.txt");
    ofstream temp("temp.txt");
    string line;

    while (getline(file, line))
    {
        istringstream iss(line);
        string user, pass;
        double bal;
        if (iss >> user >> pass >> bal)
        {
            if (user == username)
            {
                temp << user << " " << pass << " " << balance << endl;
            }
            else
            {
                temp << user << " " << pass << " " << bal << endl;
            }
        }
    }
    file.close();
    temp.close();
    remove("credentials.txt");
    rename("temp.txt", "credentials.txt");
}

double FileHandler::getBalance(const string &username)
{
    ifstream file("./credentials.txt");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string user, pass;
        double balance;
        if (iss >> user >> pass >> balance)
        {
            if (user == username)
            {
                return balance;
            }
        }
    }
    return -1;
}

bool FileHandler::createAccount(const string &username, const string &password, UserRole role)
{
    ifstream file("credentials.txt");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr)
        {
            if (user == username)
            {
                file.close();
                return false;
            }
        }
    }
    file.close();
    ofstream file2("credentials.txt", ios::app);
    if (file2.is_open())
    {
        string roleStr = (role == MANAGER) ? "MANAGER" : "USER";
        file2 << username << " " << password << " " << 0.0 << " " << roleStr << endl;
        file2.close();
        return true;
    }
    else
    {
        return false;
    }
}

string FileHandler::deleteAccount(const string &username, UserRole role)
{
    if (role != MANAGER)
    {
        return "Access denied. Only managers can delete accounts.";
    }

    ifstream file("credentials.txt");
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while (getline(file, line))
    {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr)
        {
            if (user == username)
            {
                found = true;
                continue;
            }
            temp << user << " " << pass << " " << balance << " " << roleStr << endl;
        }
    }
    file.close();
    temp.close();
    if (!found)
    {
        remove("temp.txt");
        return "Account not found.";
    }
    else
    {
        remove("credentials.txt");
        rename("temp.txt", "credentials.txt");
        return "Account deleted successfully.";
    }
}

vector<string> FileHandler::viewAllAccounts(UserRole role)
{
    if (role != MANAGER)
    {
        return {"Access denied. Only managers can view all accounts."};
    }
    
    ifstream file("credentials.txt");
    string line;
    vector<string> result;
    
    while (getline(file, line))
    {
        result.push_back(line);
    }
    
    return result;
}
string FileHandler::viewAccount(const string &username, UserRole role)
{
    ifstream file("credentials.txt");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string user, pass, roleStr;
        double balance;
        if (iss >> user >> pass >> balance >> roleStr)
        {
            if (user == username)
            {
                return "Account: " + username + ", Balance: " + to_string(balance);
            }
        }
    }
    return "Account not found.";
}
