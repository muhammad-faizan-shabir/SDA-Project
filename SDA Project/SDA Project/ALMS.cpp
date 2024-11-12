#include <iostream>
#include <string>
#include <vector>
using namespace std;


enum class leaveType
{
	casual,
	earned,
	official,
	unpaid,
	none
};



class leaveApplication
{

protected:


	string employeeName;
	string employeeID;
	leaveType leave_type;
	string dateFrom;
	string dateTo;
	string leaveAddress;
	string applicationDate;
	bool status;
	string approvalDate;

	leaveApplication(string name, string id, leaveType leave, string from, string to, string address, string app_date, bool s, string apprvl_date)
		:	employeeName{name}, employeeID{id}, leave_type{leave}, dateFrom{from}, dateTo{to}, leaveAddress{address}, status{s}, approvalDate{apprvl_date}
	{

	}


};

class casualLeave : public leaveApplication
{
public:

	casualLeave(string name, string id, string from, string to, string address, string app_date, bool s, string apprvl_date)
		:leaveApplication{ name, id, leaveType::casual, from, to,  address, app_date, s, apprvl_date }
	{

	}
	



};

class earnedLeave : public leaveApplication
{
public:
	earnedLeave(string name, string id, string from, string to, string address, string app_date, bool s, string apprvl_date)
		:leaveApplication{ name, id, leaveType::earned, from, to,  address, app_date, s, apprvl_date }
	{

	}
	



};

class officialLeave : public leaveApplication
{
public:

	officialLeave(string name, string id, string from, string to, string address, string app_date, bool s, string apprvl_date)
		:leaveApplication{ name, id, leaveType::official, from, to,  address, app_date, s, apprvl_date }
	{

	}
	



};

class unpaidLeave : public leaveApplication
{
public:
	
	unpaidLeave(string name, string id, string from, string to, string address, string app_date, bool s, string apprvl_date)
		:leaveApplication{ name, id, leaveType::unpaid, from, to,  address, app_date, s, apprvl_date }
	{

	}
	
	


};



struct attendance
{
	bool presence;

	attendance(string d = "", int entime = 0, int extime = 0)
		: date{ d }, entryTime{ entime }, exitTime{ extime }, presence{ false }, leave{ leaveType::unpaid }
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




};


class supervisor : public person
{
public:
	supervisor(string n = "", string id1 = "", string pass = "")
		: person{ n, id1, pass }
	{

	}


private:

};

class director : public person
{
public:
	director(string n = "", string id1 = "", string pass = "")
		: person{ n, id1, pass }
	{

	}




};


class employee : public person
{

	int casualLeavesAvailable;
	int earnedLeavesAvailable;
	vector<attendance> attendance_record;

public:
	employee(string n = "", string id1 = "", string pass = "")
		: person{ n, id1, pass }, casualLeavesAvailable{ 15 }, earnedLeavesAvailable{ 21 }
	{

	}

};




int main()
{

}