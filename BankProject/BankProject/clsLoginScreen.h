#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsInputValidate.h"
#include"clsMainScreen.h"
#include"clsScreen.h"
#include"Global.h"
class clsLoginScreen : clsScreen
{
private:
	static bool _Login() {
		bool LoginFaild = false;
		short LoginFaildCounter = 0;
		string UserName, Password;
		do {
			if (LoginFaild) {
				LoginFaildCounter++;
				cout << "Invalid Username/password! \n\n";
				cout << "you have " << (3 - LoginFaildCounter) << " Trial(s) to login\n";
			}

			if (LoginFaildCounter == 3) {
				cout << "You're locked after trying 3 times\n";
				return false;
			}
			cout << "Enter Username : ";
			cin >> UserName;
			cout << "Enter Password : ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
	}
public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t\t Login Screen");
		return _Login();
	}
};

