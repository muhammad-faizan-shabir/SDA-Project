#include "PersonManager.h"
#include<iostream>
#include "Person.h"
#include "PersonManagerInterface1.h"
#include "PersonManagerInterface2.h"
#include "PersonManagerInterface3.h"

Person* PersonManager::matchCredentials(int id, string password)
{
	for (int i = 0; i < persons.size(); i++)
	{
		if (persons[i]->matchCredentials(id, password) == true)
		{
			return persons[i];
		}
	}
	return nullptr;
}

PersonManager::PersonManager(Director * d)
{
	director = d;
	persons.push_back(d);
}
PersonManager::~PersonManager()
{
	for(int i=0;i<persons.size();i++)
	{
		delete persons[i];
		persons[i] = nullptr;
	}
}

void PersonManager::addPerson(Person * p)
{
	persons.push_back(p);
}

int PersonManager::getPersonIndex(int id)
{
	for (int i = 0; i < persons.size(); i++)
	{
		if (persons[i]->getId() == id)
		{
			return i;
		}
	}
	return -1;
}
Director* PersonManager::getDirector()
{
	return director;
}

Employee* PersonManager::getEmployee(int Id)
{
	for (int i = 0; i < persons.size(); i++)
	{
		if (persons[i]->getId() == Id && dynamic_cast<Employee*>(persons[i]) != nullptr)
		{
			return dynamic_cast<Employee*>(persons[i]);
		}
	}

	return nullptr;
}

Supervisor* PersonManager::getSuperVisor(int Id)
{
	for (int i = 0; i < persons.size(); i++)
	{
		if (persons[i]->getId() == Id && dynamic_cast<Supervisor*>(persons[i]) != nullptr)
		{
			return dynamic_cast<Supervisor*>(persons[i]);
		}
	}

	return nullptr;
}

void PersonManager::addEmployee()
{
	printAllPersons();
	printAllSupervisors();
	string name;
	int id;
	string password;
	int supervisorId;
	cout << "Enter Employee Name: ";
	cin >> name;
	cout << "Enter Employee ID: ";
	cin >> id;
	cout << "Enter Employee Password: ";
	cin >> password;
	cout << "Enter Employee's Supervisor Id: ";
	cin >> supervisorId;
	if (getPersonIndex(id) != -1 || getPersonIndex(supervisorId) == -1)
	{
		cout << "Error! Either Employee Id already taken or Supervisor Id does not exist" << endl;
	}
	else
	{
		Employee* newEmp = new Employee(name, id, password, supervisorId,15,21, getSuperVisor(supervisorId),director);
		persons.push_back(newEmp);
		cout << "Employee added successfully" << endl;
	}
}

void PersonManager::addGuard()
{
	printAllPersons();
	string name;
	int id;
	string password;
	cout << "Enter Guard Name: ";
	cin >> name;
	cout << "Enter Guard ID: ";
	cin >> id;
	cout << "Enter Guard Password: ";
	cin >> password;
	if(getPersonIndex(id)!=-1)
	{
		cout << "Error! Id already in use" << endl;
	}
	else
	{
		Guard* guard = new Guard(name, id, password, this);
		persons.push_back(guard);
		cout << "Guard added successfully" << endl;
	}
}

void PersonManager::addSupervisor()
{
	printAllPersons();
	string name;
	int id;
	string password;
	cout << "Enter Supervisor Name: ";
	cin >> name;
	cout << "Enter Supervisor ID: ";
	cin >> id;
	cout << "Enter Supervisor Password: ";
	cin >> password;
	if (getPersonIndex(id) != -1)
	{
		cout << "Error! Id already in use" << endl;
	}
	else
	{
		Supervisor* sp = new Supervisor(name, id, password);
		persons.push_back(sp);
		cout << "Supervisor added successfully" << endl;
	}
}


vector<Person*> & PersonManager::getPersonList()
{
	return persons;
}


void PersonManager::printAllEmployees()
{
	cout << "List of All Employees" << endl;
	for (int i = 0; i < persons.size(); i++)
	{
		Employee* emp = dynamic_cast<Employee*>(persons[i]);
		if (emp != nullptr)
		{
			cout << "Name: " << emp->getName() << " ID: " << emp->getId() << endl;
		}
	}
}


void PersonManager::printAllPersons()
{
	cout << "List of All Persons" << endl;
	for (int i = 0; i < persons.size(); i++)
	{
		cout << "Name: " << persons[i]->getName() << " ID: " << persons[i]->getId() << endl;
		
	}
}

void PersonManager::printAllSupervisors()
{
	cout << "List of All Supervisors" << endl;
	for (int i = 0; i < persons.size(); i++)
	{
		Supervisor* sp = dynamic_cast<Supervisor*>(persons[i]);
		if (sp != nullptr)
		{
			cout << "Name: " << sp->getName() << " ID: " << sp->getId() << endl;
		}
	}
}