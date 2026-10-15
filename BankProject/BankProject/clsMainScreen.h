#pragma once
#include<iostream>
#include<iomanip>
#include"Global.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsClientListScreen.h"
#include"clsAddNewClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsTransactionsScreen.h"
#include"clsManageUsersScreen.h"
#include"clsLoginRegisterScreen.h"
#include"clsCurrencyExchangeMainScreen.h"
using namespace std;
class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOption {
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7,eLoginRegister = 8, eCurrencyExchange = 9,eExit = 10
	};

	static short _ReadMainMenuOption() {
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
		short choice = clsInputValidate::ReadshortNumberBetween(1, 10, "Enter Number between 1 to 10 ? ");
		return choice;
	}

	static void _GoBacktoMainMenu() {
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");
		ShowMainMenue();
	}

    static void _ShowAllClientsScreen()
    {
        //cout << "\nClient List Screen Will be here...\n";
        clsClientListScreen::ShowClientsList();

    }

    static void _ShowAddNewClientsScreen()
    {
        //cout << "\nAdd New Client Screen Will be here...\n";
        clsAddNewClientScreen::AddNewClient();
    }

    static void _ShowDeleteClientScreen()
    {
        //cout << "\nDelete Client Screen Will be here...\n";
        clsDeleteClientScreen::DeleteClient();
    }

    static void _ShowUpdateClientScreen()
    {
        //cout << "\nUpdate Client Screen Will be here...\n";
        clsUpdateClientScreen::UpdateClient();
    }

    static void _ShowFindClientScreen()
    {
        //cout << "\nFind Client Screen Will be here...\n";
        clsFindClientScreen::FindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        //cout << "\nTransactions Menue Will be here...\n";
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        //cout << "\nUsers Menue Will be here...\n";
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    static void _ShowLoginRegisterScreen() {
        
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    
    }

    static void _ShowCurrencyExchangeScreen() {
        //cout << "We will be here soon";
        clsCurrencyExchangeMainScreen::ShowCurrenciesMenue();
    }

    /*static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be here...\n";

    }*/

    static void _LogOut() {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerformMainMenuOption(enMainMenuOption MainMenuOption) {
        switch (MainMenuOption) {
        case enMainMenuOption::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eAddNewClient:
        {
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eDeleteClient:
        {
            system("cls");
            _ShowDeleteClientScreen();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eUpdateClient:
        {
            system("cls");
            _ShowUpdateClientScreen();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eFindClient:
        {
            system("cls");
            _ShowFindClientScreen();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eShowTransactionsMenue:
        {
            system("cls");
            _ShowTransactionsMenue();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eManageUsers:
        {
            system("cls");
            _ShowManageUsersMenue();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eLoginRegister:
        {
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eCurrencyExchange:
        {
            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoBacktoMainMenu();
            break;
        }
        case enMainMenuOption::eExit:
        {
            system("cls");
            _LogOut();
            break;
        }
        }
    }

public:
    
    static void ShowMainMenue()
    {

        system("cls");
        _DrawScreenHeader("\t\t      Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformMainMenuOption((enMainMenuOption)_ReadMainMenuOption());
    }

};

