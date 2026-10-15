#pragma once
#include<iostream>
#include<iomanip>
#include"clsUser.h"
#include"clsInputValidate.h"
#include"clsScreen.h"
using namespace std;
class clsUpdateUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        User.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        User.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        User.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Password: ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

    static short _ReadPermissionsToSet() {
        short Permissions = 0;
        char Choice = 'y';

        vector<string> vPermissionsQuestions = {
            "Show Clients List ? [y/n]",
            "Add New Client ? [y/n]",
            "Delete Client ? [y/n]",
            "Update Client ? [y/n]",
            "Find Client ? [y/n]",
            "Transactions ? [y/n]",
            "Manage Users ? [y/n]",
            "Login Register? [y/n]"
        };

        cout << "Do you want to give Full Access ? [y/n] \n";
        cin >> Choice;
        if (toupper(Choice) == 'Y') {
            return -1;
        }

        cout << "Do you want to give Access to : \n";
        for (short i = 0; i < vPermissionsQuestions.size(); ++i) {
            cout << vPermissionsQuestions[i] << " ";
            cin >> Choice;

            if (toupper(Choice) == 'Y') {
                Permissions = (Permissions | (1 << i));
            }
        }

        if (Permissions == 255) {
            Permissions = -1;
        }

        return Permissions;
    }

public:
    
    static void ShowUpdateUserScreen()
    {

        _DrawScreenHeader("\tUpdate User Screen");

        string UserName = "";

        cout << "\nPlease Enter User UserName: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nAccount number is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        _PrintUser(User1);

        cout << "\nAre you sure you want to update this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";


            _ReadUserInfo(User1);

            clsUser::enSaveResults SaveResult;

            SaveResult = User1.Save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";

                _PrintUser(User1);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;

            }

            }

        }

    }
};

