#pragma once

// Function to extract day, month, and year from the date string
void extractDateComponents(const std::string& date, int& day, int& month, int& year);
// Function to calculate the approximate total days from a date
int calculateDays(int day, int month, int year);

// Function to calculate the difference between two dates
int estimateDifferenceInDays(const std::string& date1, const std::string& date2);


// Function to check if a given year is a leap year
bool isLeapYear(int year);

// Function to validate if the given date is within the year 2024
bool isValidDateIn2024(const std::string& date);

int daysInMonth(int month, int year);

std::string getNextDate(const std::string& date);