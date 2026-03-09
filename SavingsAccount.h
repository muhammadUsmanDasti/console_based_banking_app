#pragma once
#include "Account.h"

class SavingsAccount : public Account
{
private:
    double interestRate;

public:
    SavingsAccount(int id, string n, double bal, unsigned int perms, double rate = 0.05)
        : Account(id, n, bal, perms)
    {
        interestRate = rate;
    }

    string getType() { return "Savings"; }

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
        if (amount > balance)
        {
            cout << "Insufficient balance." << endl;
            return;
        }
        balance -= amount;
        transactions.push_back(-amount);
        cout << "Withdrawn " << amount << " successfully." << endl;
    }

    void applyInterest()
    {
        double interest = balance * interestRate;
        balance += interest;
        transactions.push_back(interest);
        cout << "Interest applied: " << interest << endl;
    }
};