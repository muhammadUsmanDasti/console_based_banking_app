#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define CAN_WITHDRAW  1
#define CAN_DEPOSIT   2
#define CAN_TRANSFER  4
#define VIP_ACCOUNT   8

class Account
{
protected:
    int accountId;
    string name;
    double balance;
    unsigned int permissions;
    vector<double> transactions;

public:
    Account(int id, string n, double bal, unsigned int perms)
    {
        accountId   = id;
        name        = n;
        balance     = bal;
        permissions = perms;
    }

    // pure virtual functions
    virtual void deposit(double amount)  = 0;
    virtual void withdraw(double amount) = 0;
    virtual string getType()             = 0;

    // getters
    int          getId()           { return accountId;    }
    string       getName()         { return name;         }
    double       getBalance()      { return balance;      }
    unsigned int getPermissions()  { return permissions;  }
    vector<double>& getTransactions() { return transactions; }

    void showPermissions()
    {
        cout << "Permissions : ";
        if (permissions & CAN_WITHDRAW) cout << "[Withdraw] ";
        if (permissions & CAN_DEPOSIT)  cout << "[Deposit] ";
        if (permissions & CAN_TRANSFER) cout << "[Transfer] ";
        if (permissions & VIP_ACCOUNT)  cout << "[VIP] ";
        cout << endl;
    }

    void showTransactions()
    {
        if (transactions.empty())
        {
            cout << "No transactions yet." << endl;
            return;
        }
        cout << "Transactions:" << endl;
        for (int i = 0; i < transactions.size(); i++)
        {
            if (transactions[i] > 0)
                cout << "  [" << i+1 << "] Deposit   : +" << transactions[i] << endl;
            else
                cout << "  [" << i+1 << "] Withdrawal: "  << transactions[i] << endl;
        }
    }

    void showAccount()
    {
        cout << "-----------------------------" << endl;
        cout << "Type        : " << getType()   << endl;
        cout << "Account ID  : " << accountId   << endl;
        cout << "Name        : " << name        << endl;
        cout << "Balance     : " << balance     << endl;
        showPermissions();
        showTransactions();
        cout << "-----------------------------" << endl;
    }

    virtual ~Account() {}
};