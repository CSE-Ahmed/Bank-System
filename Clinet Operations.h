#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "Global Helpers.h"
using namespace std;

// =========================================================
// 1. Conversions (Line <-> Record)
// =========================================================
stClient ConvertLinetoClientRecord(string Line, string Seperator = "#//#") {
    stClient Client;
    vector<string> vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

string ConvertRecordToLine(stClient Client, string seperator = "#//#") {
    string ClientRecord = "";
    ClientRecord += Client.AccountNumber + seperator;
    ClientRecord += Client.PinCode + seperator;
    ClientRecord += Client.Name + seperator;
    ClientRecord += Client.Phone + seperator;
    ClientRecord += to_string(Client.AccountBalance);

    return ClientRecord;
}

// =========================================================
// 2. File Operations (Load & Save)
// =========================================================
vector<stClient> LoadClientsDataFromFile() {
    vector<stClient> vClients;
    fstream MyFile;

    MyFile.open(ClientFileName, ios::in);

    if (MyFile.is_open()) {
        string Line;
        stClient Client;
        while (getline(MyFile, Line)) {
            Client = ConvertLinetoClientRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void SaveClientsDataToFile(string FileName, vector<stClient> vClients) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {
        string DataLine;
        for (stClient C : vClients) {
            if (C.Mark == false) {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
}

void AddClientRecordToFile(string Record) {
    fstream ClientRecord;
    ClientRecord.open(ClientFileName, ios::out | ios::app);

    if (ClientRecord.is_open()) {
        ClientRecord << Record << endl;
        ClientRecord.close();
    }
}

// =========================================================
// 3. Core Search & Validation Operations
// =========================================================
bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client) {
    for (stClient C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            Client = C;
            return true;
        }
    }
    return false;
}

bool ClientExistsByAccountNumber(string AccountNumber, vector<stClient> vClients) {
    stClient Client;
    return FindClientByAccountNumber(AccountNumber, vClients, Client);
}


// =========================================================
// 4. Basic Input/Output Helpers
// =========================================================
string ReadAccountNumber() {
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

stClient ReadNewRecord(vector<stClient> vClients) {
    stClient Client;

    cout << "Enter your Account Number ? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, vClients)) {
        cout << "\nClient with Account Number [" << Client.AccountNumber << "] already exists, Choose another one ? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter your Pin Code ? ";
    getline(cin, Client.PinCode);
    cout << "Enter your name ? ";
    getline(cin, Client.Name);
    cout << "Enter your phone Number ? ";
    getline(cin, Client.Phone);
    cout << "Enter your Account Balance ? ";
    cin >> Client.AccountBalance;

    return Client;
}

void PrintClientRecord(stClient Client) {
    cout << "\nThe following are the client details:\n\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
}

void PrintClientsRecord(stClient Client) {
    cout << "|" << left << setw(15) << Client.AccountNumber;
    cout << "|" << left << setw(15) << Client.PinCode;
    cout << "|" << left << setw(15) << Client.Name;
    cout << "|" << left << setw(15) << Client.Phone;
    cout << "|" << left << setw(15) << Client.AccountBalance;
}

stClient UpdateClientData(stClient& Client) {
    cout << "\nEnter the new data for this client\n";
    cout << "Pin Code        : ";
    getline(cin >> ws, Client.PinCode);
    cout << "Name            : ";
    getline(cin, Client.Name);
    cout << "Phone           : ";
    getline(cin, Client.Phone);
    cout << "Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}

// =========================================================
// 5. Transactions Operations
// =========================================================
bool DepositeClientByAccounNumber(string AccountNumber, vector<stClient>& vClient, double Amount) {
    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
        cout << "\nAre you sure you want to deposit to this account ? [Y/N] \n";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            for (stClient& C : vClient) {
                if (C.AccountNumber == AccountNumber) {
                    C.AccountBalance += Amount;
                    break;
                }
            }
            SaveClientsDataToFile(ClientFileName, vClient);
            cout << "\nDeposit added successfully :) \n";
            return true;
        }
    }
    else {
        cout << "\nAccount with Number [" << AccountNumber << "] Not Found !\n";
        return false;
    }
    return false;
}

bool WithDrawClientByAccounNumber(string AccountNumber, vector<stClient>& vClient, double Amount) {
    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
        PrintClientRecord(Client);

        // تم تصحيح الكلمة من deposit إلى withdraw
        cout << "\nAre you sure you want to withdraw from this account ? [Y/N] \n";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            for (stClient& C : vClient) {
                if (C.AccountNumber == AccountNumber) {
                    if (C.AccountBalance >= Amount) {
                        C.AccountBalance -= Amount;
                    }
                    else {
                        cout << "Enter a figure that fits your budget : " << C.AccountBalance << endl;
                    }
                }
            }
            SaveClientsDataToFile(ClientFileName, vClient);
            cout << "\nWithdraw done successfully :) \n";
            return true;
        }
    }
    else {
        cout << "\nAccount with Number [" << AccountNumber << "] Not Found !\n";
        return false;
    }
    return false;
}

// =========================================================
// 6. Main Operations & UI Screens
// =========================================================

void AddNewClient(vector<stClient>& vClients) {
    stClient Client = ReadNewRecord(vClients);
    vClients.push_back(Client);
    AddClientRecordToFile(ConvertRecordToLine(Client));
}

void AddClients(vector<stClient>& vClients) {
    char AddMore = 'Y';
    do {
        system("cls");
        cout << "Adding New client ? \n";
        AddNewClient(vClients);
        cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void FindClient(string AccountNumber, vector<stClient> vClients) {
    stClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintClientRecord(Client);
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n" << endl;
    }
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) {
    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintClientRecord(Client);
        cout << "\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            for (stClient& C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C.Mark = true;
                    break;
                }
            }
            SaveClientsDataToFile(ClientFileName, vClients);
            cout << "\n\nClient Deleted Successfully." << endl;
            vClients = LoadClientsDataFromFile();
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n" << endl;
        return false;
    }
    return false;
}

