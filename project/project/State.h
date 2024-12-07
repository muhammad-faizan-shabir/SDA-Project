#pragma once
#include<string>
class LeaveApplication;
using namespace std;

class State
{
public:
	virtual void accept(LeaveApplication* app,string date)=0;
	virtual void reject(LeaveApplication* app)=0;

};

class PendingAtSupervisorOnly : public State
{
	static PendingAtSupervisorOnly* ptr;
	PendingAtSupervisorOnly();
	~PendingAtSupervisorOnly();
public:
	static PendingAtSupervisorOnly* getPendingAtSupervisorOnlyObj();
	static void deletePendingAtSupervisorOnlyObj();
	void accept(LeaveApplication* app, string date);
	void reject(LeaveApplication* app);
};

class PendingAtSupervisor: public State
{
	static PendingAtSupervisor* ptr;
	PendingAtSupervisor();
	~PendingAtSupervisor();
public:
	static PendingAtSupervisor* getPendingAtSupervisorObj();
	static void deletePendingAtSupervisorObj();
	void accept(LeaveApplication* app, string date);
	void reject(LeaveApplication* app);
};

class PendingAtDirector: public State
{
	static PendingAtDirector* ptr;
	PendingAtDirector();
	~PendingAtDirector();
public:
	static PendingAtDirector* getPendingAtDirectorObj();
	static void deletePendingAtDirectorObj();
	void accept(LeaveApplication* app, string date);
	void reject(LeaveApplication* app);
};

class Accepted: public State
{
	static Accepted* ptr;
	Accepted();
	~Accepted();
public:
	static Accepted* getAcceptedObj();
	static void deleteAcceptedObj();
	void accept(LeaveApplication* app, string date);
	void reject(LeaveApplication* app);
};

class Rejected: public State
{
	static Rejected* ptr;
	Rejected();
	~Rejected();
public:
	static Rejected* getRejectedObj();
	static void deleteRejectedObj();
	void accept(LeaveApplication* app, string date);
	void reject(LeaveApplication* app);
};