#include "Bank.h"
#include "FileHandler.h"
#include <iostream>
#include <string>
using namespace std;

Bank::Bank()
{
    nextId = 1001;
    for (int i = 0; i < 12; i++)
        monthlyTotals[i] = 0;
}
void Bank::saveToFile()
{
    FileHandler::saveAccounts(accounts, nextId);
}
Bank::~Bank()
{
    for (int i = 0; i < accounts.size(); i++)
        delete accounts[i];
    accounts.clear();
}

Account* findById(vector<Account*>& accounts, int id)
{
    for (int i = 0; i < accounts.size(); i++)
        if (accounts[i]->getId() == id)
            return accounts[i];
    return NULL;
}

void Bank::createAccount()
{
    int choice, permChoice;
    string name;
    double initialBalance;
    unsigned int perms;

    cout << "\n--- Create Account ---" << endl;
    cout << "1. Savings Account" << endl;
    cout << "2. Current Account" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter initial balance: ";
    cin >> initialBalance;

    cout << "\nSet Permissions:" << endl;
    cout << "1. Basic (Withdraw + Deposit)" << endl;
    cout << "2. Full  (Withdraw + Deposit + Transfer)" << endl;
    cout << "3. VIP   (All permissions)" << endl;
    cout << "Enter choice: ";
    cin >> permChoice;

    if (permChoice == 1)
        perms = CAN_WITHDRAW | CAN_DEPOSIT;
    else if (permChoice == 2)
        perms = CAN_WITHDRAW | CAN_DEPOSIT | CAN_TRANSFER;
    else
        perms = CAN_WITHDRAW | CAN_DEPOSIT | CAN_TRANSFER | VIP_ACCOUNT;

    Account* acc = NULL;

    if (choice == 1)
        acc = new SavingsAccount(nextId, name, initialBalance, perms);
    else if (choice == 2)
        acc = new CurrentAccount(nextId, name, initialBalance, perms);
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }

    accounts.push_back(acc);
    cout << "Account created! Your Account ID: " << nextId << endl;
    nextId++;
}

void Bank::depositMenu()
{
    int id;
    double amount;

    cout << "\nEnter Account ID: ";
    cin >> id;

    Account* acc = findById(accounts, id);
    if (acc == NULL) { cout << "Account not found." << endl; return; }

    cout << "Enter deposit amount: ";
    cin >> amount;

    acc->deposit(amount);

    // show transaction encoding
    unsigned int encoded = encodeTransaction(1, (unsigned int)amount);
    unsigned int type, decoded;
    decodeTransaction(encoded, type, decoded);
    cout << "[Encoded: " << encoded << " | Type: " << type << ", Amount: " << decoded << "]" << endl;
}

void Bank::withdrawMenu()
{
    int id;
    double amount;

    cout << "\nEnter Account ID: ";
    cin >> id;

    Account* acc = findById(accounts, id);
    if (acc == NULL) { cout << "Account not found." << endl; return; }

    cout << "Enter withdrawal amount: ";
    cin >> amount;

    acc->withdraw(amount);

    unsigned int encoded = encodeTransaction(2, (unsigned int)amount);
    unsigned int type, decoded;
    decodeTransaction(encoded, type, decoded);
    cout << "[Encoded: " << encoded << " | Type: " << type << ", Amount: " << decoded << "]" << endl;
}

void Bank::transferMenu()
{
    int fromId, toId;
    double amount;

    cout << "\nEnter FROM Account ID: ";
    cin >> fromId;
    cout << "Enter TO Account ID: ";
    cin >> toId;
    cout << "Enter transfer amount: ";
    cin >> amount;

    Account* from = findById(accounts, fromId);
    Account* to   = findById(accounts, toId);

    if (from == NULL || to == NULL)
    {
        cout << "One or both accounts not found." << endl;
        return;
    }

    if (!(from->getPermissions() & CAN_TRANSFER))
    {
        cout << "Permission denied: Account cannot transfer." << endl;
        return;
    }

    if (amount > from->getBalance())
    {
        cout << "Insufficient balance for transfer." << endl;
        return;
    }

    from->withdraw(amount);
    to->deposit(amount);
    cout << "Transfer of " << amount << " completed." << endl;
}

void Bank::showAccount()
{
    int id;
    cout << "\nEnter Account ID: ";
    cin >> id;

    Account* acc = findById(accounts, id);
    if (acc == NULL) { cout << "Account not found." << endl; return; }

    acc->showAccount();
}

void Bank::showAllAccounts()
{
    if (accounts.empty()) { cout << "No accounts found." << endl; return; }
    for (int i = 0; i < accounts.size(); i++)
        accounts[i]->showAccount();
}

void Bank::monthlySummary()
{
    for (int i = 0; i < 12; i++)
        monthlyTotals[i] = 0;

    int month = 0;
    for (int i = 0; i < accounts.size(); i++)
    {
        vector<double>& txns = accounts[i]->getTransactions();
        for (int j = 0; j < txns.size(); j++)
        {
            monthlyTotals[month % 12] += txns[j];
            month++;
        }
    }

    string months[] = {"Jan","Feb","Mar","Apr","May","Jun",
                       "Jul","Aug","Sep","Oct","Nov","Dec"};
    cout << "\n--- Monthly Summary ---" << endl;
    for (int i = 0; i < 12; i++)
        cout << months[i] << ": " << monthlyTotals[i] << endl;
}

void Bank::adminMode()
{
    string pass;
    cout << "Enter admin password: ";
    cin >> pass;

    if (pass != "admin123")
    {
        cout << "Wrong password." << endl;
        return;
    }

    cout << "\n[ADMIN MODE ACTIVATED]" << endl;
    showAllAccounts();
    monthlySummary();
}


void Bank::loadFromFile()
{
    FileHandler::loadAccounts(accounts, nextId);
}