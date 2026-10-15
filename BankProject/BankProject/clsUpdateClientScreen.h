#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h"
class clsUpdateClientScreen : clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

	static void _PrintClientInfo(clsBankClient Client) {
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

public:

	static void UpdateClient() {
		
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}
		
		clsScreen::_DrawScreenHeader("\t\t Update Client Scren");
		
		string AccountNumber = "";
		cout << "\nEnter Account Number : \n";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClientInfo(Client1);
		char choice;
		cout << "Are you sure you want to update this client info? [y/n] ?";
		cin >> choice;

		if (choice == 'y' || choice == 'Y') {
			cout << "\n\nUpdate Client Info:";
			cout << "\n____________________\n";

			_ReadClientInfo(Client1);

			clsBankClient::enSaveResults SaveResult;
			SaveResult = Client1.Save();

			switch (SaveResult)
			{
			case  clsBankClient::enSaveResults::svSucceeded:
			{
				cout << "\nAccount Updated Successfully :-)\n";
				break;
			}
			case clsBankClient::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;

			}
			}
		}
	}
};

