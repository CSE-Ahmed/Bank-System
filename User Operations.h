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

stUsers ConvertLineToUserRecord(string Line, string Seperator = "#//#") {
    stUsers User;
    vector<string> vUserData = SplitString(Line, Seperator);

    User.UserName = vUserData[0];
    User.Password = vUserData[1];
    User.Access = stoi(vUserData[2]);

    return User;
}

string ConvertRecordToUserLine(stUsers User, string seperator = "#//#") {
    string UserRecord = "";

    UserRecord += User.UserName + seperator;
    UserRecord += User.Password + seperator;
    UserRecord += to_string(User.Access);

    return UserRecord;
}

// =========================================================
// 2. File Operations (Load & Save)
// =========================================================

vector<stUsers> LoadUsersDataFromFile() {
    vector<stUsers> vUsers;
    fstream MyFile;
    MyFile.open(UsersFileName, ios::in);

    if (MyFile.is_open()) {
        string Line;
        stUsers User;
        while (getline(MyFile, Line)) {
            User = ConvertLineToUserRecord(Line);
            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return vUsers;
}

void SaveUsersDataToFile(string FileName, vector<stUsers> vUsers) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {
        string DataLine;
        for (stUsers U : vUsers) {
            if (U.Mark == false) { 
                DataLine = ConvertRecordToUserLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
}

void AddUserRecordToFile(string Record) {
    fstream UserRecord;
    UserRecord.open(UsersFileName, ios::out | ios::app);

    if (UserRecord.is_open()) {
        UserRecord << Record << endl;
        UserRecord.close();
    }
}

// =========================================================
// 3. Core Search & Validation Operations
// =========================================================

bool FindUserByUsername(string UserName, vector<stUsers> vUsers, stUsers& CurrentUser) {
    for (stUsers U : vUsers) {
        if (U.UserName == UserName) {
            CurrentUser = U;
            return true;
        }
    }
    return false;
}

bool FindUserByUsernameAndPassword(string UserName, string Password, stUsers& CurrentUser) {
    vector<stUsers> vUsers = LoadUsersDataFromFile();

    for (stUsers U : vUsers) {
        if (U.UserName == UserName && U.Password == Password) {
            CurrentUser = U;
            return true;
        }
    }
    return false;
}

bool UserExistsByUsername(string UserName, vector<stUsers> vUsers) {
    stUsers User;
    return FindUserByUsername(UserName, vUsers, User);
}

// =========================================================
// 4. Basic Input/Output Helpers & Permissions
// =========================================================

short Givepermissions() {
    short Permissions = 0; 
    char Choice = 'y';

    vector<string> vPermissionsQuestions = {
        "Show Clients List ? [y/n]",
        "Add New Client ? [y/n]",
        "Delete Client ? [y/n]",
        "Update Client ? [y/n]",
        "Find Client ? [y/n]",
        "Transactions ? [y/n]",
        "Manage Users ? [y/n]"
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

    if (Permissions == 127) {
        Permissions = -1;
    }

    return Permissions;
}

stUsers ReadNewUserRecord(vector<stUsers> vUsers) {
    stUsers User;

    cout << "Enter your Username ? ";
    getline(cin >> ws, User.UserName);

    while (UserExistsByUsername(User.UserName, vUsers)) {
        cout << "\nUser with Username [" << User.UserName << "] already exists, Choose another one ? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "Enter your Password ? ";
    getline(cin, User.Password);

    User.Access = Givepermissions();

    return User;
}

void PrintUserRecord(stUsers User) {
    cout << "\nThe following are the User details:\n\n";
    cout << "Username : " << User.UserName << endl;
    cout << "Password : " << User.Password << endl;
    cout << "Access   : " << User.Access << endl;
}

void PrintUsersRecord(stUsers User) {
    cout << "|" << left << setw(15) << User.UserName;
    cout << "|" << left << setw(15) << User.Password;
    cout << "|" << left << setw(15) << User.Access;
}

stUsers UpdateUsersData(stUsers& User) {
    cout << "\nEnter the new data for this User\n";
    cout << "Password       : ";
    getline(cin >> ws, User.Password);

    User.Access = Givepermissions();

    return User;
}

string ReadUserName() {
    string str;
    cout << "Enter Username : ";
    getline(cin >> ws, str);
    return str;
}

// =========================================================
// 5. Main Operations & UI Screens
// =========================================================

void AddNewUser(vector<stUsers>& vUsers) {
    stUsers User = ReadNewUserRecord(vUsers);
    vUsers.push_back(User);
    AddUserRecordToFile(ConvertRecordToUserLine(User));
}

void AddUsers(vector<stUsers>& vUsers) {
    char AddMore = 'Y';
    do {
        system("cls");
        cout << "Adding New User ? \n";
        AddNewUser(vUsers);
        cout << "\nUser Added Successfully, do you want to add more Users ? Y / N ? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void FindUser(string UserName, vector<stUsers> vUsers) {
    stUsers User;

    if (FindUserByUsername(UserName, vUsers, User)) {
        PrintUserRecord(User);
    }
    else {
        cout << "\nUser with UserName (" << UserName << ") is Not Found!\n" << endl;
    }
}

bool DeleteUserByUsername(string UserName, vector<stUsers>& vUsers) {
    stUsers User;
    char Answer = 'n';

    if (FindUserByUsername(UserName, vUsers, User)) {
        
        if (UserName == "Admin") {
            cout << "Admin cannot Removed :( \n";
            return false;
        }
        
        PrintUserRecord(User);
        cout << "\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            for (stUsers& U : vUsers) {
                if (U.UserName == UserName) {
                    U.Mark = true;
                    break;
                }
            }
            SaveUsersDataToFile(UsersFileName, vUsers);
            cout << "\n\nUser Deleted Successfully." << endl;
            vUsers = LoadUsersDataFromFile();
            return true;
        }
    }
    else {
        cout << "\nUser with UserName (" << UserName << ") is Not Found!\n" << endl;
        return false;
    }
    return false;
}

bool UpdateUserByUsername(string UserName, vector<stUsers>& vUsers) {
    stUsers User;
    char Answer = 'n';

    if (FindUserByUsername(UserName, vUsers, User)) {
        PrintUserRecord(User);
        cout << "\nAre you sure you want to update this User ? [Y/N]\n";
        cin >> Answer;

        if (toupper(Answer) == 'Y') {
            for (stUsers& U : vUsers) {
                if (U.UserName == UserName) {
                    UpdateUsersData(U);
                    break;
                }
            }

            SaveUsersDataToFile(UsersFileName, vUsers);
            cout << "\nUser updated successfully :) \n";
            return true;
        }
    }
    else {
        cout << "User with Username [" << UserName << "] Not found !\n";
        return false;
    }
    return false;
}

void PrintAllUsersRecord(vector<stUsers> vUsers) {
    cout << setw(50) << "User List (" << vUsers.size() << ") User(s) " << setw(50) << endl;
    cout << string(90, '_') << "\n\n";
    cout << "| " << left << setw(14) << "UserName ";
    cout << "| " << left << setw(14) << "Password ";
    cout << "| " << left << setw(14) << "Access ";
    cout << "\n" << string(90, '_') << "\n\n";

    for (short i = 0; i < vUsers.size(); i++) {
        PrintUsersRecord(vUsers[i]);
        cout << endl;
    }
    cout << string(90, '_') << endl;
}