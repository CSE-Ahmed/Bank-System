#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

const string UsersFileName = "Users.txt";
const string ClientFileName = "ClientsRecord.txt";

struct stUsers {
    string UserName;
    string Password;
    int Access;
    bool Mark = false;
};

struct stClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool Mark = false;
};

enum enMainMenuOptions {
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransactions = 6,
    eMangeUsers = 7,
    eLogOut = 8
};

enum enTransactionsMenuOptions {
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalances = 3,
    eShowMainMenu = 4
};

enum enManagerusers {
    eListUsers = 1,
    eAddNewUsers = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenu = 6
};

enum enPermissions {
    eAll = -1,
    enListClients = 1,
    enAddNewClient = 2,
    enDeleteClient = 4,
    enUpdateClient = 8,
    enFindClient = 16,
    enTransactions = 32,
    enManageUsers = 64
};

vector<string> SplitString(string S1, string delim = "#//#") {
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(delim)) != std::string::npos) {
        sWord = S1.substr(0, pos);
        if (sWord != "") {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + delim.length());
    }
    if (S1 != "") {
        vString.push_back(S1);
    }
    return vString;
}