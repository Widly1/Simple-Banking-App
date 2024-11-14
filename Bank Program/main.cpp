#include "bank.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {
    Bank myBank("client_info.txt");

    if (argc > 1) { // Check if arguments are passed
        string command = argv[1];

        if (command == "deposit" && argc == 4) {
            long account_number = stol(argv[2]); // Get account number from args
            long double amount = stod(argv[3]);   // Get amount from args
            // Call the deposit function and show the result
            cout << "Deposit Result: $" << myBank.deposit(account_number, amount) << endl;
            return 0; // Exit after processing
        }
        else if (command == "withdraw" && argc == 4) {
            long account_number = stol(argv[2]); // Get account number from args
            long double amount = stod(argv[3]);   // Get amount from args
            // Call the withdraw function and output the result
            cout << myBank.withdraw(account_number, amount) << endl;
            return 0; // Exit after processing
        }
           else if (command == "show_clients") {
            // Display all clients
            for (int i = 0; i < myBank.get_num_clients(); ++i) {
                Client* clients = myBank.get_clients_info();  // Get the pointer to the clients array
                cout << "Client Name: " << clients[i].client_Name << endl;
                cout << "SSN: " << clients[i].ssn << endl;
                cout << "Account Number: " << clients[i].bank_account_number << endl;
                cout << "Balance: $" << fixed << setprecision(2) << clients[i].balance << endl;
                cout << "-----------------------------" << endl;
            }
            return 0; // Exit after processing
        }
        else if (command == "find_client" && argc == 3) {
            long account_number = stol(argv[2]); // Get account number from args
            myBank.find_client(account_number);  // Call find_client function
            return 0; // Exit after processing
        }
        else if (command == "add_client" && argc == 6) { // Change to 6 since there are 5 arguments plus the command
            string name = argv[2];               // Get client name from args
            string ssn = argv[3];                // Get SSN from args
            long account_number = stol(argv[4]);     // Get account number from args
            long double balance = stod(argv[5]);  // Get balance from args
            myBank.add_new_client(name, ssn, account_number, balance); // Correctly pass account number and balance
            cout << "New client added successfully!" << endl;
            return 0; // Exit after processing
        }
        else if (command == "save_changes") {
            // Save changes to the file
            myBank.saving_info("client_info.txt");
            cout << "Changes saved to file." << endl;
            return 0; // Exit after processing
        }

    }
        // If no command-line arguments, show the menu
        int choice;
        long account_number;
        long double amount;
        string name, ssn;
        Client new_client;

    do {
        cout << "\n--- Welcome to Our Banking System ---" << endl;
        cout << "       ⬇  Menu Choices ⬇     " << endl;
        cout << "1. Show all clients information" << endl;
        cout << "2. Deposit into an account" << endl;
        cout << "3. Withdraw from an account" << endl;
        cout << "4. Find a client by account number" << endl;
        cout << "5. Add a new client" << endl;
        cout << "6. Save changes" << endl;
        cout << "7. Exit" << endl;
        cout << "-------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Display all clients
                for (int i = 0; i < myBank.get_num_clients(); ++i) {
                    Client* clients = myBank.get_clients_info();  // Get the pointer to the clients array
                    cout << "Client Name: " << clients[i].client_Name << endl;
                    cout << "SSN: " << clients[i].ssn << endl;
                    cout << "Account Number: " << clients[i].bank_account_number << endl;
                    cout << "Balance: $" <<fixed << setprecision(2)<< clients[i].balance << endl;
                    cout << "-----------------------------" << endl;
                }
                break;
                
            case 2:
                // Deposit into an account
                cout << "Enter account number: ";
                cin >> account_number;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                if (amount <= 0) 
                {
                    cout << "Invalid amount. Please enter a positive value." << endl;
                } 
                else {
                    double new_balance = myBank.deposit(account_number, amount);
                if (new_balance != -1) {
                    cout << "Your updated balance is: $" << new_balance << endl;
                }
            }
            break;

            case 3:
                // Withdraw from an account
                cout << "Enter account number: ";
                cin >> account_number;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                cout << myBank.withdraw(account_number, amount) << endl;
                break;

            case 4:
                // Find a client by account number
                cout << "Enter account number: ";
                cin >> account_number;
                myBank.find_client(account_number);
                break;

            case 5:
                // Add a new client
                myBank.add_new_client(name, ssn, account_number, amount);
                cout << "New client added successfully!✅" << endl;
                break;

            case 6:
                // Save changes to the file
                myBank.saving_info("client_info.txt");
                cout << "Changes saved to file." << endl;
                break;

            case 7:
                // Exit
                cout << "Visit us again. See you later 😄 !" << endl;
                break;

            default:
                cout << "🚩Invalid choice🚩, please try again." << endl;
        }
    } while (choice != 7);  // Exit the loop when user selects 7

    return 0;
}
