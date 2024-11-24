#include<iostream>
#include<string>
#include<chrono>
#include<vector>
using namespace std;

class Main
{
	static Main* mainPtr;
	vector<Person*> persons;

	Main()
	{
	}
	~Main()
	{
		if (mainPtr != nullptr)
		{
			delete mainPtr;
		}
	}

	int getPersonIndex(int id)
	{
		for (int i = 0; i < persons.size(); i++)
		{
			if (persons[i]->getId() == id)
			{
				return i;
			}
		}
		return -1;
	}
public:
	static Main* getMainObj()
	{
		if (mainPtr == nullptr)
		{
			mainPtr = new Main();
		}
		return mainPtr;
	}

	void userInterface()
	{
		bool flag = true;

		while (flag == true)
		{
			cout << "Welcome to Attendance and Leave Management System" << endl;
			int choice = 0;
			cout << "Press 1 to Login" << endl;
			cout << "Press 2 to Quit" << endl;
			cin >> choice;
			if (choice == 1)
			{
				int Id = 0;
				string password;
				system("CLS");
				cout << "Login Screen" << endl;
				cout << "Enter ID: ";
				cin >> Id;
				cout << "Enter password: ";
				cin >> password;
				bool credentialsMatched = false;
				for (int i = 0; i < persons.size(); i++)
				{
					if (persons[i]->matchCredentials(Id, password) == true)
					{
						credentialsMatched = true;
						persons[i]->userInterface();
					}
				}
				if (credentialsMatched == false)
				{
					cout << "Invalid ID or Password" << endl;
				}
			}
			else if (choice == 2)
			{
				system("CLS");
				cout << "Good Bye!" << endl;
				flag = false;
			}
			else
			{
				cout << "Invalid Input! " << endl;
			}
		}

	}

	Employee* getEmployee(int Id)
	{
		for (int i = 0; i < persons.size(); i++)
		{
			if (persons[i]->getId() == Id && dynamic_cast<Employee*>(persons[i]) != nullptr)
			{
				return dynamic_cast<Employee*>(persons[i]);
			}
		}

		return nullptr;
	}

	Supervisor* getSuperVisor(int Id)
	{
		for (int i = 0; i < persons.size(); i++)
		{
			if (persons[i]->getId() == Id && dynamic_cast<Supervisor*>(persons[i]) != nullptr)
			{
				return dynamic_cast<Supervisor*>(persons[i]);
			}
		}

		return nullptr;
	}

	bool addEmployee(string name, int id, string loginPassword, int superVisorId)
	{
		if (getPersonIndex(id) != -1 or getPersonIndex(superVisorId) == -1)
		{
			return false;
		}
		else
		{
			Employee* newEmp = new Employee(name, id, loginPassword, getSuperVisor(superVisorId));
			persons.push_back(newEmp);
			return true;
		}
	}

	bool removeEmployee(int id)
	{
		Employee* emp = getEmployee(id);
		if (emp != nullptr)
		{
			int indexToBeDeleted = getPersonIndex(id);

			persons.erase(persons.begin() + indexToBeDeleted);
			return true;
		}
		else
		{
			return false;
		}
	}

	void generateReport1(string month, float percentage)
	{
		cout << "Employees whose attendance for Month: " << month << "is less than " << percentage << endl;
		for (int i = 0; i < persons.size(); i++)
		{
			int name;
			int id;
			if (dynamic_cast<Employee*>(persons[i]) != nullptr)
			{
				if ()
			}
		}
	}

	void generateReport2()
	{
	}

	void generateReport3(int id)
	{
	}

	void generateReport4(int id)
	{
	}

};
Main* Main::mainPtr = nullptr;

enum class LeaveType
{
	CausualLeave,
	EarnedLeave,
	OfficialLeave,
	UnpaidLeave,
	None
};

enum class Status
{
	PendingAtSupervisor,
	PendingAtDirector,
	Accepted,
	Rejected

};

class Person
{
protected:
	int objId;
	string name;
	int id;
	string loginPassword;
public:
	Person(string n, int i, string p)
	{
		name = n;
		id = i;
		loginPassword = p;
	}
	int getId()
	{
		return id;
	}
	bool matchCredentials(int Id, string password)
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
	virtual void userInterface() = 0;
};


