#pragma once
#include<vector>
#include<string>

class PersonManagerInterface1;
class ReportGenerator;
class LeaveApplication;
class PersonManagerInterface2;
class PersonManager;
using namespace std;

class Person
{
protected:
	int objId;
	string name;
	int id;
	string loginPassword;
public:
	Person(string n, int i, string p);
	int getId();
	string getName();
	string getPassword();
	bool matchCredentials(int Id, string password);
	virtual void userInterface() = 0;
	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Admin : public Person
{
	PersonManager* interface;
	ReportGenerator* reportGenerator;
public:
	Admin(string name, int id, string password, PersonManager* interface, ReportGenerator* reportGenerator);
	void userInterface();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Supervisor : public Person
{
	vector<LeaveApplication*> applications;
public:
	Supervisor(string n, int id, string p);
	void userInterface();
	void addLeaveApplication(LeaveApplication* app);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Director : public Person
{
	vector<LeaveApplication*> applications;
public:
	Director(string n, int id, string p);
	void userInterface();
	void addLeaveApplication(LeaveApplication* app);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Attendance
{
	int empolyeeId;
	string date;
	float hoursWorked;
	string entryTime;
	string exitTime;
	string leaveType;

public:
	Attendance(string date,string entryTime,int empId);
	Attendance(string date,float hrs,string entryTime,string exitTime,string leaveType,int empId);
	void printAttendanceDetails();
	float getHours();
	string getMonth();
	void setExitTime(string entryTime);
	string getDate();
	string getEntryTime();
	string getExitTime();
	string getLeaveType();
	int getemployeeId();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Employee : public Person
{
protected:
	int casualLeavesAvailable;
	int earnedLeavesAvailable;
	vector<Attendance> attendance;
	vector<LeaveApplication*> applications;
	Supervisor* superVisor;
	Director* director;
	int supervisorId;
public:
	Employee(string n, int id, string p,int supervisorId, int casualLeaves, int earnedLeaves, Supervisor* sp, Director* d);
	void userInterface();
	bool addEntryRecord(string entryTime, string date);
	bool addExitRecord(string exitTime, string date);
	float computeAttendacePercentage(string month);
	bool isAnyApplicationPending();
	void printAttendanceDetails();
	void printLeaveApplicationDetails();
	Supervisor* getSupervisor();
	Director* getDirector();
	int getCasualLeaves();
	int getEarnedLeaves();
	void addAttendance(Attendance at);
	void decrementCasualLeaves(int n);
	void decrementEarnedLeaves(int n);
	int getSupervisorId();
	vector<Attendance>& getAttendanceList();
	vector<LeaveApplication*>& getApplicationList();
	void addApplication(LeaveApplication * app);
	void sendLeaveApplications();
	~Employee();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Guard : public Person
{
	PersonManager* personInterface;
	bool addEntryTime(int id, string entryTime, string date);
	bool addExitTime(int id, string exitTime, string date);
public:
	Guard(string name,int id,string password,PersonManager * interface);
	void userInterface();
};


