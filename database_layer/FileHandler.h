#pragma once
#include <string>
#include <vector>
using namespace std;

// Forward declaration
class Account;

class FileHandler
{
public:
    static void saveAccounts(vector<Account*>& accounts);
    static void loadAccounts(vector<Account*>& accounts, int& nextId);
};