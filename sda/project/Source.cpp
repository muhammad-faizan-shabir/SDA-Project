#include<iostream>

#include "PersonManager.h"
#include "Person.h"
#include "ReportGenerator.h"
#include "PersonManagerInterface1.h"
#include "PersonManagerInterface2.h"
#include "PersonManagerInterface3.h"
#include "State.h"
#include "DataHandler.h"
using namespace std;


void login(PersonManager* personManager)
{
	int Id = 0;
	string password;
	cout << endl << "Login Screen" << endl;
	cout << "Enter ID: ";
	cin >> Id;
	cout << "Enter password: ";
	cin >> password;
	Person* person = personManager->matchCredentials(Id, password);
	
	if (person!=nullptr)
	{
		person->userInterface();
	}
	else
	{
		cout << "Invalid ID or Password" << endl;
	}
}




void showMenu(PersonManager* personManager)
{
	bool flag = true;
	while (flag == true)
	{
		cout << endl << "Welcome to Attendance and Leave Management System" << endl;
		int choice = 0;
		cout << "Press 1 to Login" << endl;
		cout << "Press 2 to Quit" << endl;
		cin >> choice;
		if (choice == 1)
		{
			login(personManager);
		}
		else if (choice == 2)
		{
			cout << "Good Bye!" << endl;
			flag = false;
		}
		else
		{
			cout << "Invalid Input! " << endl;
		}
	}
}

int main()
{
	string name;
	int id;
	string password;
	getDirectorCredentials(name,id,password);
	Director* d = new Director(name, id, password);
	PersonManager personManager(d);
	ReportGenerator rg(&personManager);
	getAdminCredentials(name,id,password);
	Admin* ad = new Admin(name, id, password, &personManager, &rg);
	personManager.addPerson(ad);



	loadData(&personManager);
	showMenu(&personManager);
	saveData(&personManager);
	PendingAtSupervisorOnly::deletePendingAtSupervisorOnlyObj();
	PendingAtSupervisor::deletePendingAtSupervisorObj();
	PendingAtDirector::deletePendingAtDirectorObj();
	Accepted::deleteAcceptedObj();
	Rejected::deleteRejectedObj();
	system("pause");
}


