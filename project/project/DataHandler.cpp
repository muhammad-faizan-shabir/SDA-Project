#include<iostream>
#include<string>
#include<fstream>
#include "PersonManager.h"
#include "Person.h"
#include "DataHandler.h"
#include "LeaveApplication.h"
#include "Constants.h"
#include "State.h"
using namespace std;


void saveData(PersonManager* personManager)
{
	saveGuards(personManager);
	saveSupervisors(personManager);
	saveEmployees(personManager);
	saveAttendance(personManager);
	saveLeaveApplications(personManager);
}


void saveGuards(PersonManager* personManager)
{
	ofstream outFile(GUARD, std::ios::trunc);
	if (!outFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	vector<Person*>& persons = personManager->getPersonList();
	for (int i = 0; i < persons.size(); i++)
	{
		Guard* guard = dynamic_cast<Guard*>(persons[i]);
		
		if (guard != nullptr)
		{
			outFile << guard->getName() << " " << guard->getId() << " " << guard->getPassword() << endl;
		}
	}

	outFile.close();
}

void saveSupervisors(PersonManager * personManager)
{
	ofstream outFile(SUPERVISOR, std::ios::trunc);
	if (!outFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	vector<Person*>& persons = personManager->getPersonList();
	for (int i = 0; i < persons.size(); i++)
	{
		Supervisor* sp = dynamic_cast<Supervisor*>(persons[i]);
		
		if (sp != nullptr)
		{
			outFile << sp->getName() << " " << sp->getId() << " " << sp->getPassword() << endl;
		}
	}

	outFile.close();
}

void saveEmployees(PersonManager * personManager)
{
	ofstream outFile(EMPLOYEE, std::ios::trunc);
	if (!outFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	vector<Person*>& persons = personManager->getPersonList();
	for (int i = 0; i < persons.size(); i++)
	{
		Employee * emp= dynamic_cast<Employee*>(persons[i]);
		if(emp!=nullptr)
		{
			outFile << emp->getName() << " " << emp->getId() << " " << emp->getPassword() << " " << emp->getCasualLeaves() << " " << emp->getEarnedLeaves() <<" " << emp->getSupervisorId() << endl;
		}
	}

	outFile.close();
}


void saveAttendance(PersonManager* personManager)
{
	ofstream outFile(ATTENDANCE, std::ios::trunc);
	if (!outFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	vector<Person*>& persons = personManager->getPersonList();
	for (int i = 0; i < persons.size(); i++)
	{
		Employee* emp = dynamic_cast<Employee*>(persons[i]);
		if (emp != nullptr)
		{
			vector<Attendance>& attendance = emp->getAttendanceList();
			for(int i=0;i<attendance.size();i++)
			{
				outFile << attendance[i].getDate() << " " << attendance[i].getHours() << " " << attendance[i].getEntryTime() << " " << attendance[i].getExitTime() << " " << attendance[i].getLeaveType() << " " << attendance[i].getemployeeId() << endl;
			}
		}
	}

	outFile.close();
}

void saveLeaveApplications(PersonManager* personManager)
{
	ofstream outFile(LEAVE, std::ios::trunc);
	if (!outFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	vector<Person*>& persons = personManager->getPersonList();
	for (int i = 0; i < persons.size(); i++)
	{
		Employee* emp = dynamic_cast<Employee*>(persons[i]);
		if (emp != nullptr)
		{
			vector<LeaveApplication*>& applications = emp->getApplicationList();
			for (int i = 0; i < applications.size(); i++)
			{
				outFile << applications[i]->getEmployeeName() << " " << applications[i]->getEmployeeId() << " " << applications[i]->getLeaveType() << " " << applications[i]->getDateFrom() << " " << applications[i]->getDateTo() << " " << applications[i]->getLeaveAddress() << " " << applications[i]->getReason() << " " << applications[i]->getApplicationDate() << " " << applications[i]->getStatus() << " " << applications[i]->getApprovalDate() << endl;
			}
		}
	}

	outFile.close();
}

void getDirectorCredentials(string& name, int& id, string& password)
{
	ifstream inFile(DIRECTOR);
	if (!inFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	string n;
	int i;
	string p;
	if(inFile >> n >> i >> p)
	{
		name = n;
		id = i;
		password = p;
	}
	else
	{
		cout << "Error! Data could not be read from director file!" << endl;
	}		

	inFile.close();
}


void getAdminCredentials(string& name, int& id, string& password)
{
	ifstream inFile(ADMIN);
	if (!inFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	string n;
	int i;
	string p;
	if (inFile >> n >> i >> p)
	{
		name = n;
		id = i;
		password = p;
	}
	else
	{
		cout << "Error! Data could not be read from admin file!" << endl;
	}

	inFile.close();
}

void loadData(PersonManager * personManager)
{
	loadGuards(personManager);
	loadSupervisors(personManager);
	loadEmployees(personManager);
	loadAttendance(personManager);
	loadLeaveApplications(personManager);
	sendLeaveApplications(personManager);
}


void loadGuards(PersonManager *personManager)
{
	ifstream inFile(GUARD);
	if (!inFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	string name;
	int id;
	string password;
	while(inFile>>name>>id>>password)
	{
		personManager->addPerson(new Guard(name, id, password, personManager));
	}

	inFile.close();
}

void loadSupervisors(PersonManager *personManager)
{
	ifstream inFile(SUPERVISOR);
	if (!inFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	string name;
	int id;
	string password;
	while (inFile >> name >> id >> password)
	{
		personManager->addPerson(new Supervisor(name, id, password));
	}

	inFile.close();
}


void loadEmployees(PersonManager *personManager)
{
	ifstream inFile(EMPLOYEE);
	if (!inFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	string name;
	int id;
	string password;
	int casualLeaves;
	int earnedLeaves;
	int supervisorId;
	while(inFile>>name>>id>>password>>casualLeaves>>earnedLeaves>>supervisorId)
	{
		personManager->addPerson(new Employee(name,id,password,supervisorId,casualLeaves,earnedLeaves, personManager->getSuperVisor(supervisorId), personManager->getDirector()));
	}

	inFile.close();
}


void loadAttendance(PersonManager* personManager)
{
	ifstream inFile(ATTENDANCE);
	if (!inFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	string date;
	float hours;
	string entryTime;
	string exitTime;
	string leaveType;
	int employeeId;
	while(inFile>>date>>hours>>entryTime>>exitTime>>leaveType>>employeeId)
	{
		Employee* emp = personManager->getEmployee(employeeId);
		emp->addAttendance(Attendance(date,hours,entryTime,exitTime,leaveType, employeeId));
	}
	
		
	inFile.close();
}

void loadLeaveApplications(PersonManager* personManager)
{
	ifstream inFile(LEAVE);
	if (!inFile)
	{
		cout << "Error opening the file!" << endl;
		return;
	}
	string name;
	int empId;
	string leaveType;
	string dateFrom;
	string dateTo;
	string leaveAddress;
	string reason;
	string applicationDate;
	string status;
	string approvalDate;
	while(inFile>>name>>empId>>leaveType>>dateFrom>>dateTo>>leaveAddress>>reason>>applicationDate>>status>>approvalDate)
	{
		Employee* emp = personManager->getEmployee(empId);
		if(leaveType==CASUAL_LEAVE)
		{
			CasualLeave* app = new CasualLeave(name, empId, leaveType, dateTo, dateFrom, leaveAddress, reason, applicationDate,status, emp);
			app->setApprovalDate(approvalDate);
			setState(app, status);
			emp->addApplication(app);
		}
		else if(leaveType==EARNED_LEAVE)
		{
			EarnedLeave* app = new EarnedLeave(name, empId, leaveType, dateTo, dateFrom, leaveAddress, reason, applicationDate, status, emp);
			app->setApprovalDate(approvalDate);
			setState(app, status);
			emp->addApplication(app);
		}
		else if(leaveType==OFFICIAL_LEAVE)
		{
			OfficialLeave* app = new OfficialLeave(name, empId, leaveType, dateTo, dateFrom, leaveAddress, reason, applicationDate, status, emp);
			app->setApprovalDate(approvalDate);
			setState(app, status);
			emp->addApplication(app);
		}
		else
		{
			UnpaidLeave* app = new UnpaidLeave(name, empId, leaveType, dateTo, dateFrom, leaveAddress, reason, applicationDate, status, emp);
			app->setApprovalDate(approvalDate);
			setState(app, status);
			emp->addApplication(app);
		}
	}
	inFile.close();
}

void setState(LeaveApplication * app,string status)
{
	if(status==PENDING_AT_SUPERVISOR_ONLY)
	{
		app->setState(PendingAtSupervisorOnly::getPendingAtSupervisorOnlyObj());
	}
	else if(status ==PENDING_AT_SUPERVISOR)
	{
		app->setState(PendingAtSupervisor::getPendingAtSupervisorObj());
	}
	else if(status==PENDING_AT_DIRECTOR)
	{
		app->setState(PendingAtDirector::getPendingAtDirectorObj());
	}
	else if(status == ACCEPTED)
	{
		app->setState(Accepted::getAcceptedObj());
	}
	else
	{
		app->setState(Rejected::getRejectedObj());
	}
}

void sendLeaveApplications(PersonManager * personManager)
{
	vector<Person*>& persons = personManager->getPersonList();

	for(int i=0;i<persons.size();i++)
	{
		Employee* emp = dynamic_cast<Employee*>(persons[i]);
		if(emp!=nullptr)
		{
			emp->sendLeaveApplications();
		}
	}
}