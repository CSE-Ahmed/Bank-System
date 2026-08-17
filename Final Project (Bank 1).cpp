#include <iostream>
#include <string>
#include "Clinet Operations.h"
#include "User Operations.h"

using namespace std;

void ShowMainMenu(); 

void LoginScreen(stUsers &User) {
    bool LoginFailed = false;

    do {
        system("cls");

        cout << "------------------------------------------\n";
        cout << "\t\tLogin Screen\n";
        cout << "------------------------------------------\n";

        if (LoginFailed) {
            cout << "Invalid Username/Password!\n";
        }

        cout << "Enter Username? ";
        cin >> User.UserName;
        cout << "Enter Password? ";
        cin >> User.Password;

        LoginFailed = !FindUserByUsernameAndPassword(User.UserName, User.Password, User);

    } while (LoginFailed);

    ShowMainMenu();
}

void AccessDenied() {
    cout << string(40, '-') << endl;
    cout << "Access Denied, \n";
    cout << "You Don't Have Permissions to do it\n";
    cout << "Please Contact Your Admin \n";
    cout << string(40, '-') << endl;
}

bool CheckAccess(enPermissions Permissions, stUsers CurrentUser) {
    if (Permissions == enPermissions::eAll) {
        return true;
    }

    if ((Permissions & CurrentUser.Access) == Permissions) {
        return true;
    }

    else {
        return false;
    }
}

void GoBackToMainMenu() {
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
}

void GoBackToTransactionsMenu() {
    cout << "\n\nPress any key to go back to Transactions Menu...";
    system("pause>0");
}

void GoBackToManageMenu() {
    cout << "\n\nPress any key to go back to Manage Menu...";
    system("pause>0");
}

void ShowAllClientsScreen(vector<stClient>& vClients) {
    cout << "\n-----------------------------------\n";
    cout << "\tShow Client List Screen";
    cout << "\n-----------------------------------\n";
    PrintAllClientsRecord(vClients);
}

void ShowAddNewClientsScreen(vector<stClient>& vClients) {
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddClients(vClients);
}

