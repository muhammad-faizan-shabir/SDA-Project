#include <iostream>
#include <string>
using namespace std;


enum class leaveType
{
	casual,
	earned,
	official,
	unpaid,
	none
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
	string name;
	string id;
	string loginPassword;

protected:

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



public:
	employee(string n = "", string id1 = "", string pass = "")
		: person{ n, id1, pass }, casualLeavesAvailable{ 15 }, earnedLeavesAvailable{ 21 }
	{

	}

};




int main()
{

}