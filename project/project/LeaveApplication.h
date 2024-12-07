#pragma once
#include<string>
class Employee;
class State;
using namespace std;

class LeaveApplication
{
protected:
	int objId;
	string employeeName;
	int employeeId;
	string leaveType;
	string dateFrom;
	string dateTo;
	string leaveAddress;
	string reason;
	string applicationDate;
	string status;
	string approvalDate;
	Employee* emp;
	State* st;
public:
	LeaveApplication(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate,string status,Employee * emp);
	void printLeaveApplicationDetails();
	void accept(string date);
	void reject();
	bool isPending();
	void setStatus(string status);
	void setApprovalDate(string date);
	void setState(State* state);
	virtual void updateEmployee();
	void forwardToDirector();
	int getEmployeeId();
	string getEmployeeName();
	string getLeaveType();
	string getDateTo();
	string getDateFrom();
	string getLeaveAddress();
	string getReason();
	string getApplicationDate();
	string getStatus();
	string getApprovalDate();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CasualLeave : public LeaveApplication
{
public:
	CasualLeave(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate,string status, Employee* emp);
	void updateEmployee();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EarnedLeave : public LeaveApplication
{
public:
	EarnedLeave(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate, string status, Employee* emp);
	void updateEmployee();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class OfficialLeave :public LeaveApplication
{
public:
	OfficialLeave(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate, string status, Employee* emp);
	void updateEmployee();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UnpaidLeave :public LeaveApplication
{
public:
	UnpaidLeave(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate, string status, Employee* emp);
	void updateEmployee();
};