void ShowDeleteClientScreen(vector<stClient>& vClients) {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen(vector<stClient>& vClients) {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    string AccountNumber = ReadAccountNumber();
    updateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen(vector<stClient>& vClients) {
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    string AccountNumber = ReadAccountNumber();
    FindClient(AccountNumber, vClients);
}

void ShowEndScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

void PerformTransactionsMenuOption(enTransactionsMenuOptions Option, vector<stClient>& vClients) {
    switch (Option) {
    case enTransactionsMenuOptions::eDeposit:
        system("cls");
        ShowDepositScreen(vClients);
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOptions::eWithdraw:
        system("cls");
        ShowWithdrawScreen(vClients);
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOptions::eTotalBalances:
        system("cls");
        ShowTotalBalancesScreen(vClients);
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOptions::eShowMainMenu:
        break;
    }
}

void ShowTransactionsMenuScreen(vector<stClient>& vClients) {
    short Choice;
    do {
        system("cls");
        cout << "===========================================\n";
        cout << "\t\tTransactions Menu Screen\n";
        cout << "===========================================\n";
        cout << "\t[1] Deposit.\n";
        cout << "\t[2] Withdraw.\n";
        cout << "\t[3] Total Balances.\n";
        cout << "\t[4] Main Menu.\n";
        cout << "===========================================\n";
        cout << "Choose what do you want to do? [1 to 4]? ";

        cin >> Choice;
        PerformTransactionsMenuOption((enTransactionsMenuOptions)Choice, vClients);

    } while (Choice != enTransactionsMenuOptions::eShowMainMenu);
}

void PerformManageMenuOption(enManagerusers Option, vector<stUsers>& vUsers) {
    switch (Option) {
    case enManagerusers::eListUsers:
        system("cls");
        PrintAllUsersRecord(vUsers);
        GoBackToManageMenu();
        break;
    case enManagerusers::eAddNewUsers:
        system("cls");
        AddUsers(vUsers);
        GoBackToManageMenu();
        break;
    case enManagerusers::eDeleteUser: {
        system("cls");
        string Username = ReadUserName();
        DeleteUserByUsername(Username, vUsers);
        GoBackToManageMenu();
        break;
    }
    case enManagerusers::eUpdateUser: {
        system("cls");
        string Username = ReadUserName();
        UpdateUserByUsername(Username, vUsers);
        GoBackToManageMenu();
        break;
    }
    case enManagerusers::eFindUser: {
        system("cls");
        string Username = ReadUserName();
        FindUser(Username, vUsers);
        GoBackToManageMenu();
        break;
    }
    case enManagerusers::eMainMenu:
        break;
    }

}

void showmanageMenuScreen(vector<stUsers>& vUsers) {
    short Choice;
    do {
        system("cls");
        cout << "===========================================\n";
        cout << "\t\tManage Menu Screen\n";
        cout << "===========================================\n";
        cout << "\t[1] Show All Users.\n";
        cout << "\t[2] Add New User.\n";
        cout << "\t[3] Delete User.\n";
        cout << "\t[4] Update User.\n";
        cout << "\t[5] Find User.\n";
        cout << "\t[6] Main Menu.\n";
        cout << "===========================================\n";

        cin >> Choice;
        PerformManageMenuOption((enManagerusers)Choice, vUsers);
    } while (Choice != enManagerusers::eMainMenu);
}

void ShowMainMenu() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Log Out.\n";
    cout << "===========================================\n";
    cout << "Choose what do you want to do? [1 to 8]? ";
}

void PerformMainMenuOption(enMainMenuOptions Option, vector<stClient>& vClients, vector<stUsers> &vUsers, stUsers &CurrentUser) {
    switch (Option) {
    case enMainMenuOptions::eListClients:
        system("cls");
        if (CheckAccess(enPermissions::enListClients, CurrentUser)) {
            ShowAllClientsScreen(vClients);
        }
        else {
            AccessDenied();
        }
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eAddNewClient:
        system("cls");
        if(CheckAccess(enPermissions::enAddNewClient,CurrentUser)){
            ShowAddNewClientsScreen(vClients);
        }
        else {
            AccessDenied();
        }
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eDeleteClient:
        system("cls");
        if (CheckAccess(enPermissions::enDeleteClient, CurrentUser)) {
            ShowDeleteClientScreen(vClients);
        }
        else {
            AccessDenied();
        }
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eUpdateClient:
        system("cls");
        if (CheckAccess(enPermissions::enUpdateClient, CurrentUser)) {
            ShowUpdateClientScreen(vClients);
        }
        else {
            AccessDenied();
        }
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eFindClient:
        system("cls");
        if (CheckAccess(enPermissions::enFindClient, CurrentUser)) {
            ShowFindClientScreen(vClients);
        }
        else {
            AccessDenied();
        }
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eTransactions:
        system("cls");
        if (CheckAccess(enPermissions::enTransactions, CurrentUser)) {
            ShowTransactionsMenuScreen(vClients);
        }
        else {
            AccessDenied();
        }
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eMangeUsers:
        system("cls");
        if (CheckAccess(enPermissions::enManageUsers, CurrentUser)) {
            showmanageMenuScreen(vUsers);
        }
        else {
            AccessDenied();
        }
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eLogOut:
        system("cls");
        ShowEndScreen();
        break;
    }
}

void StartBankSystem(vector<stClient>& vClients, vector<stUsers>& vUsers) {
    short Choice;
    stUsers CurrentUser;

    LoginScreen(CurrentUser);
    do {
        ShowMainMenu();
        cin >> Choice;
        PerformMainMenuOption((enMainMenuOptions)Choice, vClients, vUsers,CurrentUser);
    } while (Choice != enMainMenuOptions::eLogOut);
}

int main() {
    vector<stClient> vClient = LoadClientsDataFromFile();
    vector<stUsers> vUsers = LoadUsersDataFromFile();
    StartBankSystem(vClient, vUsers);

    return 0;
}