/* Date.cpp
* Date class implementation
* CSC 222 intro to classes project
*  
*/

#include"Date.h"
#include <sstream>
#include <iomanip>	
using namespace std;

//Private Helper
void Date::setDefault()
{
	month = 1;
	day = 1;
	year = 1900;
}

//Constructor 
Date::Date(int m, int d, int y)
{
	//VAlidate if any date is not right go to default 
	if (m < 1 || m>12 || y < 1)
	{
		setDefault();
		return;
	}
	int maxDay = lastDay(m, y);
	if (d<1 || d>maxDay)
	{
		setDefault();
		return;
	}
	month = m;
	day = d;
	year = y;
}


//Mutator 
void Date::setDate(int m, int d, int y)
{
	if (m < 1 || m > 12 || y < 1)
	{
		setDefault();
		return;
	}
	int maxDay = lastDay(m, y);
	if (d < 1 || d > maxDay)
	{
		setDefault();
		return;
	}
	month = m;
	day = d;
	year = y;
}
//LEap year overloads

bool Date::isLeapYear() const
{
	return isLeapYear(year);
}

bool Date::isLeapYear(int y) const
{
	// Leap year: divisible by 4, EXCEPT century years,
	// UNLESS also divisible by 400
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

//Last Day of the month overloads 
int Date::lastDay() const
{
	return lastDay(month, year);
}

int Date::lastDay(int m, int y) const
{
	switch (m)
	{
	case 1: case 3: case 5: case 7:
	case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return isLeapYear(y) ? 29 : 28;
	default:
		return 0; // invalid month
	}
}

//Returns full month name 
static string monthName(int m)
{
	static const char* names[] = {
		"", "January","February","March","April",
		"May","June","July","August",
		"September","October","November","December"
	};
	if (m < 1 || m > 12) return "Unknown";
	return names[m];
}

//Print/Output the dates

// 12/25/2021/example
string Date::printNumeric() const
{
	ostringstream oss;
	oss << month << "/" << day << "/" << year;
	return oss.str();
}

// December 25, 2021/example
string Date::printLongFormat() const
{
	ostringstream oss;
	oss << monthName(month) << " " << day << ", " << year;
	return oss.str();
}

// 25 December 2021/example
string Date::printInternational() const
{
	ostringstream oss;
	oss << day << " " << monthName(month) << " " << year;
	return oss.str();
}