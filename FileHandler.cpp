#include "FileHandler.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include <fstream>
#include <iostream>
using namespace std;

void FileHandler::saveAccounts(vector<Account*>& accounts, int nextId)
{
    ofstream file("accounts.txt", ios::trunc);
    if (!file)
    {
        cout << "Error: Could not open file for saving." << endl;
        return;
    }

    // save nextId at the very top of file
    file << "NEXTID " << nextId << endl;

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
    for (int i = 0; i < accounts.size(); i++)
        delete accounts[i];
    accounts.clear();

    ifstream file("accounts.txt");
    if (!file)
    {
        cout << "No save file found. Starting fresh." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        // read nextId from top of file
        if (line.find("NEXTID") != string::npos)
        {
            nextId = stoi(line.substr(7));
            continue;
        }

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
        getline(file, line);

        Account* acc = NULL;
        if (type == "Savings")
            acc = new SavingsAccount(id, name, balance, perms);
        else if (type == "Current")
            acc = new CurrentAccount(id, name, balance, perms);
        else
            continue;

        getline(file, line); // read "TRANSACTIONS"

        while (getline(file, line) && line != "END")
        {
            if (line.empty()) continue;
            double t = stod(line);
            acc->getTransactions().push_back(t);
        }

        accounts.push_back(acc);
    }

    file.close();
    cout << "Accounts loaded successfully." << endl;
}