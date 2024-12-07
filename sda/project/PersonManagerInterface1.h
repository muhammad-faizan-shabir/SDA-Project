#pragma once
#include<iostream>
using namespace std;

// used by Admin
class PersonManagerInterface1
{
public:
	virtual void addEmployee() = 0;
	virtual void addGuard() = 0;
	virtual void addSupervisor() = 0;
	virtual ~PersonManagerInterface1() = default;
};