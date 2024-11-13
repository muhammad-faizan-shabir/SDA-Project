#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


#pragma once
class Date
{
    int day, month, year;

    // Array to hold the number of days in each month (index 0 is ignored for simplicity)
    static const int daysInMonth[13];

    // Helper function to check if a year is a leap year
    bool isLeapYear(int year) const {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                return (year % 400 == 0);
            }
            return true;
        }
        return false;
    }

    // Get the number of days in a given month
    int getDaysInMonth(int month, int year) const {
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return daysInMonth[month];
    }

    // Helper to adjust date if day/month overflows
    void normalizeDate() {
        while (day > getDaysInMonth(month, year)) {
            day -= getDaysInMonth(month, year);
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        while (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day += getDaysInMonth(month, year);
        }
    }

public:
    // Constructor with day, month, and year
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {
        normalizeDate(); // Normalize the initial date
    }

    // Constructor from a string of format "dd-mm-yyyy"
    Date(const std::string& dateStr) {
        std::stringstream ss(dateStr);
        char delimiter;
        ss >> day >> delimiter >> month >> delimiter >> year;
        normalizeDate();
    }

    // Print the date in dd/mm/yyyy format
    void print() const {
        printf("%02d/%02d/%04d\n", day, month, year);
        std::cout << std::endl;
    }

    // Convert the date to a string in dd-mm-yyyy format
    std::string toString() const {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << day << "-"
            << std::setw(2) << std::setfill('0') << month << "-"
            << year;
        return ss.str();
    }

    // Overload the increment operator (prefix)
    Date& operator++() {
        day++;
        normalizeDate();
        return *this;
    }

    // Overload the increment operator (postfix)
    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }

    // Overload the decrement operator (prefix)
    Date& operator--() {
        day--;
        normalizeDate();
        return *this;
    }

    // Overload the decrement operator (postfix)
    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }

    // Add a number of days to the date
    Date& operator+=(int days) {
        day += days;
        normalizeDate();
        return *this;
    }

    // Subtract a number of days from the date
    Date& operator-=(int days) {
        day -= days;
        normalizeDate();
        return *this;
    }

    // Overload comparison operators
    bool operator==(const Date& other) const {
        return (day == other.day && month == other.month && year == other.year);
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator>(const Date& other) const {
        return other < *this;
    }

    bool operator<=(const Date& other) const {
        return !(other < *this);
    }

    bool operator>=(const Date& other) const {
        return !(*this < other);
    }
};