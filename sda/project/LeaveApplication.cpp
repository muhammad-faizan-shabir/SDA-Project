#include<iostream>
#include "LeaveApplication.h"
#include "Constants.h"
#include "Person.h"
#include "State.h"
#include "HelpingFunctions.h"
using namespace std;

LeaveApplication::LeaveApplication(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate,string status,Employee * emp)
{
	employeeName = name;
	employeeId = id;
	leaveType = lt;
	dateFrom = datefrom;
	dateTo = dateto;
	leaveAddress = leaveaddress;
	reason = r;
	applicationDate = appDate;
	this->status = status;
	approvalDate = NONE;
	this->emp = emp;
}

bool LeaveApplication::isPending()
{
	if(status!= REJECTED && status!=ACCEPTED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

string LeaveApplication::getEmployeeName()
{
	return employeeName;
}
string LeaveApplication::getLeaveType() 
{
	return leaveType;
}
string LeaveApplication::getDateTo()
{
	return dateTo;
}
string LeaveApplication::getDateFrom()
{
	return dateFrom;
}
string LeaveApplication::getLeaveAddress() 
{
	return leaveAddress;
}
string LeaveApplication::getReason()
{
	return reason;
}
string LeaveApplication::getApplicationDate() 
{
	return applicationDate;
}
string LeaveApplication::getStatus() 
{
	return status;
}
string LeaveApplication::getApprovalDate() 
{
	return approvalDate;
}

void LeaveApplication::printLeaveApplicationDetails()
{
	cout <<"EmpName: "<<employeeName<<", EmpId: "<<employeeId << ", Leave Type: " << leaveType << ", From: " << dateFrom << ", To: " << dateTo << ", leaveAddress: " << leaveAddress << ", reason: " << reason << "Application Date: " << applicationDate << ", status: " << status << ", Approval Date: " << approvalDate << endl;
}

int LeaveApplication::getEmployeeId()
{
	return employeeId;
}

void LeaveApplication::accept(string date)
{
	st->accept(this,date);
}

void LeaveApplication::updateEmployee()
{
	return;
}

void LeaveApplication::forwardToDirector()
{
	emp->getDirector()->addLeaveApplication(this);
}

void LeaveApplication::reject()
{
	st->reject(this);
}

void LeaveApplication::setStatus(string status)
{
	this->status = status;
}

void LeaveApplication::setApprovalDate(string date)
{
	approvalDate = date;
}

void LeaveApplication::setState(State * state)
{
	st = state;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CasualLeave::CasualLeave(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate, string status, Employee* emp) : LeaveApplication(name, id, lt, dateto, datefrom, leaveaddress, r, appDate,status, emp)
{
	st = PendingAtSupervisorOnly::getPendingAtSupervisorOnlyObj();
}

void CasualLeave::updateEmployee()
{
	int days = estimateDifferenceInDays(dateFrom,dateTo);
	string date = dateFrom;
	for(int i=0;i<days;i++)
	{
		emp->addAttendance(Attendance(date, 8, NONE, NONE,leaveType,emp->getId()));
		date = getNextDate(date);
	}
	emp->decrementCasualLeaves(days);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EarnedLeave::EarnedLeave(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate, string status, Employee* emp) : LeaveApplication(name, id, lt, dateto, datefrom, leaveaddress, r, appDate,status, emp)
{
	st = PendingAtSupervisor::getPendingAtSupervisorObj();
}

void EarnedLeave::updateEmployee()
{
	int days = estimateDifferenceInDays(dateFrom, dateTo);
	string date = dateFrom;
	for (int i = 0; i < days; i++)
	{
		emp->addAttendance(Attendance(date, 8, NONE, NONE, leaveType,emp->getId()));
		date = getNextDate(date);
	}
	emp->decrementEarnedLeaves(days);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

OfficialLeave::OfficialLeave(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate, string status, Employee* emp) : LeaveApplication(name, id, lt, dateto, datefrom, leaveaddress, r, appDate,status,emp)
{
	st = PendingAtSupervisorOnly::getPendingAtSupervisorOnlyObj();
}

void OfficialLeave::updateEmployee()
{
	emp->addAttendance(Attendance(dateTo,8,NONE,NONE,leaveType,emp->getId()));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UnpaidLeave::UnpaidLeave(string name, int id, string lt, string dateto, string datefrom, string leaveaddress, string r, string appDate, string status, Employee* emp) : LeaveApplication(name, id, lt, dateto, datefrom, leaveaddress, r, appDate,status,emp)
{
	st = PendingAtSupervisor::getPendingAtSupervisorObj();
}

void UnpaidLeave::updateEmployee()
{
	return;
}