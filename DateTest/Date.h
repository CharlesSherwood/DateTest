#pragma once
// Date.h
// Date Class Declaration
// CSC 222 - Introduction to Classes Project

#ifndef DATE_H
#define DATE_H
using namespace std;

#include <string>

class Date
{
private:
    int month;
    int day;
    int year;

    // Private helper: reset to default date
    void setDefault();

public:
    // Constructor (default arguments = January 1, 1900)
    Date(int m = 1, int d = 1, int y = 1900);

    // Mutator
    void setDate(int m, int d, int y);

    // Accessors (inline)
    int getMonth() const { return month; }
    int getDay()   const { return day; }
    int getYear()  const { return year; }

    // Leap-year overloads
    bool isLeapYear() const;               // uses stored year
    bool isLeapYear(int y) const;          // uses provided year

    // Last-day-of-month overloads
    int lastDay() const;                   // uses stored month & year
    int lastDay(int m, int y) const;       // uses provided month & year

    // Print / output functions  (return  string)
    string printNumeric()      const; // 12/25/2021
    string printLongFormat()   const; // December 25, 2021
    string printInternational() const; // 25 December 2021
};

#endif // DATE_H