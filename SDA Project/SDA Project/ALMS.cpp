#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Date.h"
using namespace std;

class leaveApplication; // Forward declaration
class PendingState;
class ApprovedState;
class RejectedState;

enum class leaveType
{
	casual,
	earned,
	official,
	unpaid,
	none
};



class LeaveState {
public:
	virtual void approve(leaveApplication* leave) = 0;
	virtual void reject(leaveApplication* leave) = 0;
	virtual string getStatus() const = 0;
	
};

class PendingState : public LeaveState {
public:
	void approve(leaveApplication* leave) override;
	void reject(leaveApplication* leave) override;
	string getStatus() const override {
		return "Pending";
	}
};

class ApprovedState : public LeaveState {
public:
	void approve(leaveApplication* leave) override {
		cout << "Already approved\n";
	}

	void reject(leaveApplication* leave) override {
		cout << "Cannot reject an already approved leave\n";
	}

	string getStatus() const override {
		return "Approved";
	}
};

class RejectedState : public LeaveState {
public:
	void approve(leaveApplication* leave) override {
		cout << "Cannot approve a rejected leave\n";
	}

	void reject(leaveApplication* leave) override {
		cout << "Already rejected\n";
	}

	string getStatus() const override {
		return "Rejected";
	}
};

class leaveApplication
{

	friend class supervisor;
	friend class director;
	friend class SupervisorApprovalStrategy;
	friend class DirectorApprovalStrategy;
	friend class LeaveState;
	friend class PendingState;
	friend class ApprovedState;
	friend class RejectedState;


protected:

	LeaveState* currentState;

	string employeeName;
	string employeeID;
	leaveType leave_type;
	string dateFrom;
	string dateTo;
	string leaveAddress;
	string applicationDate;
	string reason;
	string approvalDate;
	int days;

	leaveApplication(string name, string id, leaveType leave, string from, string to, int d, string address, string reasn, string app_date = "", string apprvl_date = "")
		: employeeName{ name }, employeeID{ id }, leave_type{ leave }, dateFrom{ from }, dateTo{ to }, days{ d }, leaveAddress{ address }, reason{ reasn }, approvalDate{ apprvl_date }, currentState{new PendingState()}
	{
		
	}


	void setState(LeaveState* state) {
		currentState = state;
	}

	void approve() {
		currentState->approve(this);
	}

	void reject() {
		currentState->reject(this);
	}

public:

	virtual string getFrom() = 0;
	virtual string getTo() = 0;
	virtual int getDays() = 0;
	virtual leaveType getLeaveType() = 0;



	string getStatus() {
		return currentState->getStatus();
	}

	~leaveApplication() {
		delete currentState;  // Clean up allocated state memory
	}

};

class LeaveApprovalStrategy
{
protected:

	virtual bool approve(leaveApplication* leave) = 0;

};

class SupervisorApprovalStrategy : public LeaveApprovalStrategy
{

public:

	bool approve(leaveApplication* leave) {
		
		if (leave->leave_type==leaveType::earned || leave->leave_type==leaveType::official)
		{
			leave->approve();

			return true;
		}
	}

	bool reject(leaveApplication* leave) {
		
		if (leave->leave_type == leaveType::earned)
		{
			leave->reject();

			return false;
		}
	}

};

class DirectorApprovalStrategy : public LeaveApprovalStrategy
{

public:

	bool approve(leaveApplication* leave) {

		if (leave->leave_type == leaveType::unpaid)
		{
			leave->approve();

			return true;
		}
	}

	bool reject(leaveApplication* leave) {

		if (leave->leave_type == leaveType::unpaid)
		{
			leave->reject();

			return false;
		}

	}
};



class casualLeave : public leaveApplication
{
public:

	casualLeave(string name, string id, string from, string to, int days, string address, string reason, string app_date = "", string apprvl_date = "")
		:leaveApplication{ name, id, leaveType::casual, from, to, days  ,address, reason, app_date, apprvl_date }
	{

	}

	string getFrom()
	{
		return dateFrom;
	}

	string getTo()
	{
		return dateTo;
	}

	int getDays()
	{
		return days;
	}

	leaveType getLeaveType()
	{
		return leave_type;
	}

};

class earnedLeave : public leaveApplication
{
public:
	earnedLeave(string name, string id, string from, string to, int d, string address, string reason, string app_date = "", string apprvl_date = "")
		:leaveApplication{ name, id, leaveType::earned, from, to,d ,  address, reason, app_date, apprvl_date }
	{

	}

	string getFrom()
	{
		return dateFrom;
	}

	string getTo()
	{
		return dateTo;
	}

	int getDays()
	{
		return days;
	}

	leaveType getLeaveType()
	{
		return leave_type;
	}
};

class officialLeave : public leaveApplication
{
public:

	officialLeave(string name, string id, string from, string to, int days, string address, string reason, string app_date = "", string apprvl_date = "")
		:leaveApplication{ name, id, leaveType::official, from, to, days,  address, reason, app_date, apprvl_date }
	{

	}

	string getFrom()
	{
		return dateFrom;
	}