void PrintAllClientsRecord(vector<stClient> vString) {
    cout << setw(50) << "Client List (" << vString.size() << ") client (s) " << setw(50) << endl;
    cout << string(90, '_') << "\n\n";
    cout << "| " << left << setw(14) << "Account Number";
    cout << "| " << left << setw(14) << "Pin Code ";
    cout << "| " << left << setw(14) << "Name ";
    cout << "| " << left << setw(14) << "Phone ";
    cout << "| " << left << setw(15) << "Account Balance \n";
    cout << string(90, '_') << "\n\n";

    for (short i = 0; i < vString.size(); i++) {
        PrintClientsRecord(vString[i]);
        cout << endl;
    }
    cout << string(90, '_') << endl;
}

bool updateClientByAccountNumber(string AccountNumber, vector<stClient>& vClient) {
    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client)) {
        PrintClientRecord(Client);
        cout << "\nAre you sure you want to update this Client ? [Y/N]\n";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            for (stClient& C : vClient) {
                if (C.AccountNumber == AccountNumber) {
                    UpdateClientData(C);
                    break;
                }
            }
            SaveClientsDataToFile(ClientFileName, vClient);
            cout << "\nClient updated successfully :) \n";
            return true;
        }
    }
    else {
        cout << "Client with Account Number [" << AccountNumber << "] Not found !\n";
        return false;
    }
    return false;
}

void ShowDepositScreen(vector<stClient>& vClients) {
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    stClient Client;
    string AccountNumber = ReadAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadAccountNumber();
    }

    PrintClientRecord(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositeClientByAccounNumber(AccountNumber, vClients, Amount);
}

void ShowWithdrawScreen(vector<stClient>& vClients) {
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    stClient Client;
    string AccountNumber = ReadAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadAccountNumber();
    }

    PrintClientRecord(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    while (Amount > Client.AccountBalance) {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    WithDrawClientByAccounNumber(AccountNumber, vClients, Amount);
}

void ShowTotalBalancesScreen(vector<stClient> vClients) {
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0) {
        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else {
        for (stClient C : vClients) {
            cout << "| " << setw(15) << left << C.AccountNumber;
            cout << "| " << setw(40) << left << C.Name;
            cout << "| " << setw(12) << left << C.AccountBalance << endl;
            TotalBalances += C.AccountBalance;
        }
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
}