#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

static int Count = 0;

class Account {
private:
    char name[100];
    int balance;

public:
    // 預設建構子
    Account() {
        balance = 0;
        name[0] = '\0';
        Count++;
    }

    // 輸入建構子
    Account(int initialBalance, const char* accName) {
        balance = initialBalance;
        strcpy(name, accName);
        Count++;
        cout << Count << endl;
    }

    // 存款函數
    void Deposit(int amount) {
        balance += amount;
    }

    // 提款函數
    void Withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    // 取得使用者名稱
    const char* GetName() const {
        return name;
    }


    // 取得帳戶餘額
    int GetBalance() const {
        return balance;
    }


    // 取得帳戶數量
    static int GetCount() {
        return Count;
    }

    // 解構子
    ~Account() {
    }
};

int main() {
    // 儲存所有帳戶
    vector<Account> accounts;
    char name[100];
    
    while (true) {
        cout << "Enter your name (or enter 'quit' to exit): ";
        cin >> name;

        if (strcmp(name, "quit") == 0) {
            break;
        }

        int balance;
        cout << "Enter initial balance: ";
        cin >> balance;

        Account acc(balance, name);
        accounts.push_back(acc);

        while (true) {
            cout << "\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. Quit\n";
            cout << "Choose an operation: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                int amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                acc.Deposit(amount);
            } else if (choice == 2) {
                int amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                acc.Withdraw(amount);
            } else if (choice == 3) {
                break;
            } else {
                cout << "Invalid choice. Please choose again." << endl;
            }
        }

        cout << acc.GetName() << "'s balance is " << acc.GetBalance() << endl;
    }

    cout << "There are " << Account::GetCount() << " accounts in this ATM." << endl;
    cout << "----------------------------------" << endl;

    for (const auto& acc : accounts) {
        cout << acc.GetName() << "'s balance is " << acc.GetBalance() << endl;
    }

    return 0;
}

    // // 設定使用者名稱
    // void SetName(const char* accName) {
    //     strcpy(name, accName);
    // }
    // // 設定帳戶餘額
    // void SetBalance(int amount) {
    //     balance = amount;
    // }