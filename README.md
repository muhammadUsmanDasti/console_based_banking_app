# 🏦 Banking Transaction System

![C++](https://img.shields.io/badge/Language-C++-blue.svg)
![OOP](https://img.shields.io/badge/Paradigm-OOP-green.svg)
![Architecture](https://img.shields.io/badge/Architecture-3--Layer-orange.svg)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

A secure, console-based **Banking Transaction System** built in **C++** using Object-Oriented Programming, 3-Layered Architecture, File Handling, Bitwise Operators, Dynamic Memory, and  Vectors.

> 📚 Built as a semester project for CS — 3rd Semester  
> 🎓 Covers: OOP, Pointers, Vectors, Arrays, File Handling, Bitwise Operators

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Architecture](#-3-layered-architecture)
- [Concepts Covered](#-concepts-covered)
- [Getting Started](#-getting-started)
- [How to Compile](#-how-to-compile)
- [How to Run](#-how-to-run)
- [Usage](#-usage)
- [File Format](#-file-format)
- [Bitwise Permission System](#-bitwise-permission-system)
- [Transaction Compression](#-transaction-compression)
- [Screenshots](#-screenshots)
- [Author](#-author)

---

## 🔍 Overview

This is a console-based banking system that simulates real-world banking operations such as account creation, deposits, withdrawals, fund transfers, and persistent data storage. The system is designed with a clean **3-layered architecture** separating the presentation, business logic, and data access layers.

---

## ✨ Features

| Feature | Description |
|---|---|
| 🆕 Create Account | Create Savings or Current accounts with custom permissions |
| 💰 Deposit | Deposit money with permission validation |
| 💸 Withdraw | Withdraw money with balance and permission checks |
| 🔄 Transfer | Transfer funds between accounts |
| 📄 View Account | View account details and full transaction history |
| 💾 Auto Save | Data is automatically saved on exit |
| 📂 Auto Load | Data is automatically loaded on startup |
| 📊 Monthly Summary | View net balance changes across 12 months |
| 🔐 Admin Mode | Password-protected admin panel |
| 📈 Interest | Savings accounts support interest calculation |
| ⚠️ Overdraft | Current accounts support overdraft limit |
| 🔒 Permissions | Bitwise permission flags per account |
| 🗜️ Compression | Transaction type + amount encoded in a single unsigned int |

---

## 📁 Project Structure

```
BankingApp/
│
├── main.cpp                ← Layer 1: Presentation Layer
│
├── Account.h               ← Abstract Base Class
├── SavingsAccount.h        ← Derived Class (Savings)
├── CurrentAccount.h        ← Derived Class (Current)
├── Transaction.h           ← Bit Manipulation (encode/decode)
│
├── Bank.h                  ← Bank Class Declaration
├── Bank.cpp                ← Bank Class Implementation (Business Logic)
│
├── FileHandler.h           ← FileHandler Declaration
├── FileHandler.cpp         ← FileHandler Implementation (Data Access)
│
└── accounts.txt            ← Auto-generated data file (created on first save)
```

---

## 🏗️ 3-Layered Architecture

```
┌──────────────────────────────────────────────┐
│           LAYER 1 — Presentation             │
│  main.cpp                                    │
│  Shows menus, takes user input, calls Bank   │
├──────────────────────────────────────────────┤
│         LAYER 2 — Business Logic             │
│  Account.h / SavingsAccount.h                │
│  CurrentAccount.h / Transaction.h            │
│  Bank.h / Bank.cpp                           │
│  All rules, permissions, and calculations    │
├──────────────────────────────────────────────┤
│          LAYER 3 — Data Access               │
│  FileHandler.h / FileHandler.cpp             │
│  Only responsible for file read/write        │
└──────────────────────────────────────────────┘
```

Each layer only communicates with the layer directly below it.  
`main.cpp` never touches files. `FileHandler` never shows any menu.

---

## 📚 Concepts Covered

| Concept | Where Used |
|---|---|
| **Encapsulation** | `protected` variables in `Account.h` |
| **Inheritance** | `SavingsAccount` and `CurrentAccount` extend `Account` |
| **Polymorphism** | `acc->deposit()` calls correct child function at runtime |
| **Abstract Class** | `Account` has pure virtual functions `= 0` |
| **Dynamic Memory** | `new` in `FileHandler`, `delete` in `Bank::~Bank()` |
| **Pointers** | `vector<Account*>` stores base class pointers |
| **Bitwise OR** | `CAN_WITHDRAW \| CAN_DEPOSIT` to assign permissions |
| **Bitwise AND** | `permissions & CAN_DEPOSIT` to check permissions |
| **Bit Shifting** | `type << 28` and `encoded >> 28` in `Transaction.h` |
| **File Handling** | `ofstream` for save, `ifstream` for load |
| **Arrays** | `double monthlyTotals[12]` for monthly summary |
| **Vectors** | `vector<Account*>` and `vector<double> transactions` |


---

## 🔨 How to Compile

Make sure you are inside the project folder, then run:

```bash
g++ -o bank main.cpp Bank.cpp FileHandler.cpp
```

> ⚠️ You must include **all three** `.cpp` files in the compile command.

---

## ▶️ How to Run

```bash
./bank
```

On Windows:
```bash
bank.exe
```

---

## 💻 Usage

When the program starts, it **automatically loads** saved data from `accounts.txt`.

```
=============================
   BANKING TRANSACTION SYSTEM
=============================

--- Main Menu ---
1. Create Account
2. Deposit
3. Withdraw
4. Transfer
5. Show Account
6. Save to File
7. Load from File
8. Monthly Summary
9. Admin Mode
0. Exit
Enter choice:
```

### Creating an Account
- Choose account type: `Savings` or `Current`
- Enter your name and initial balance
- Choose permission level:
  - **Basic** → Withdraw + Deposit
  - **Full** → Withdraw + Deposit + Transfer
  - **VIP** → All permissions

### Admin Mode
- Select option `9` from the menu
- Enter password: `admin123`
- View all accounts and monthly summary

> 💡 When you choose `0` to exit, all data is **automatically saved**.

---

## 💾 File Format

Data is stored in `accounts.txt` in plain text format:

```
NEXTID 1003
ACCOUNT Savings
1001 Ali 5000 7
TRANSACTIONS
1000
-500
300
END
ACCOUNT Current
1002 Sara 8000 3
TRANSACTIONS
2000
-1000
END
```

| Field | Description |
|---|---|
| `NEXTID` | Tracks the next account ID to prevent duplicates |
| `ACCOUNT` | Account type (Savings / Current) |
| `1001 Ali 5000 7` | ID, Name, Balance, Permissions |
| `TRANSACTIONS` | Marks start of transaction history |
| Positive values | Deposits |
| Negative values | Withdrawals |
| `END` | Marks end of one account block |

---

## 🔒 Bitwise Permission System

Each account stores permissions as a single `unsigned int` using bit flags:

```
Bit 0 → 1  → CAN_WITHDRAW
Bit 1 → 2  → CAN_DEPOSIT
Bit 2 → 4  → CAN_TRANSFER
Bit 3 → 8  → VIP_ACCOUNT
```

### Assigning Permissions (Bitwise OR)
```cpp
permissions = CAN_WITHDRAW | CAN_DEPOSIT | CAN_TRANSFER;
// 1 | 2 | 4 = 7
```

### Checking Permissions (Bitwise AND)
```cpp
if (permissions & CAN_DEPOSIT)   // check if deposit is allowed
if (permissions & CAN_WITHDRAW)  // check if withdraw is allowed
```

### Permission Values
| Value | Meaning |
|---|---|
| `3` | Withdraw + Deposit |
| `7` | Withdraw + Deposit + Transfer |
| `15` | All permissions (VIP) |

---

## 🗜️ Transaction Compression

Each transaction is encoded into a **single unsigned int** using bit manipulation:

```
[ 4 bits — transaction type ][ 28 bits — amount ]
```

| Type Value | Meaning |
|---|---|
| `1` | Deposit |
| `2` | Withdrawal |
| `3` | Transfer |

### Encoding
```cpp
unsigned int encoded = (type << 28) | (amount & 0x0FFFFFFF);
```

### Decoding
```cpp
type   = (encoded >> 28) & 0xF;
amount =  encoded & 0x0FFFFFFF;
```

---

## 📸 Screenshots

### Main Menu
```
=============================
   BANKING TRANSACTION SYSTEM
=============================
1. Create Account
2. Deposit
3. Withdraw
4. Transfer
5. Show Account
6. Save to File
7. Load from File
8. Monthly Summary
9. Admin Mode
0. Exit
```

### Account Details
```
-----------------------------
Type        : Savings
Account ID  : 1001
Name        : Ali
Balance     : 4800
Permissions : [Withdraw] [Deposit] [Transfer]
Transactions:
  [1] Deposit   : +5000
  [2] Withdrawal: -200
-----------------------------
```

### Monthly Summary
```
--- Monthly Summary ---
Jan: 5000
Feb: -200
Mar: 1500
Apr: 0
...
```

---

## 👨‍💻 Author

**Muhammad Usman Dasti**  
BS Computer Science 
📅 2026

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

> 💡 **Note:** This project was built for educational purposes as part of a CS semester assignment covering OOP, Data Structures, File Handling, and Bitwise Operations in C++.
