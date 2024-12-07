#pragma once
class PersonManager;

class ReportGenerator
{
	PersonManager* interface;
public:
	ReportGenerator(PersonManager* interface);
	void generateReport1();
	void generateReport2();
	void generateReport3();
	void generateReport4();
};


