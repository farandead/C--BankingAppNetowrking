#include "ClientSocket.h"
#include "UserInterface.h"
#include "Protocol.h" // Assuming this includes enums and commands for communication
#include <iostream>
#include <sstream>
using namespace std;
int main() {
    ClientSocket clientSocket;
    UserInterface userInterface;
    UserRole role = UserRole::USER;
    string serverIP = "127.0.0.1"; 
    int serverPort = 8080;            

    // Connect to the server
    if (!clientSocket.connectToServer(serverIP, serverPort)) {
        cerr << "Failed to connect to the server." << endl;
        return -1;
    }
    cout << "Connected to server." << endl;

    while (true) {
        int choice = userInterface.showMainMenu(role);
        
        switch (choice) {
            case 1: { 
                string username;
                cout << "Enter username for deposit: ";
                cin >> username;
                double amount = userInterface.getTransactionAmount("deposit");
                string depositRequest = "DEPOSIT " + username + " " + to_string(amount);
                clientSocket.sendMessage(depositRequest);
                
                string response = clientSocket.receiveMessage();
                userInterface.displayMessage(response);
                break;
            }
            case 2: { 
                string username;
                cout << "Enter username for withdrawal: ";
                cin >> username;
                double amount = userInterface.getTransactionAmount("withdraw");
                string withdrawRequest = "WITHDRAW " + username + " " + to_string(amount);
                clientSocket.sendMessage(withdrawRequest);
                
                string response = clientSocket.receiveMessage();
                userInterface.displayMessage(response);
                break;
            }
            case 3: { 
                string username;
                cout << "Enter username to check balance: ";
                cin >> username;
                clientSocket.sendMessage("CHECK_BALANCE " + username);
                string response = clientSocket.receiveMessage();
                userInterface.displayBalance(stod(response));
                break;
            }
            case 4: {
                string fromUser;
                cout << "Enter your username: ";
                cin >> fromUser;
                auto transferDetails = userInterface.getTransferDetails();
                string transferRequest = "TRANSFER " + fromUser + " " + transferDetails.first + " " + to_string(transferDetails.second);
                clientSocket.sendMessage(transferRequest);
                
                string response = clientSocket.receiveMessage();
                userInterface.displayMessage(response);
                break;
            }
            case 5: { 
                if (role == UserRole::MANAGER) {
                    clientSocket.sendMessage("VIEW_ALL_ACCOUNTS");
                    string response = clientSocket.receiveMessage();
                    // Process response to display all accounts as needed
                } else {
                    cout << "Unauthorized access." << endl;
                }
                break;
            }
            case 6: { 
                if (role == UserRole::MANAGER) {
                    string username = userInterface.getUsernameForAccountView();
                    string request = "VIEW_ACCOUNT " + username;
                    clientSocket.sendMessage(request);
                    
                    string response = clientSocket.receiveMessage();
                    userInterface.displayAccountDetails(response);
                } else {
                    cout << "Unauthorized access." << endl;
                }
                break;
            }

            case 7: { 
                cout << "Exiting the program..." << endl;
                clientSocket.disconnect();
                return 0;
            }
            case 8 : {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                string request = "CREATE_ACCOUNT " + username + " " + password;
                clientSocket.sendMessage(request);
                
                string response = clientSocket.receiveMessage();
                userInterface.displayMessage(response);
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
