#pragma once
#include<vector>
#include "Person.h"

//interface for report generator
class PersonManagerInterface3
{
public:
	virtual vector<Person*> & getPersonList() = 0;
	virtual Employee* getEmployee(int Id) = 0;
	virtual void printAllEmployees() = 0;
	virtual ~PersonManagerInterface3() = default;
};