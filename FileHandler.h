#pragma once
#include <string>
#include <vector>
using namespace std;

class Account;

class FileHandler
{
public:
    static void saveAccounts(vector<Account*>& accounts, int nextId);
    static void loadAccounts(vector<Account*>& accounts, int& nextId);
};