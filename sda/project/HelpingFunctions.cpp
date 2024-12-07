#include<iostream>
#include <sstream>
#include <unordered_map>
#include "HelpingFunctions.h"
using namespace std;
#pragma warning(disable : 4996)

// Function to extract day, month, and year from the date string
void extractDateComponents(const std::string& date, int& day, int& month, int& year) {
	// Using substring to extract day, month, and year from the date string
	day = std::stoi(date.substr(0, 2));      // Extract the day
	month = std::stoi(date.substr(3, 2));    // Extract the month
	year = std::stoi(date.substr(6, 4));     // Extract the year
}

// Function to calculate the approximate total days from a date
int calculateDays(int day, int month, int year) {
	return (year * 365) + (month * 30) + day;
}

// Function to calculate the difference between two dates
int estimateDifferenceInDays(const std::string& date1, const std::string& date2) {
	// Extract day, month, and year from both dates
	int day1, month1, year1;
	int day2, month2, year2;

	extractDateComponents(date1, day1, month1, year1);
	extractDateComponents(date2, day2, month2, year2);

	// Calculate total days for both dates
	int days1 = calculateDays(day1, month1, year1);
	int days2 = calculateDays(day2, month2, year2);

	// Return the absolute difference in days
	return std::abs(days1 - days2) + 1;
}


// Function to check if a given year is a leap year
bool isLeapYear(int year) {
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Function to validate if the given date is within the year 2024
bool isValidDateIn2024(const std::string& date) {
	int day, month, year;
	extractDateComponents(date, day, month, year);

	// Check if the year is 2024
	if (year != 2024) {
		return false;
	}

	// Define the number of days in each month for 2024
	std::unordered_map<int, int> daysInMonth = {
		{1, 31}, {2, isLeapYear(2024) ? 29 : 28}, {3, 31}, {4, 30},
		{5, 31}, {6, 30}, {7, 31}, {8, 31}, {9, 30}, {10, 31},
		{11, 30}, {12, 31}
	};

	// Check if the month is valid
	if (month < 1 || month > 12) {
		return false;
	}

	// Check if the day is valid for the given month
	if (day < 1 || day > daysInMonth[month]) {
		return false;
	}

	return true;
}

int daysInMonth(int month, int year) {
	// Days in each month for a non-leap year
	std::vector<int> daysInEachMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// Adjust February days for leap years
	if (month == 2 && isLeapYear(year)) {
		return 29;
	}
	return daysInEachMonth[month - 1];
}

std::string getNextDate(const std::string& date) {
	// Extract day, month, year from the input date string (DD:MM:YYYY)
	int day, month, year;
	std::sscanf(date.c_str(), "%d:%d:%d", &day, &month, &year);

	// Increment the day
	day++;

	// Check if the day exceeds the number of days in the current month
	if (day > daysInMonth(month, year)) {
		day = 1;
		month++;

		// Check if the month exceeds December (12), then reset to January and increment the year
		if (month > 12) {
			month = 1;
			year++;
		}
	}

	// Format the new date as a string "DD:MM:YYYY"
	char nextDate[11];
	std::sprintf(nextDate, "%02d:%02d:%04d", day, month, year);

	return std::string(nextDate);
}