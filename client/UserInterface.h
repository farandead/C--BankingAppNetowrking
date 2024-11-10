#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "Protocol.h"
#include <string>
#include <vector>


struct LoginDetails {
    std::string username;
    std::string password;
};
class UserInterface {
public:
    int showMainMenu(UserRole role);

    LoginDetails getLoginDetails();

    bool createAccount(const std::string &username, const  std::string &password, UserRole role);

    double getTransactionAmount(const std::string &transactionType);

    // Displays messages or information to the user
    void displayMessage(const std::string &message);

    // Displays the user's balance
    void displayBalance(double balance);

    // Prompts the user for transfer details
    std::pair<std::string, double> getTransferDetails(); // Can replace pair similarly if needed

    // Displays a list of all accounts (for manager use)
    void displayAllAccounts(const std::vector<std::string> &accounts);

    // Displays a specific account's details (for manager use)
    void displayAccountDetails(const std::string &accountDetails);

    // Prompt for username input for account viewing
    std::string getUsernameForAccountView();

private:
    int getIntInput(const std::string &prompt);
    double getDoubleInput(const std::string &prompt);
};
#endif // USERINTERFACE_H