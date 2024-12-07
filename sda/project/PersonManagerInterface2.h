#pragma once
#include<iostream>
#include "Person.h"
using namespace std;

// Interface for guard
class PersonManagerInterface2
{
public:
	virtual Employee* getEmployee(int Id) = 0;
	virtual void printAllEmployees() = 0;
	virtual ~PersonManagerInterface2() = default;
};