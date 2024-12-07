#include "ReportGenerator.h"
#include "Person.h"
#include "PersonManager.h"
#include<string>
#include<iostream>
using namespace std;

ReportGenerator::ReportGenerator(PersonManager* interface)
{
	this->interface = interface;
}

void ReportGenerator::generateReport1()
{
	string month;
	float percentage;
	cout << "Enter month: " << endl;
	cin >> month;
	cout << "Enter percentage: ";
	cin >> percentage;
	
	vector<Person*> &persons = interface->getPersonList();
	
	cout << "Employees whose attendance for Month: " << month << " is less than " << percentage << endl;
	for (int i = 0; i < persons.size(); i++)
	{
		Employee* emp = dynamic_cast<Employee*>(persons[i]);
		if (emp != nullptr)
		{
			float computedPercentage = emp->computeAttendacePercentage(month);
			if (computedPercentage < percentage)
			{
				cout << "Name: " << emp->getName() << " ID: " << emp->getId() << endl;
			}
		}
	}
}



void ReportGenerator::generateReport2()
{
	vector<Person*>& persons = interface->getPersonList();
	cout << "Employees with Outstanding Leaves: " << endl;
	for (int i = 0; i < persons.size(); i++)
	{
		Employee* emp = dynamic_cast<Employee*>(persons[i]);
		if (emp != nullptr && emp->isAnyApplicationPending())
		{
			cout << "Name: " << emp->getName() << " ID: " << emp->getId() << endl;
		}
	}
}

void ReportGenerator::generateReport3()
{
	interface->printAllEmployees();
	int id;
	cout << "Enter ID of the Employee whose attendance is to be seen: ";
	cin >> id;
	
	Employee* emp = interface->getEmployee(id);
	
	if (emp!= nullptr)
	{
		cout << "Attendance details for employee with Id: " << id << endl;
		emp->printAttendanceDetails();
	}
	else
	{
		cout << "Error! Invalid ID" << endl;
	}
}

void ReportGenerator::generateReport4()
{
	interface->printAllEmployees();
	int id;
	cout << "Enter ID of the Employee whose leave deatils are to be seen: ";
	cin >> id;

	Employee* emp = interface->getEmployee(id);

	if (emp != nullptr)
	{
		cout << "Leave Details for employee with Id: " << id << endl;
		emp->printLeaveApplicationDetails();
		cout << "Casual Leaves left to avail: " << emp->getCasualLeaves() << endl;
		cout << "Earned Leaves left to avail: " << emp->getEarnedLeaves() << endl;
	}
	else
	{
		cout << "Error! Invalid ID" << endl;
	}
}