class Guard : public Person
{
	bool addEntryTime(int id, string entryTime, string date)
	{
		Main* ptr = Main::getMainObj();
		Employee* emp = ptr->getEmployee(id);

		if (emp == nullptr)
		{
			return false;
		}
		else
		{
			return emp->addEntryRecord(entryTime, date);
		}
	}

	bool addExitTime(int id, string exitTime, string date)
	{
		Main* ptr = Main::getMainObj();
		Employee* emp = ptr->getEmployee(id);

		if (emp == nullptr)
		{
			return false;
		}
		else
		{
			return emp->addExitRecord(exitTime, date);
		}
	}


public:
	void userInterface()
	{
		bool flag = true;
		while (flag == true)
		{
			int choice = 0;
			system("CLS");
			cout << "Guard Interface" << endl;
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

				cout << "Enter employee id: ";
				cin >> id;
				cout << "Enter entryTime: ";
				cin >> entryTime;
				cout << "Enter date(YY-MM-DD): ";
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
				cout << "Enter employee id: ";
				cin >> id;
				cout << "Enter exitTime: ";
				cin >> exitTime;
				cout << "Enter date(YY-MM-DD): ";
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
};

class Admin : public Person
{
	void userInterface()
	{
		bool flag = true;

		while (flag == true)
		{
			int choice = 0;
			system("CLS");
			cout << "Admin Interface" << endl;
			cout << "Press 1 to add employee" << endl;
			cout << "Press 2 to remove employee" << endl;
			cout << "Press 3 to generate report 1" << endl;
			cout << "Press 4 to generate report 2" << endl;
			cout << "Press 5 to generate report 3" << endl;
			cout << "Press 6 to generate report 4" << endl;
			cout << "Press 7 to Logout" << endl;
			cin >> choice;
			if (choice == 1)
			{
				string name;
				int id;
				string password;
				int supervisorId;
				cout << "Enter employee name: ";
				cin >> name;
				cout << "Enter employee id: ";
				cin >> id;
				cout << "Set employee password: ";
				cin >> password;
				cout << "Enter Supervisor id: ";
				cin >> supervisorId;
				bool entrySuccessful = Main::getMainObj()->addEmployee(name, id, password, supervisorId);
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
				int id;
				cout << "Enter ID of the employee to be removed" << endl;
				cin >> id;
				bool removalSuccessful = Main::getMainObj()->removeEmployee(id);

				if (removalSuccessful == true)
				{
					cout << "Employee removed successfully!" << endl;
				}
				else
				{
					cout << "Error in removing employee!" << endl;
				}
			}
			else if (choice == 3)
			{
				string month;
				float percentage;
				cout << "Enter month: " << endl;
				cin >> month;
				cout << "Enter percentage: ";
				cin >> percentage;
				Main::getMainObj()->generateReport1(month, percentage);
			}
			else if (choice == 4)
			{
				Main::getMainObj()->generateReport2();
			}
			else if (choice == 5)
			{
				int id;
				cout << "Enter ID of the employee:  ";
				cin >> id;
				Main::getMainObj()->generateReport3(id);
			}
			else if (choice == 6)
			{
				int id;
				cout << "Enter ID of the employee: ";
				cin >> id;
				Main::getMainObj()->generateReport4(id);

			}
			else if (choice == 7)
			{
				flag = false;
			}
			else
			{
				cout << "Invalid input!" << endl;
			}
		}
	}
};

class Supervisor : public Person
{
	vector<LeaveApplication*> applications;
public:

	void userInterface()
	{
		bool flag = true;
		while (flag == true)
		{
			int choice;
			system("CLS");
			cout << "Supservisor Interface" << endl;
			cout << "Press 1 to View Employee Leave Applications" << endl;
			cout << "Press 2 to Approve/Reject Employee Leave Applications" << endl;
			cout << "Press 3 to Logout" << endl;
			cin >> choice;

			if (choice == 1)
			{
				cout << "Leave Application Log" << endl;
				for (int i = 0; i < applications.size(); i++)
				{
					applications[i]->printLeaveApplicationDetails();
				}
			}
			else if (choice == 2)
			{

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
	void addLeaveApplication(LeaveApplication* app)
	{
		applications.push_back(app);
	}


};

class Director : public Person
{
	vector<LeaveApplication*> applications;
public:
	void userInterface()
	{
		bool flag = true;
		while (flag == true)
		{
			int choice;
			system("CLS");
			cout << "Director Interface" << endl;
			cout << "Press 1 to View Employee Leave Applications" << endl;
			cout << "Press 2 to Approve/Reject Employee Leave Applications" << endl;
			cout << "Press 3 to Logout" << endl;
			cin >> choice;

			if (choice == 1)
			{
				cout << "Leave Application Log" << endl;
				for (int i = 0; i < applications.size(); i++)
				{
					applications[i]->printLeaveApplicationDetails();
				}
			}
			else if (choice == 2)
			{

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
};

class Employee : public Person
{
	int casualLeavesAvailable;
	int earnedLeavesAvailable;
	vector<Attendance> attendance;
	vector<LeaveApplication*> applications;
	Supervisor* superVisor;

	void getLeaveDetails(string& dateFrom, string& dateTo, string LeaveAddress, string reason, string applicationDate)
	{
		cout << "Enter date from(DD-MM-YYYY): ";
		cin >> dateFrom;
		cout << "Enter date to(DD-MM-YYYY): ";
		cin >> dateTo;
		cout << "Enter LeaveAddress: ";
		cin >> LeaveAddress;
		cout << "Enter reason for leave: " << endl;
		cin >> reason;
		cout << "Enter date of filing the application(DD-MM-YYYY): ";
		cin >> applicationDate;
	}

public:
	Employee(string n, int id, string p, Supervisor* sp = nullptr) : Person(n, id, p)
	{
		superVisor = sp;
		casualLeavesAvailable = 15;
		earnedLeavesAvailable = 21;
	}
	void userInterface()
	{
		bool flag = true;
		while (flag == true)
		{
			int choice = 0;
			system("CLS");
			cout << "Employee Interface" << endl;
			cout << "Press 1 to View Attendance" << endl;
			cout << "Press 2  to Apply for a Leave Application" << endl;
			cout << "Press 3 to Delete a Leave Application" << endl;
			cout << "Press 4 to View Leave Application Status" << endl;
			cout << "Press 5 to Logout" << endl;
			cin >> choice;
			if (choice == 1)
			{
				cout << "Attendance Log:" << endl;
				for (int i = 0; i < attendance.size(); i++)
				{
					attendance[i].printAttendanceDetails();
				}
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
						string dateFrom;
						string dateTo;
						string LeaveAddress;
						string reason;
						string applicationDate;
						getLeaveDetails(dateFrom, dateTo, LeaveAddress, reason, applicationDate);
						LeaveApplication* application = new CasualLeave(name, id, LeaveType::CausualLeave, dateFrom, dateTo, LeaveAddress, reason, applicationDate);
						applications.push_back(application);
						superVisor->addLeaveApplication(application);
						cout << "Casual Leave filed successfully!" << endl;

					}
				}
				else if (leavetype == 2)
				{
					string dateFrom;
					string dateTo;
					string LeaveAddress;
					string reason;
					string applicationDate;
					getLeaveDetails(dateFrom, dateTo, LeaveAddress, reason, applicationDate);
					LeaveApplication* application = new EarnedLeave(name, id, LeaveType::CausualLeave, dateFrom, dateTo, LeaveAddress, reason, applicationDate);
					applications.push_back(application);
					superVisor->addLeaveApplication(application);
					cout << "Earned Leave filed successfully!" << endl;
				}
				else if (leavetype == 3)
				{
					string dateFrom;
					string dateTo;
					string LeaveAddress;
					string reason;
					string applicationDate;
					getLeaveDetails(dateFrom, dateTo, LeaveAddress, reason, applicationDate);
					LeaveApplication* application = new OfficialLeave(name, id, LeaveType::CausualLeave, dateFrom, dateTo, LeaveAddress, reason, applicationDate);
					applications.push_back(application);
					superVisor->addLeaveApplication(application);
					cout << "Official Leave filed successfully!" << endl;
				}
				else if (leavetype == 4)
				{
					string dateFrom;
					string dateTo;
					string LeaveAddress;
					string reason;
					string applicationDate;
					getLeaveDetails(dateFrom, dateTo, LeaveAddress, reason, applicationDate);
					LeaveApplication* application = new UnpaidLeave(name, id, LeaveType::CausualLeave, dateFrom, dateTo, LeaveAddress, reason, applicationDate);
					applications.push_back(application);
					superVisor->addLeaveApplication(application);
					cout << "Unpaid Leave filed successfully!" << endl;
				}
				else
				{
					cout << "Invalid Input!" << endl;
				}
			}
			else if (choice == 3)
			{
			}
			else if (choice == 4)
			{
				cout << "Leave Application Log" << endl;
				for (int i = 0; i < applications.size(); i++)
				{
					applications[i]->printLeaveApplicationDetails();
				}
			}
			else if (choice == 5)
			{
				flag = false;
			}
			else
			{
				cout << "Invalid Input!" << endl;
			}


		}
	}
	bool addEntryRecord(string entryTime, string date)
	{
	}

	bool addExitRecord(string exitTime, string date)
	{
	}

	bool computeAttendacePercentage(string month, float percentage, string& name, int& id)
	{
		float hours = 0;
		for (int i = 0; i < attendance.size(); i++)
		{
			hours = hours + attendance[i].getHours(month);
		}

		float attendancePercentage = (hours / 160.0) * 100;
		if (attendancePercentage < percentage)
		{
			name = this->name;
			id = this->id;
			return true;
		}
		else
		{
			return false;
		}
	}
};

class LeaveApplication
{
	int objId;
	string employeeName;
	int employeeId;
	LeaveType leaveType;
	string dateFrom;
	string dateTo;
	string leaveAddress;
	string reason;
	string applicationDate;
	Status status;
	string approvalDate;

public:
	LeaveApplication(string name, int id, LeaveType lt, string dateto, string datefrom, string leaveaddress, string r, string appDate)
	{
		employeeName = name;
		employeeId = id;
		leaveType = lt;
		dateFrom = datefrom;
		dateTo = dateto;
		leaveAddress = leaveaddress;
		reason = r;
		applicationDate = appDate;
		status = Status::PendingAtSupervisor;
		approvalDate = "";
	}

	void printLeaveApplicationDetails()
	{

	}
};

class CasualLeave : public LeaveApplication
{
public:
	CasualLeave(string name, int id, LeaveType lt, string dateto, string datefrom, string leaveaddress, string r, string appDate) : LeaveApplication(name, id, lt, dateto, datefrom, leaveaddress, r, appDate)
	{

	}
};

class EarnedLeave : public LeaveApplication
{
public:
	EarnedLeave(string name, int id, LeaveType lt, string dateto, string datefrom, string leaveaddress, string r, string appDate) : LeaveApplication(name, id, lt, dateto, datefrom, leaveaddress, r, appDate)
	{
	}
};

class OfficialLeave :public LeaveApplication
{
public:
	OfficialLeave(string name, int id, LeaveType lt, string dateto, string datefrom, string leaveaddress, string r, string appDate) : LeaveApplication(name, id, lt, dateto, datefrom, leaveaddress, r, appDate)
	{
	}
};

class UnpaidLeave :public LeaveApplication
{
public:
	UnpaidLeave(string name, int id, LeaveType lt, string dateto, string datefrom, string leaveaddress, string r, string appDate) : LeaveApplication(name, id, lt, dateto, datefrom, leaveaddress, r, appDate)
	{
	}
};
class Attendance
{
	int objId;
	string date;
	int hoursWorked;
	string entryTime;
	string exitTime;
	LeaveType leaveType;
	char presence;

public:
	void printAttendanceDetails()
	{
	}

	float getHours(string month)
	{

	}
};




int main()
{
	Main* mainPtr = Main::getMainObj();
	mainPtr->userInterface();
}



