#pragma once

void loadData(PersonManager * personManager);

void saveData(PersonManager* personManager);
void getDirectorCredentials(string &name, int &id,string & password);
void getAdminCredentials(string &name, int &id, string&password);
void saveGuards(PersonManager* personManager);
void saveSupervisors(PersonManager* personManager);
void saveEmployees(PersonManager* personManager);
void saveAttendance(PersonManager* personManager);
void saveLeaveApplications(PersonManager* personManager);
void loadGuards(PersonManager* personManager);
void loadSupervisors(PersonManager* personManager);
void loadEmployees(PersonManager* personManager);
void loadAttendance(PersonManager* personManager);
void loadLeaveApplications(PersonManager* personManager);
void sendLeaveApplications(PersonManager* personManager);
void setState(LeaveApplication* app, string status);