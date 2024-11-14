#include "bank.h" // Include the header file
#include <iostream>
#include <fstream>  // To read from files
#include <sstream>  // To process input from the file

using namespace std;

// Constructor: Load client information from a file
Bank::Bank(string file_name) {
    ifstream file(file_name); // using file to read from the client_info.txt file

    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // now we count how many clients are in the file
    string line;
    num_clients = 0;
    
    while (getline(file, line)) {
        num_clients++;
    }

    // Allocate memory for the clients array
    clients = new Client[num_clients];

    // reset file pointer and reload client information
    file.clear(); // we clear once we reach the end of the file
    file.seekg(0); // Rewind to the head of the file after counting to read the content
    
    int index = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        // now we get data from the stringstream object with the line content from the file
        ss >> clients[index].client_Name >> clients[index].ssn
           >> clients[index].bank_account_number>> clients[index].balance;
        index++;
    }

    file.close(); 
}

// Destructor: Free the dynamically allocated memory
Bank::~Bank() {
    delete[] clients;  // Deallocate the dynamic array
    clients = nullptr; // Avoid dangling pointers
}

// Deep copy constructor: creating a copy of the bank object
Bank::Bank(const Bank& other) {
    num_clients = other.num_clients;    // Copy the number of clients
    clients = new Client[num_clients];  // Allocate new memory for clients

    // to copy each client information from the file
    for (int i = 0; i < num_clients; i++) {
        clients[i] = other.clients[i];
    }
}

// Load client info from client_info.txt file 
// (like to update or refresh the data after changes)
void Bank::load_clients_info(string file_name) {
    ifstream file(file_name);
    
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // First, count how many clients are in the file
    string line;
    num_clients = 0;
    
    while (getline(file, line)) {
        num_clients++;
    }

    // Deallocate previous memory if needed (for space)
    delete[] clients;

    // Allocate new memory for clients array
    clients = new Client[num_clients];

    // reset file pointer and reload client information
    file.clear(); // we clear once we reach the end of the file
    file.seekg(0); // Rewind to the head of the file after counting to read the content
    
    int index = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string fullName;
        // Read full name 
        getline(ss, fullName); 

        // Read other fields
        ss >> clients[index].ssn;
        ss.ignore(); // Ignore the comma after SSN
        ss >> clients[index].bank_account_number;
        ss.ignore(); // Ignore the comma after account number
        ss >> clients[index].balance;

        // Assign the full name to the client structure
        clients[index].client_Name = fullName;
        index++;

    }

    file.close(); 
}

// Return a pointer to the array of clients 
Client* Bank::get_clients_info() {
    return clients;
}

// Deposit: Update the balance for a specific account and return the new balance
double Bank::deposit(long account_number, long double amount) {
    for (int i = 0; i < num_clients; i++) {
        if (clients[i].bank_account_number == account_number) {
            clients[i].balance += amount;
            return clients[i].balance;
        }
    }
    cerr << "Account not found!" << endl;
    return -1; // Return -1 if the account is not found
}

// Withdraw: Update the balance for a specific account, make sure there's enough balance, and return a message
string Bank::withdraw(long account_number, long double amount) {
    for (int i = 0; i < num_clients; i++) {
        if (clients[i].bank_account_number == account_number) {
            if (clients[i].balance >= amount) {
                clients[i].balance -= amount;
                return "Withdrawal successful. New balance: " + to_string(clients[i].balance);
            } else {
                return "Insufficient funds.";
            }
        }
    }
    return "Account not found!";
}

// Save client info to the file
void Bank::saving_info(string file_name) {
    ofstream file(file_name);
    
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (int i = 0; i < num_clients; i++) {
        file << clients[i].client_Name << " " << clients[i].ssn << " "
             << clients[i].bank_account_number << " " << clients[i].balance << endl;
    }

    file.close();  
}

// Finding a client by account number and showing their information
void Bank::find_client(long account_number) {
    for (int i = 0; i < num_clients; i++) {
        if (clients[i].bank_account_number == account_number) {
            cout << "Client Name: " << clients[i].client_Name << endl;
            cout << "SSN: " << clients[i].ssn << endl;
            cout << "Account Number: " << clients[i].bank_account_number << endl;
            cout << "Balance: $" << clients[i].balance << endl;
            return;
        }
    }
    cout << "Client not found." << endl;
}

// Adding a new client to the array
void Bank::add_new_client(string name,string ssn,long account_number, long double amount) {
    Client new_client;
 // Set new client values
    new_client.client_Name = name;
    new_client.ssn = ssn;
    new_client.bank_account_number = account_number;
    new_client.balance = amount;

    // Create a new array with one extra space for the new client
    Client* new_clients = new Client[num_clients + 1];

    // Copy the old clients
    for (int i = 0; i < num_clients; i++) {
        new_clients[i] = clients[i];
    }

    // New client
    new_clients[num_clients] = new_client;

    // Deallocate the old clients array and update the pointer
    delete[] clients;
    clients = new_clients;
    num_clients++;

    // Save the updated info to the file
    saving_info("client_info.txt");
}


