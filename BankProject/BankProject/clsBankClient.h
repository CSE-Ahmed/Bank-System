#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
#include"clsPerson.h"
#include"clsString.h"
#include"clsInputValidate.h"
#include"clsUtil.h"
#include"Global.h"
using namespace std;
class clsBankClient : public clsPerson
{

private:
	
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;
	enum enMode {enEmptyMode = 0, enUpdateMode = 1, enAddNewMode = 2};
	enMode _Mode;

	struct stTrnsferLogRecord;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);
		
		return clsBankClient(enMode::enUpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::enEmptyMode, "", "", "", "", "","", 0);
	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client._AccountNumber + Seperator;
		stClientRecord += Client._PinCode + Seperator;
		stClientRecord += to_string(Client._AccountBalance);

		return stClientRecord;

	}

	static vector <clsBankClient> _LoadClientsDataFromFile() {
		vector <clsBankClient> vClientData;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			string Line;
			while (getline(MyFile, Line)) {
				clsBankClient Client1 = _ConvertLinetoClientObject(Line);
				vClientData.push_back(Client1);
			}
			MyFile.close();
		}
		return vClientData;
	}
																	 
	static void _SaveCleintsDataToFile(vector<clsBankClient> vClientData) {
		fstream MyFile;
		MyFile.open("Clients.txt",ios::out);

		if (MyFile.is_open()) {
			string DataLine;
			for (clsBankClient C : vClientData) {

				if (C.MarkedForDelete() == false) {
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestenationClient,
		string UserName, string Seperator = "#//#") {
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemTimeDate() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestenationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestenationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}


	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
	{

		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;

	}

	void _Update() {
		vector<clsBankClient> _vCleint = _LoadClientsDataFromFile();
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open()) {
			for (clsBankClient& C : _vCleint) {
				if (C.AccountNumber() == AccountNumber()) {
					C = *this;
					break;
				}
			}
			MyFile.close();
		}

		_SaveCleintsDataToFile(_vCleint);
	}

	void _AddDataLineToFile(string DataLine) {
		fstream Myfile;
		Myfile.open("Clients.txt", ios::out | ios::app);
		if (Myfile.is_open()) {
			
			Myfile << DataLine << endl;
			Myfile.close();
		
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}
		
public:
	
	clsBankClient(enMode Mode, string FirstName, string LastName, string Phone, string Email, string AccountNumber,
	string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone) {
		_Mode = Mode;
		_AccountBalance = AccountBalance;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
	}
	
	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;

	};

	string AccountNumber() {
		return _AccountNumber;
	}

	bool IsEmpty() {
		return (_Mode == enMode::enEmptyMode);
	}

	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetMarkedForDeleted(bool MarkedForDeleted) {
		_MarkedForDelete = MarkedForDeleted;
	}

	bool MarkedForDelete() {
		return _MarkedForDelete;
	}

	__declspec(property(get = MarkedForDelete, put = SetMarkedForDeleted)) bool MarkForDeleted;

	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}*/

	static clsBankClient Find(string AccountNumber) {
	fstream MyFile;
	MyFile.open("Clients.txt", ios::in);
	if (MyFile.is_open()) {
		string Line;
		while (getline(MyFile, Line)) {
			clsBankClient Client = _ConvertLinetoClientObject(Line);
			if (Client.AccountNumber() == AccountNumber) {
				MyFile.close();
				return Client;
			}
		}
		MyFile.close();
	}
	return _GetEmptyClientObject();
}

	static clsBankClient Find(string AccountNumber,string PinCode) {
	fstream MyFile;
	MyFile.open("Clients.txt", ios::in);
	if (MyFile.is_open()) {
		string Line;
		while (getline(MyFile, Line)) {
			clsBankClient Client = _ConvertLinetoClientObject(Line);
			if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
				MyFile.close();
				return Client;
			}
		}
		MyFile.close();
	}
	return _GetEmptyClientObject();
}

	static bool IsClientExist(string AccountNumber) {
	clsBankClient Client1 = clsBankClient::Find(AccountNumber);
	return (!Client1.IsEmpty());
}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2};

	enSaveResults Save() {
	switch (_Mode) {
	case enMode::enEmptyMode: {
		if (IsEmpty()) {
			return enSaveResults::svFaildEmptyObject;
		}
		
	}
	case enMode::enUpdateMode: {
		_Update();
		return enSaveResults::svSucceeded;
		break;
	}

	case enMode::enAddNewMode: {
		if (clsBankClient::IsClientExist(_AccountNumber)) {
			return enSaveResults::svFaildAccountNumberExists;
		}
		else {
			_AddNew();
			_Mode = enMode::enUpdateMode;
			return enSaveResults::svSucceeded;
		}
		break;
	}
	}
}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {
		return clsBankClient(enMode::enAddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
		
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}

		}
		_SaveCleintsDataToFile(_vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector <clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances() {
		vector <clsBankClient> vClient = _LoadClientsDataFromFile();
		float TotalBalances = 0;

		for (clsBankClient& C : vClient) {
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	static void PrintClientRecordBalanceLine(clsBankClient Client)
	{

		cout << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;

	}

	static void ShowTotalBalances()
	{

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		double TotalBalances = clsBankClient::GetTotalBalances();

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

			for (clsBankClient Client : vClients)
			{
				PrintClientRecordBalanceLine(Client);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
		cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance) {
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
			return true;
		}
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient,string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);
		return true;
	}

	static  vector <stTrnsferLogRecord> GetTransfersLogList()
	{
		vector <stTrnsferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stTrnsferLogRecord TransferRecord;

			while (getline(MyFile, Line))
			{

				TransferRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferRecord);

			}

			MyFile.close();

		}

		return vTransferLogRecord;
	}
};