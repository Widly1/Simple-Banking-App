#ifndef Bank_h
#define Bank_h 

#include <string> // to use strings in this code
                  // i.e.: client's name and ssn 

using namespace std;

// the client structure
struct Client{
    string client_Name;         //this will store the client's name
    string ssn;                 // for the SSN 
    long bank_account_number;   // for bank acct num
    long double balance;        // for the balance on the account
};

// the class for bank
class Bank{

private:
    int num_clients;    // the num of clients
    Client* clients;    // creating a dynamic array of clients

public:

    //our constructor
    Bank(string file_name);
    // this is gonna load client's info from a file during construction

    // our destructor
    ~Bank(); // this is 2 delete whatever is hanging around that's no longer needed 
            // to avoid any memory leaks


    // the deep copy constructor, this is gonna be used to help make sure that each object 
    Bank(const Bank& other); // has its own seperate copy of the data


    // the getter for num_clients
    int get_num_clients() const { 
        return num_clients; 
    }


    // now we have our public methods
    void load_clients_info (string file_name);                   //load client info from a file 
    Client* get_clients_info();                                  //will give you access to the array of clients from bank class
    double deposit(long account_number, long double amount);     //our function to deposit

    string withdraw(long account_number, long double amount);    //our function to withdraw
    //it's a string because we want to return a message once the process is complete or not

    void saving_info(string file_name);                         // save clients info to file
    void find_client(long account_number);                      // find and return a client's info
    void add_new_client(string name, string ssn, long bank_account_number,long double amount);                                    // to add a new client
};
#endif 