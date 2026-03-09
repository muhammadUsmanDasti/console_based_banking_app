#pragma once
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "Transaction.h"
#include <vector>

class Bank
{
private:
    vector<Account*> accounts;
    int nextId;
    double monthlyTotals[12];

public:
    Bank();
    ~Bank();

    void createAccount();
    void depositMenu();
    void withdrawMenu();
    void transferMenu();
    void showAccount();
    void showAllAccounts();
    void monthlySummary();
    void adminMode();
    void saveToFile();
    void loadFromFile();

    // needed by FileHandler
    vector<Account*>& getAccounts() { return accounts; }
    int& getNextId()                { return nextId;   }
};