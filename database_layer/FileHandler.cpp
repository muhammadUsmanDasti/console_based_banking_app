#include "FileHandler.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include <fstream>
#include <iostream>

void FileHandler::saveAccounts(vector<Account*>& accounts)
{
    ofstream file("accounts.txt", ios::trunc);
    if (!file)
    {
        cout << "Error: Could not open file for saving." << endl;
        return;
    }

    for (int i = 0; i < accounts.size(); i++)
    {
        file << "ACCOUNT " << accounts[i]->getType() << endl;
        file << accounts[i]->getId() << " "
             << accounts[i]->getName() << " "
             << accounts[i]->getBalance() << " "
             << accounts[i]->getPermissions() << endl;
        file << "TRANSACTIONS" << endl;

        vector<double>& txns = accounts[i]->getTransactions();
        for (int j = 0; j < txns.size(); j++)
            file << txns[j] << endl;

        file << "END" << endl;
    }

    file.close();
    cout << "All accounts saved successfully." << endl;
}

void FileHandler::loadAccounts(vector<Account*>& accounts, int& nextId)
{
    // free existing memory first
    for (int i = 0; i < accounts.size(); i++)
        delete accounts[i];
    accounts.clear();

    ifstream file("accounts.txt");
    if (!file)
    {
        cout << "No save file found." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.find("ACCOUNT") == string::npos)
            continue;

        string type = "";
        if (line.find("Savings") != string::npos) type = "Savings";
        if (line.find("Current") != string::npos) type = "Current";

        int id;
        string name;
        double balance;
        unsigned int perms;

        file >> id >> name >> balance >> perms;
        getline(file, line); // consume leftover newline

        Account* acc = NULL;
        if (type == "Savings")
            acc = new SavingsAccount(id, name, balance, perms);
        else if (type == "Current")
            acc = new CurrentAccount(id, name, balance, perms);
        else
            continue;

        getline(file, line); // read "TRANSACTIONS" line

        while (getline(file, line) && line != "END")
        {
            if (line.empty()) continue;
            double t = stod(line);
            acc->getTransactions().push_back(t);
        }

        accounts.push_back(acc);
        if (id >= nextId) nextId = id + 1;
    }

    file.close();
    cout << "Accounts loaded successfully." << endl;
}