#include "Bank.h"
#include <iostream>
using namespace std;

void showMenu()
{
    cout << "\n=============================" << endl;
    cout << "   BANKING TRANSACTION SYSTEM" << endl;
    cout << "=============================" << endl;
    cout << "1. Create Account"             << endl;
    cout << "2. Deposit"                    << endl;
    cout << "3. Withdraw"                   << endl;
    cout << "4. Transfer"                   << endl;
    cout << "5. Show Account"               << endl;
    cout << "6. Save to File"               << endl;
    cout << "7. Load from File"             << endl;
    cout << "8. Monthly Summary"            << endl;
    cout << "9. Admin Mode"                 << endl;
    cout << "0. Exit"                       << endl;
    cout << "Enter choice: ";
}

int main()
{
    Bank bank;
    int choice;

    // AUTO LOAD when program starts
    cout << "Loading data..." << endl;
    bank.loadFromFile();

    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
            case 1: bank.createAccount();  break;
            case 2: bank.depositMenu();    break;
            case 3: bank.withdrawMenu();   break;
            case 4: bank.transferMenu();   break;
            case 5: bank.showAccount();    break;
            case 6: bank.saveToFile();     break;
            case 7: bank.loadFromFile();   break;
            case 8: bank.monthlySummary(); break;
            case 9: bank.adminMode();      break;
            case 0:
                // AUTO SAVE when program exits
                cout << "Saving data..." << endl;
                bank.saveToFile();
                cout << "Goodbye!" << endl;
                break;
            default: cout << "Invalid option." << endl;
        }

    } while (choice != 0);

    return 0;
}