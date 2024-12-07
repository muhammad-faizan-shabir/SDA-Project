#pragma once
#include<vector>
#include<string>
class Person;
class Employee;
class Supervisor;
class Director;
using namespace std;
class PersonManagerInterface1;
class PersonManagerInterface2;
class PersonManagerInterface3;


class PersonManager 
{
	vector<Person*> persons;
	Director* director;
	int getPersonIndex(int id);
public:
	Person* matchCredentials(int id, std::string password);
	PersonManager(Director* d);
	~PersonManager();
	Employee* getEmployee(int Id);
	void printAllEmployees();
	vector<Person*>& getPersonList();
	Supervisor* getSuperVisor(int Id);
	void addEmployee();
	void addGuard();
	void addSupervisor();
	void printAllPersons();
	void printAllSupervisors();
	void addPerson(Person* p);
	Director* getDirector();

};






