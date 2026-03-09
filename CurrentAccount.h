#pragma once
#include "Account.h"

class CurrentAccount : public Account
{
private:
    double overdraftLimit;

public:
    CurrentAccount(int id, string n, double bal, unsigned int perms, double overdraft = 1000)
        : Account(id, n, bal, perms)
    {
        overdraftLimit = overdraft;
    }

    string getType() { return "Current"; }

    void deposit(double amount)
    {
        if (!(permissions & CAN_DEPOSIT))
        {
            cout << "Permission denied: Cannot deposit." << endl;
            return;
        }
        if (amount <= 0)
        {
            cout << "Invalid amount." << endl;
            return;
        }
        balance += amount;
        transactions.push_back(amount);
        cout << "Deposited " << amount << " successfully." << endl;
    }

    void withdraw(double amount)
    {
        if (!(permissions & CAN_WITHDRAW))
        {
            cout << "Permission denied: Cannot withdraw." << endl;
            return;
        }
        if (amount <= 0)
        {
            cout << "Invalid amount." << endl;
            return;
        }
        if (amount > balance + overdraftLimit)
        {
            cout << "Exceeds overdraft limit. Max withdrawal: "
                 << balance + overdraftLimit << endl;
            return;
        }
        balance -= amount;
        transactions.push_back(-amount);
        cout << "Withdrawn " << amount << " successfully." << endl;
        if (balance < 0)
            cout << "Warning: Account is in overdraft. Balance: " << balance << endl;
    }
};