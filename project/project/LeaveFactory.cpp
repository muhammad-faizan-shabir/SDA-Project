#include "LeaveFactory.h"
#include "LeaveApplication.h"
#include "Constants.h"
#include "Person.h"
#include "HelpingFunctions.h"

LeaveApplication* CasualLeaveFactory::createLeave(Employee* emp)
{
	string dateFrom;
	string dateTo;
	string LeaveAddress;
	string reason;
	string applicationDate;
	getLeaveDetails(dateFrom, dateTo, LeaveAddress, reason, applicationDate);
	if(isValidDateIn2024(dateTo)==true && isValidDateIn2024(dateFrom)==true && isValidDateIn2024(applicationDate)==true)
	{
		if(estimateDifferenceInDays(dateFrom,dateTo)<=4 && estimateDifferenceInDays(dateFrom, dateTo)<=emp->getCasualLeaves())
		{
			LeaveApplication* application = new CasualLeave(emp->getName(), emp->getId(), CASUAL_LEAVE, dateTo, dateFrom, LeaveAddress, reason, applicationDate,PENDING_AT_SUPERVISOR_ONLY, emp);
			return application;
		}
		else
		{
			cout << "Error! You cannot avail this amount of casual leaves" << endl;
			return nullptr;
		}
	}
	else
	{
		cout << "Error! Date must be within year 2024" << endl;
		return nullptr;
	}
}

void LeaveFactory::getLeaveDetails(string& dateFrom, string& dateTo, string& LeaveAddress, string& reason, string& applicationDate)
{
	cout << "Enter date from(DD-MM-YYYY): ";
	cin >> dateFrom;
	cout << "Enter date to(DD-MM-YYYY): ";
	cin >> dateTo;
	cout << "Enter LeaveAddress: ";
	cin >> LeaveAddress;
	cout << "Enter reason for leave: ";
	cin >> reason;
	cout << "Enter date of filing the application(DD-MM-YYYY): ";
	cin >> applicationDate;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LeaveApplication* EarnedLeaveFactory::createLeave(Employee* emp) 
{
	string dateFrom;
	string dateTo;
	string LeaveAddress;
	string reason;
	string applicationDate;
	getLeaveDetails(dateFrom, dateTo, LeaveAddress, reason, applicationDate);
	if (isValidDateIn2024(dateTo) == true && isValidDateIn2024(dateFrom)==true && isValidDateIn2024(applicationDate)==true)
	{
		if (estimateDifferenceInDays(dateFrom, dateTo) >4 && estimateDifferenceInDays(dateFrom, dateTo) <= emp->getEarnedLeaves())
		{
			LeaveApplication* application = new EarnedLeave(emp->getName(), emp->getId(), EARNED_LEAVE, dateTo, dateFrom, LeaveAddress, reason, applicationDate,PENDING_AT_SUPERVISOR, emp);
			return application;
		}
		else
		{
			cout << "Error! You cannot avail this amount of earned leaves" << endl;
			return nullptr;
		}
	}
	else
	{
		cout << "Error! Date must be within year 2024" << endl;
		return nullptr;
	}

	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LeaveApplication* OfficialLeaveFactory::createLeave(Employee* emp)
{
	string dateFrom;
	string dateTo;
	string LeaveAddress;
	string reason;
	string applicationDate;
	getLeaveDetails(dateFrom, dateTo, LeaveAddress, reason, applicationDate);
	if (isValidDateIn2024(dateTo) == true && isValidDateIn2024(dateFrom)==true && isValidDateIn2024(applicationDate)==true)
	{
		if(estimateDifferenceInDays(dateFrom, dateTo)<2)
		{
			LeaveApplication* application = new OfficialLeave(emp->getName(), emp->getId(), OFFICIAL_LEAVE, dateTo, dateFrom, LeaveAddress, reason, applicationDate,PENDING_AT_SUPERVISOR_ONLY, emp);
			return application;
		}
		else
		{
			cout << "Error! you can only avail one official leave at a time" << endl;
			return nullptr;
		}
		
	}
	else
	{
		cout << "Error! Date must be within year 2024" << endl;
		return nullptr;
	}
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LeaveApplication* UnpaidLeaveFactory::createLeave(Employee* emp)
{
	string dateFrom;
	string dateTo;
	string LeaveAddress;
	string reason;
	string applicationDate;
	getLeaveDetails(dateFrom, dateTo, LeaveAddress, reason, applicationDate);
	if(isValidDateIn2024(applicationDate)==true)
	{
		LeaveApplication* application = new UnpaidLeave(emp->getName(), emp->getId(), UNPAID_LEAVE,  dateTo,dateFrom, LeaveAddress, reason, applicationDate,PENDING_AT_SUPERVISOR, emp);
		return application;
	}
	else
	{
		cout << "Error! Application filing date not within 2024" << endl;
		return nullptr;
	}
	
}