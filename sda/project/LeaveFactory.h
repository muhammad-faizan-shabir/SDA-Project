#pragma once
#include<string>
class Employee;
class LeaveApplication;
using namespace std;

class LeaveFactory
{
public:
	virtual LeaveApplication * createLeave(Employee * emp) = 0;
	void getLeaveDetails(string& dateFrom, string& dateTo, string& LeaveAddress, string& reason, string& applicationDate);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CasualLeaveFactory : public LeaveFactory
{
public:
	 LeaveApplication* createLeave(Employee* emp);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EarnedLeaveFactory : public LeaveFactory
{
public:
	LeaveApplication* createLeave(Employee* emp);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OfficialLeaveFactory : public LeaveFactory 
{
public:
	LeaveApplication* createLeave(Employee* emp);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UnpaidLeaveFactory : public LeaveFactory
{
	LeaveApplication* createLeave(Employee* emp);
};
