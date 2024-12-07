#include "State.h"
#include "Constants.h"
#include "LeaveApplication.h"

#include "Person.h"



void PendingAtSupervisorOnly::accept(LeaveApplication* app, string date)
{
	app->setStatus(ACCEPTED);
	app->setApprovalDate(date);
	app->setState(Accepted::getAcceptedObj());
	app->updateEmployee();
	

}
void PendingAtSupervisorOnly::reject(LeaveApplication* app)
{
	app->setStatus(REJECTED);
	app->setState(Rejected::getRejectedObj());
}
PendingAtSupervisorOnly::PendingAtSupervisorOnly()
{
}
PendingAtSupervisorOnly::~PendingAtSupervisorOnly()
{
}
PendingAtSupervisorOnly* PendingAtSupervisorOnly::ptr = nullptr;
PendingAtSupervisorOnly* PendingAtSupervisorOnly::getPendingAtSupervisorOnlyObj()
{
	if(ptr==nullptr)
	{
		ptr = new PendingAtSupervisorOnly;
	}
	return ptr;
}

void PendingAtSupervisorOnly::deletePendingAtSupervisorOnlyObj()
{
	if(ptr!=nullptr)
	{
		delete ptr;
	}
}


void PendingAtSupervisor::accept(LeaveApplication* app, string date)
{
	app->setStatus(PENDING_AT_DIRECTOR);
	app->setApprovalDate(date);
	app->setState(PendingAtDirector::getPendingAtDirectorObj());
	app->forwardToDirector();
}
void PendingAtSupervisor::reject(LeaveApplication* app)
{
	app->setStatus(REJECTED);
	app->setState(Rejected::getRejectedObj());
}
PendingAtSupervisor::PendingAtSupervisor()
{
}
PendingAtSupervisor::~PendingAtSupervisor()
{
}
PendingAtSupervisor* PendingAtSupervisor::ptr = nullptr;
PendingAtSupervisor* PendingAtSupervisor::getPendingAtSupervisorObj()
{
	if(ptr==nullptr)
	{
		ptr = new PendingAtSupervisor;
	}
	return ptr;
}
void PendingAtSupervisor::deletePendingAtSupervisorObj()
{
	if(ptr!=nullptr)
	{
		delete ptr;
	}
}

void PendingAtDirector::accept(LeaveApplication* app, string date)
{
	app->setStatus(ACCEPTED);
	app->setApprovalDate(date);
	app->setState(Accepted::getAcceptedObj());
	app->updateEmployee();
}
void PendingAtDirector::reject(LeaveApplication* app)
{
	app->setStatus(REJECTED);
	app->setState(Rejected::getRejectedObj());
}
PendingAtDirector::PendingAtDirector()
{
}
PendingAtDirector::~PendingAtDirector()
{
}
PendingAtDirector* PendingAtDirector::ptr = nullptr;
PendingAtDirector* PendingAtDirector::getPendingAtDirectorObj()
{
	if(ptr==nullptr)
	{
		ptr = new PendingAtDirector;
	}
	return ptr;
}
void PendingAtDirector::deletePendingAtDirectorObj()
{
	if(ptr!=nullptr)
	{
		delete ptr;
	}
}
void Accepted::accept(LeaveApplication* app, string date)
{
	return;
}
void Accepted::reject(LeaveApplication* app)
{
	return;
}
Accepted::Accepted()
{
}
Accepted::~Accepted()
{
}
Accepted* Accepted::ptr = nullptr;
Accepted* Accepted::getAcceptedObj()
{
	if(ptr==nullptr)
	{
		ptr = new Accepted;
	}
	return ptr;
}
void Accepted::deleteAcceptedObj()
{
	if(ptr!=nullptr)
	{
		delete ptr;
	}
}

void Rejected::accept(LeaveApplication* app, string date)
{
	return;
}
void Rejected::reject(LeaveApplication* app)
{
	return;
}

Rejected::Rejected()
{
}
Rejected::~Rejected()
{
}
Rejected* Rejected::ptr = nullptr;
Rejected* Rejected::getRejectedObj()
{
	if(ptr==nullptr)
	{
		ptr = new Rejected;
	}
	return ptr;
}

void Rejected::deleteRejectedObj()
{
	if(ptr!=nullptr)
	{
		delete ptr;
	}
}