	string getTo()
	{
		return dateTo;
	}

	int getDays()
	{
		return days;
	}

	leaveType getLeaveType()
	{
		return leave_type;
	}
};

class unpaidLeave : public leaveApplication
{
public:

	unpaidLeave(string name, string id, string from, string to, int days, string address, string reason, string app_date = "", string apprvl_date = "")
		:leaveApplication{ name, id, leaveType::unpaid, from, to, days , address, reason, app_date, apprvl_date }
	{

	}

	string getFrom()
	{
		return dateFrom;
	}

	string getTo()
	{
		return dateTo;
	}

	int getDays()
	{
		return days;
	}

	leaveType getLeaveType()
	{
		return leave_type;
	}


};



struct attendance
{
	bool presence;
	string id;

	attendance(string id1, string d = "", int entime = 0, int extime = 0, bool p = false)
		: id{ id1 }, date{ d }, entryTime{ entime }, exitTime{ extime }, presence{ p }, leave{ leaveType::none }
	{
		hoursWorked = exitTime - entryTime;
	}

private:

	string date;
	int entryTime;
	int exitTime;
	int hoursWorked;
	leaveType leave;

};




class person
{

protected:

	string name;
	string id;
	string loginPassword;

	person(string n = "", string id1 = "", string pass = "")
		: name{ n }, id{ id1 }, loginPassword{ pass }
	{

	}

};


class guard : public person
{
public:
	guard(string n = "", string id1 = "", string pass = "")
		: person{ n, id1, pass }
	{

	}

	attendance add_attendance(string id1, string date, int entryTime, int exitTime, bool presence)
	{
		return attendance(id1, date, entryTime, exitTime, presence);
	}
};


class supervisor : public person
{

	SupervisorApprovalStrategy* strgy;

public:
	supervisor(string n = "", string id1 = "", string pass = "")
		: person{ n, id1, pass }, strgy{new SupervisorApprovalStrategy()}
	{

	}

	bool getApplication(leaveApplication* leave)
	{
		
			string choice; // press a to accept, press r to reject
			cin >> choice;
		
			if (choice=="a")
			{
				strgy->approve(leave);
				return true;
			}

			else
			{
				strgy->reject(leave);
				return false;
			}

	}

	~supervisor()
	{
		delete strgy;
	}


};

class director : public person
{

	DirectorApprovalStrategy* strgy;

public:
	director(string n = "", string id1 = "", string pass = "")
		: person{ n, id1, pass }, strgy{new DirectorApprovalStrategy}
	{

	}

	bool getApplication(leaveApplication* leave)
	{



		string choice; // press a to accept, press r to reject
		cin >> choice;

		if (choice == "a")
		{
			strgy->approve(leave);
		}

		else
		{
			strgy->reject(leave);
		}

	}


	~director()
	{
		delete strgy;
	}


};

class employee : public person
{

	int casualLeavesAvailable;
	int earnedLeavesAvailable;
	vector<attendance> attendance_record;
	supervisor sp;
	director dr;

public:
	employee(string n = "", string id1 = "", string pass = "")
		: person{ n, id1, pass }, casualLeavesAvailable{ 15 }, earnedLeavesAvailable{ 21 }
	{

	}

	void add_attendance(const attendance& a)
	{
		if (a.id == this->id)
		{
			attendance_record.push_back(a);
			cout << "Attendance for " << this->name << " added successfully\n";
		}

		else
		{
			cout << "Employee not found";
		}

	}

	string getName()
	{
		return name;
	}

	string getID()
	{
		return id;
	}

	leaveApplication* apply_leave(string from, string to, int days, string address, string reason)
	{

		if (reason != "official")
		{
			if (days <= 4)
			{
				if (casualLeavesAvailable < days)
				{
					cout << "Not enough leaves available" << endl;
					return nullptr;
				}

				casualLeavesAvailable -= days;
				return new casualLeave(name, id, from, to, days, address, reason);
			}

			else if (days > 4 && days <= 21)
			{

				if (earnedLeavesAvailable<days)
				{
					cout << "Not enough leaves available" << endl;
					return nullptr;
				}


				leaveApplication* la = new earnedLeave(name, id, from, to, days, address, reason);
				bool check = sp.getApplication(la);

				earnedLeavesAvailable = earnedLeavesAvailable - days;

				if (check == true)
				{

					
					return la;
				}

				else
				{
					delete la;
					return nullptr;
				}



			}
		}


		else
		{
			leaveApplication* ol = new officialLeave(name, id, from, to, days, address, reason);

			sp.getApplication(ol);

			return ol;

		}


	}

	



};




int main()
{
	employee kayan("Kayan", "1920", "helloworld");

	guard shabi;

	kayan.add_attendance(shabi.add_attendance("1920", "13-11-2024", 8, 13, true));

	auto leave = kayan.apply_leave("14-11-2024", "28-11-2024", 15, "Isl", "Checkup");
}

void PendingState::approve(leaveApplication* leave)
{
	leave->setState(new ApprovedState());
}

void PendingState::reject(leaveApplication* leave)
{
	leave->setState(new RejectedState());
}
