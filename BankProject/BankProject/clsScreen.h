#pragma once
#include<iostream>
#include<string>
#include"clsUser.h"
#include"Global.h"
#include"clsDate.h"
using namespace std;
class clsScreen
{
protected:
	static void _DrawScreenHeader(string title, string subtitle = "") {
		cout << "\t\t\t\t\t______________________________________";
		cout << "\n\n\t\t\t\t" << title;
		if (subtitle != ""){
			cout << "\n\t\t\t\t\t  " << subtitle;
		}
		cout << "\n\t\t\t\t\t______________________________________\n\n";

        cout << "\t\t\t\t\tUser : " << CurrentUser.UserName << endl;
        
        cout << "\t\t\t\t\tDate : " << clsDate::GetSystemTimeDate() << endl;
	}
    
    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {

        if (!CurrentUser.CheckAccessPermissions(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
        else
        {
            return true;
        }

    }
};

