#include<iostream>
#include<string>
#include "Person.h"
#include "PersonManagerInterface1.h"
#include "PersonManagerInterface2.h"
#include "ReportGenerator.h"
#include "LeaveApplication.h"
#include "Constants.h"
#include "LeaveFactory.h"
#include "PersonManager.h"
using namespace std;

Person::Person(string n, int i, string p)
{
	name = n;
	id = i;
	loginPassword = p;
}

string Person::getPassword()
{
	return loginPassword;
}

int Person::getId()
{
	return id;
}

string Person::getName()
{
	return name;
}

bool Person::matchCredentials(int Id, string password)
{
	if (Id == id && password == loginPassword)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Admin::Admin(string name, int id, string password, PersonManager* interface, ReportGenerator* reportGenerator) : Person(name, id, password)
{
	this->interface = interface;
	this->reportGenerator = reportGenerator;
}

void Admin::userInterface()
{
	bool flag = true;

	while (flag == true)
	{
		int choice = 0;
		
		cout <<endl<< "Admin Interface" << endl;
		cout << "Press 1 to add employee" << endl;
		cout << "Press 2 to add guard" << endl;
		cout << "Press 3 to add a supervisor" << endl;
		cout << "Press 4 to generate report 1" << endl;
		cout << "Press 5 to generate report 2" << endl;
		cout << "Press 6 to generate report 3" << endl;
		cout << "Press 7 to generate report 4" << endl;
		cout << "Press 8 to Logout" << endl;
		cin >> choice;
		if (choice == 1)
		{
			interface->addEmployee();
		}
		else if (choice == 2)
		{
			interface->addGuard();
		}
		else if (choice == 3)
		{
			interface->addSupervisor();
		}
		else if (choice == 4)
		{
			reportGenerator->generateReport1();
		}
		else if (choice == 5)
		{
			reportGenerator->generateReport2();
		}
		else if (choice == 6)
		{
			reportGenerator->generateReport3();
		}
		else if (choice == 7)
		{
			reportGenerator->generateReport4();
		}
		else if (choice == 8)
		{
			flag = false;
		}
		else
		{
			cout << "Invalid input!" << endl;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Supervisor::userInterface()
{
	bool flag = true;
	while (flag == true)
	{
		int choice;
		
		cout<<endl << "Supservisor Interface" << endl;
		cout << "Press 1 to View Employee Leave Applications" << endl;
		cout << "Press 2 to Approve/Reject Employee Leave Applications" << endl;
		cout << "Press 3 to Logout" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "Leave Application Log" << endl;
			for (int i = 0; i < applications.size(); i++)
			{
				cout << i + 1 << ": ";
				applications[i]->printLeaveApplicationDetails();
			}
		}
		else if (choice == 2)
		{
			
			int no;
			cout << "Enter No of application: ";
			cin >> no;
			if (no>0 && no <= applications.size())
			{
				--no;
				int ch;
				cout << "Press 1 to approve" << endl;
				cout << "Press 2 to reject" << endl;
				cin >> ch;
				if (ch == 1)
				{
					string date;
					cout << "Enter date(DD-MM-YYYY): ";
					cin >> date;
					applications[no]->accept(date);
					cout << "Application Processed Successfully!" << endl;
				}
				else if (ch == 2)
				{
					applications[no]->reject();
					cout << "Application Processed Successfully!" << endl;
				}
				else
				{
					cout << "Invalid Input!" << endl;
				}
			}
			else
			{
				cout << "Error! Approval/rejection failed!" << endl;
			}
		}
		else if (choice == 3)
		{
			flag = false;
		}
		else
		{
			cout << "Invalid Input!" << endl;
		}
	}
}
void Supervisor::addLeaveApplication(LeaveApplication* app)
{
	applications.push_back(app);
}

Supervisor::Supervisor(string n,int id,string p):Person(n,id,p)
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Director::userInterface()
{
	bool flag = true;
	while (flag == true)
	{
		int choice;
		
		cout <<endl<< "Director Interface" << endl;
		cout << "Press 1 to View Employee Leave Applications" << endl;
		cout << "Press 2 to Approve/Reject Employee Leave Applications" << endl;
		cout << "Press 3 to Logout" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "Leave Application Log" << endl;
			for (int i = 0; i < applications.size(); i++)
			{
				cout << i+1<<": ";
				applications[i]->printLeaveApplicationDetails();
			}
		}
		else if (choice == 2)
		{
			int no;
			cout << "Enter No of application: ";
			cin >> no;
			if (no>0 && no<=applications.size())
			{
				--no;
				int ch;
				cout << "Press 1 to approve" << endl;
				cout << "Press 2 to reject" << endl;
				cin >> ch;
				if (ch == 1)
				{
					string date;
					cout << "Enter date(DD-MM-YYYY): ";
					cin >> date;
					applications[no]->accept(date);
					cout << "Application Processed Successfully!" << endl;
				}
				else if (ch == 2)
				{
					applications[no]->reject();
					cout << "Application Processed Successfully!" << endl;
				}
				else
				{
					cout << "Invalid Input!" << endl;
				}
			}
			else
			{
				cout << "Error! Approval/rejection failed!" << endl;
			}
		}
		else if (choice == 3)
		{
			flag = false;
		}
		else
		{
			cout << "Invalid Input!" << endl;
		}
	}
}

Director::Director(string n,int id,string p):Person(n,id,p)
{
}

void Director::addLeaveApplication(LeaveApplication * app)
{
	applications.push_back(app);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Attendance::Attendance(string date, string entryTime,int empId)
{
	this->empolyeeId = empId;
	this->date= date;
	hoursWorked = 0;
	this->entryTime = entryTime;
	exitTime = NONE;
	leaveType = NONE;
}

Attendance::Attendance(string date, float hrs, string entryTime, string exitTime, string leaveType,int empId)
{
	this->empolyeeId = empId;
	this->date = date;
	this->hoursWorked = hrs;
	this->entryTime = entryTime;
	this->exitTime = exitTime;
	this->leaveType = leaveType;
}
void Attendance::printAttendanceDetails()
{
	cout << "Date: " << date << ", Hours Worked: " << hoursWorked << ", Entry Time: " << entryTime << ", Exit Time: " << exitTime << ", LeaveType: " << leaveType << endl;
}

float Attendance::getHours()
{
	return hoursWorked;
}

string Attendance::getMonth()
{
	char digit1 = date[3];
	char digit2 = date[4];
	string result = string(1, digit1) + digit2;
	return  result;
}

void Attendance::setExitTime(string exitTime)
{
	this->exitTime = exitTime;
	int hours1 = std::stoi(entryTime.substr(0, 2));
	int minutes1 = std::stoi(entryTime.substr(3, 2));

	// Parse the hours and minutes from the second time
	int hours2 = std::stoi(exitTime.substr(0, 2));
	int minutes2 = std::stoi(exitTime.substr(3, 2));

	// Convert both times to total minutes
	int totalMinutes1 = hours1 * 60 + minutes1;
	int totalMinutes2 = hours2 * 60 + minutes2;

	// Calculate the absolute difference in minutes
	int differenceInMinutes = std::abs(totalMinutes1 - totalMinutes2);

	// Convert minutes to hours (with fractional part if needed)
	float differenceInHours = differenceInMinutes / float(60);
	hoursWorked = differenceInHours;
}

string Attendance::getDate()
{
	return date;
}
string Attendance::getEntryTime()
{
	return entryTime;
}
string Attendance::getExitTime()
{
	return exitTime;
}

string Attendance::getLeaveType()
{
	return leaveType;
}

int Attendance::getemployeeId()
{
	return empolyeeId;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Employee::Employee(string n, int id, string p,int supervisorId, int casualLeaves = 15, int earnedLeaves = 21, Supervisor* sp = nullptr, Director* d = nullptr) : Person(n, id, p)
{
	this->supervisorId = supervisorId;
	superVisor = sp;
	director = d;
	casualLeavesAvailable = casualLeaves;
	earnedLeavesAvailable = earnedLeaves;
}
void Employee::addAttendance(Attendance at)
{
	attendance.push_back(at);
}

void Employee::addApplication(LeaveApplication * app)
{
	applications.push_back(app);
}

void Employee::sendLeaveApplications()
{
	for(int i=0;i<applications.size();i++)
	{
		if(applications[i]->getLeaveType()==CASUAL_LEAVE || applications[i]->getLeaveType() == OFFICIAL_LEAVE)
		{
			superVisor->addLeaveApplication(applications[i]);
		}
		else
		{
			if(applications[i]->getStatus()==PENDING_AT_SUPERVISOR_ONLY || applications[i]->getStatus()==PENDING_AT_SUPERVISOR)
			{
				superVisor->addLeaveApplication(applications[i]);
			}
			else if(applications[i]->getStatus() == PENDING_AT_DIRECTOR || applications[i]->getStatus() == ACCEPTED)
			{
				superVisor->addLeaveApplication(applications[i]);
				director->addLeaveApplication(applications[i]);
			}
			else
			{
				if(applications[i]->getApprovalDate()==NONE)
				{
					superVisor->addLeaveApplication(applications[i]);
				}
				else
				{
					superVisor->addLeaveApplication(applications[i]);
					director->addLeaveApplication(applications[i]);
				}
			}
		}
	}
}

void Employee::userInterface()
{
	bool flag = true;
	while (flag == true)
	{
		int choice = 0;
		
		cout <<endl<< "Employee Interface" << endl;
		cout << "Press 1 to View Attendance" << endl;
		cout << "Press 2  to Apply for a Leave Application" << endl;
		cout << "Press 3 to View Leave Application Status" << endl;
		cout << "Press 4 to Logout" << endl;
		cin >> choice;
		if (choice == 1)
		{
			printAttendanceDetails();
		}
		else if (choice == 2)
		{
			int leavetype;
			cout << "Press 1 to Apply for Casual Leave" << endl;
			cout << "Press 2 to Apply for Earned Leave" << endl;
			cout << "Press 3 to Apply for Official Leave" << endl;
			cout << "Press 4 to Apply for Unpaid Leave" << endl;
			cin >> leavetype;
			if (leavetype == 1)
			{
				if (casualLeavesAvailable == 0)
				{
					cout << "Application Cannot be processed. All casual leaves availed!" << endl;
				}
				else
				{
					CasualLeaveFactory clf;
					LeaveFactory& leaveFactory = clf;
					LeaveApplication* app = leaveFactory.createLeave(this);
					if(app!=nullptr)
					{
						applications.push_back(app);
						superVisor->addLeaveApplication(app);
						cout << "Casual Leave filed successfully!" << endl;
					}				
					
				}
			}
			else if (leavetype == 2)
			{
				if(earnedLeavesAvailable==0)
				{
					cout << "Application Cannot be processed. All earned leaves availed!" << endl;
				}
				else
				{
					EarnedLeaveFactory elf;
					LeaveFactory& leaveFactory = elf;
					LeaveApplication* app = leaveFactory.createLeave(this);
					if(app!=nullptr)
					{
						applications.push_back(app);
						superVisor->addLeaveApplication(app);
						cout << "Earned Leave filed successfully!" << endl;
					}
					
				}
				
			}
			else if (leavetype == 3)
			{
				OfficialLeaveFactory olf;
				LeaveFactory& leaveFactory = olf;
				LeaveApplication* app = leaveFactory.createLeave(this);
				if(app!=nullptr)
				{
					applications.push_back(app);
					superVisor->addLeaveApplication(app);
					cout << "Official Leave filed successfully!" << endl;
				}
				
			}
			else if (leavetype == 4)
			{
				UnpaidLeaveFactory ulf;
				LeaveFactory& leaveFactory = ulf;
				LeaveApplication* app = leaveFactory.createLeave(this);
				if(app!=nullptr)
				{
					applications.push_back(app);
					superVisor->addLeaveApplication(app);
					cout << "Unpaid Leave filed successfully!" << endl;
				}
				
			}
			else
			{
				cout << "Invalid Input!" << endl;
			}
		}
		else if (choice == 3)
		{
			printLeaveApplicationDetails();
		}
		else if (choice == 4)
		{
			flag = false;
		}
		else
		{
			cout << "Invalid Input!" << endl;
		}


	}
}
void Employee::decrementCasualLeaves(int n)
{
	casualLeavesAvailable=casualLeavesAvailable-n;
}

int Employee::getSupervisorId()
{
	return supervisorId;
}
void Employee::decrementEarnedLeaves(int n)
{
	earnedLeavesAvailable=earnedLeavesAvailable-n;
}

vector<Attendance> & Employee::getAttendanceList()
{
	return attendance;
}

vector<LeaveApplication*>& Employee::getApplicationList()
{
	return applications;
}

bool Employee::addEntryRecord(string entryTime, string date)
{
	Attendance at(date, entryTime,this->id);
	attendance.push_back(at);
	return true;
}

bool Employee::addExitRecord(string exitTime, string date)
{
	for(int i=0;i<attendance.size();i++)
	{
		if(attendance[i].getDate()==date)
		{
			attendance[i].setExitTime(exitTime);
			return true;
		}
	}
	return false;
}

float Employee::computeAttendacePercentage(string month)
{
	float hours = 0;
	for (int i = 0; i < attendance.size(); i++)
	{
		if (month == attendance[i].getMonth())
		{
			hours = hours + attendance[i].getHours();
		}
	}

	float attendancePercentage = (hours / float(160)) * 100;
	return attendancePercentage;
}

bool Employee::isAnyApplicationPending()
{
	for(int i=0;i<applications.size();i++)
	{
		if(applications[i]->isPending()==true)
		{
			return true;
		}
	}
	return false;
}

void Employee::printAttendanceDetails()
{
	cout << "Attendance Log:" << endl;
	for (int i = 0; i < attendance.size(); i++)
	{
		cout << i + 1 << ": ";
		attendance[i].printAttendanceDetails();
	}
}

void Employee::printLeaveApplicationDetails()
{
	cout << "Leave Application Log" << endl;
	for (int i = 0; i < applications.size(); i++)
	{
		cout << i + 1 << ": ";
		applications[i]->printLeaveApplicationDetails();
	}
}

Supervisor * Employee::getSupervisor()
{
	return superVisor;
}

Director * Employee::getDirector()
{
	return director;
}

int Employee::getCasualLeaves()
{
	return casualLeavesAvailable;
}

int Employee::getEarnedLeaves()
{
	return earnedLeavesAvailable;
}

Employee::~Employee()
{
	for(int i=0;i<applications.size();i++)
	{
		delete applications[i];
		applications[i] = nullptr;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Guard::addEntryTime(int id, string entryTime, string date)
{
	Employee* emp = personInterface->getEmployee(id);

	if (emp == nullptr)
	{
		return false;
	}
	else
	{
		return emp->addEntryRecord(entryTime, date);
	}
}

bool Guard::addExitTime(int id, string exitTime, string date)
{
	Employee* emp = personInterface->getEmployee(id);

	if (emp == nullptr)
	{
		return false;
	}
	else
	{
		return emp->addExitRecord(exitTime, date);
	}
}

Guard::Guard(string name, int id, string password, PersonManager* interface) : Person(name, id, password)
{
	personInterface = interface;
}

void Guard::userInterface()
{
	bool flag = true;
	while (flag == true)
	{
		int choice = 0;
		
		cout<<endl << "Guard Interface" << endl;
		cout << "Press 1 for adding entry time of an employee" << endl;
		cout << "Press 2 for adding exit time of an employee" << endl;
		cout << "Press 3 to Logout" << endl;
		cin >> choice;

		int id = 0;
		string entryTime = "";
		string exitTime = "";
		string date = "";
		if (choice == 1)
		{
			personInterface->printAllEmployees();
			cout << "Enter employee id: ";
			cin >> id;
			cout << "Enter entryTime(HH:MM): ";
			cin >> entryTime;
			cout << "Enter date(DD-MM-YYYY): ";
			cin >> date;

			bool entrySuccessful = addEntryTime(id, entryTime, date);
			if (entrySuccessful == false)
			{
				cout << "Error! Entry not made." << endl;
			}
			else
			{
				cout << "Entry Successful!" << endl;
			}
		}
		else if (choice == 2)
		{
			personInterface->printAllEmployees();
			cout << "Enter employee id: ";
			cin >> id;
			cout << "Enter exitTime(HH:MM): ";
			cin >> exitTime;
			cout << "Enter date(DD-MM-YYYY): ";
			cin >> date;

			bool entrySuccesful = addExitTime(id, exitTime, date);
			if (entrySuccesful == false)
			{
				cout << "Error! Entry not made." << endl;
			}
			else
			{
				cout << "Entry Successful!" << endl;
			}
		}
		else if (choice == 3)
		{
			flag = false;
		}
		else
		{
			cout << "Invalid Input!" << endl;
		}
	}
}