// DateTest.cpp
// Date Class - Comprehensive Test Program
// CSC 222 - Introduction to Classes Project
//
// Covers every item in the Test Plan Checklist:
//   - Default constructor
//   - Valid parameterized constructor
//   - Invalid parameterized constructor (resets to default)
//   - setDate() valid and invalid
//   - isLeapYear() both overloads
//   - lastDay() both overloads
//   - Edge-case calendar validation
//   - All three print formats

#include <iostream>
#include <string>
#include "Date.h"

// -------------------------------------------------------
// Counters
// -------------------------------------------------------
static int testsPassed = 0;
static int testsFailed = 0;

// -------------------------------------------------------
// Assertion helpers
// -------------------------------------------------------
void checkBool(const std::string& label, bool expected, bool actual)
{
    std::string result = (expected == actual) ? "PASS" : "FAIL";
    if (expected == actual) ++testsPassed; else ++testsFailed;
    std::cout << "  [" << result << "] " << label
        << "  expected=" << (expected ? "true" : "false")
        << "  got=" << (actual ? "true" : "false") << "\n";
}

void checkInt(const std::string& label, int expected, int actual)
{
    std::string result = (expected == actual) ? "PASS" : "FAIL";
    if (expected == actual) ++testsPassed; else ++testsFailed;
    std::cout << "  [" << result << "] " << label
        << "  expected=" << expected
        << "  got=" << actual << "\n";
}

void checkStr(const std::string& label,
    const std::string& expected,
    const std::string& actual)
{
    std::string result = (expected == actual) ? "PASS" : "FAIL";
    if (expected == actual) ++testsPassed; else ++testsFailed;
    std::cout << "  [" << result << "] " << label
        << "\n         expected: " << expected
        << "\n         got     : " << actual << "\n";
}

void section(const std::string& title)
{
    std::cout << "\n--------------------------------------------------\n";
    std::cout << " " << title << "\n";
    std::cout << "--------------------------------------------------\n";
}

// -------------------------------------------------------
// Test groups
// -------------------------------------------------------

void testDefaultConstructor()
{
    section("1. Default Constructor");
    Date d;
    checkInt("month == 1", 1, d.getMonth());
    checkInt("day   == 1", 1, d.getDay());
    checkInt("year  == 1900", 1900, d.getYear());
    checkStr("Numeric", "1/1/1900", d.printNumeric());
    checkStr("Long format", "January 1, 1900", d.printLongFormat());
    checkStr("International", "1 January 1900", d.printInternational());
}

void testValidConstructor()
{
    section("2. Valid Parameterized Constructor");

    // 12/25/2021
    {
        Date d(12, 25, 2021);
        checkInt("12/25/2021 - month", 12, d.getMonth());
        checkInt("12/25/2021 - day", 25, d.getDay());
        checkInt("12/25/2021 - year", 2021, d.getYear());
        checkStr("Numeric", "12/25/2021", d.printNumeric());
        checkStr("Long format", "December 25, 2021", d.printLongFormat());
        checkStr("International", "25 December 2021", d.printInternational());
    }

    // 1/1/1900
    {
        Date d(1, 1, 1900);
        checkInt("1/1/1900 - month", 1, d.getMonth());
        checkInt("1/1/1900 - day", 1, d.getDay());
        checkInt("1/1/1900 - year", 1900, d.getYear());
    }

    // 2/14/2022
    {
        Date d(2, 14, 2022);
        checkInt("2/14/2022 - month", 2, d.getMonth());
        checkInt("2/14/2022 - day", 14, d.getDay());
        checkInt("2/14/2022 - year", 2022, d.getYear());
    }
}

void testInvalidConstructor()
{
    section("3. Invalid Parameterized Constructor (resets to 1/1/1900)");

    // Invalid month: 0
    {
        Date d(0, 15, 2021);
        checkInt("month=0  -> month default", 1, d.getMonth());
        checkInt("month=0  -> day   default", 1, d.getDay());
        checkInt("month=0  -> year  default", 1900, d.getYear());
    }

    // Invalid month: 13
    {
        Date d(13, 15, 2021);
        checkInt("month=13 -> month default", 1, d.getMonth());
    }

    // Invalid day: 0
    {
        Date d(5, 0, 2021);
        checkInt("day=0    -> day   default", 1, d.getDay());
    }

    // Invalid day: 32 in January
    {
        Date d(1, 32, 2021);
        checkInt("day=32 (Jan) -> default", 1, d.getMonth());
    }

    // Invalid year: 0
    {
        Date d(6, 15, 0);
        checkInt("year=0   -> year  default", 1900, d.getYear());
    }
}

void testSetDate()
{
    section("4. setDate() Mutator");

    // Valid update
    Date d(1, 1, 2000);
    d.setDate(7, 4, 1776);
    checkInt("valid setDate - month", 7, d.getMonth());
    checkInt("valid setDate - day", 4, d.getDay());
    checkInt("valid setDate - year", 1776, d.getYear());

    // Invalid month -> reset
    d.setDate(13, 1, 2021);
    checkInt("setDate month=13 -> default month", 1, d.getMonth());
    checkInt("setDate month=13 -> default year", 1900, d.getYear());

    // Invalid day -> reset
    d.setDate(4, 31, 2021);  // April has only 30 days
    checkInt("setDate April 31 -> default", 1, d.getMonth());

    // Invalid day: Feb 30
    d.setDate(2, 30, 2020);
    checkInt("setDate Feb 30 -> default", 1, d.getMonth());

    // Verify getters after invalid set
    checkInt("getMonth() after invalid set", 1, d.getMonth());
    checkInt("getDay()   after invalid set", 1, d.getDay());
    checkInt("getYear()  after invalid set", 1900, d.getYear());
}

void testLeapYear()
{
    section("5. isLeapYear() - Both Overloads");

    Date d(1, 1, 2024);   // stored year = 2024 (leap)

    // No-argument overload
    checkBool("2024 isLeapYear() - no arg", true, d.isLeapYear());

    // Explicit-year overload
    checkBool("2024 isLeapYear(2024)", true, d.isLeapYear(2024));
    checkBool("2023 isLeapYear(2023) - false", false, d.isLeapYear(2023));
    checkBool("1900 isLeapYear(1900) - false", false, d.isLeapYear(1900));
    checkBool("2000 isLeapYear(2000) - true", true, d.isLeapYear(2000));
    checkBool("1800 isLeapYear(1800) - false", false, d.isLeapYear(1800));
    checkBool("1600 isLeapYear(1600) - true", true, d.isLeapYear(1600));
}

void testLastDay()
{
    section("6. lastDay() - Both Overloads");

    Date d(1, 1, 2023);  // January, non-leap year

    // No-argument overload
    checkInt("January lastDay() - no arg", 31, d.lastDay());

    // Explicit overload
    checkInt("lastDay(1,  2023) Jan = 31", 31, d.lastDay(1, 2023));
    checkInt("lastDay(4,  2023) Apr = 30", 30, d.lastDay(4, 2023));
    checkInt("lastDay(2,  2023) Feb non-leap = 28", 28, d.lastDay(2, 2023));
    checkInt("lastDay(2,  2024) Feb leap     = 29", 29, d.lastDay(2, 2024));
    checkInt("lastDay(12, 2023) Dec = 31", 31, d.lastDay(12, 2023));
}

void testEdgeCases()
{
    section("7. Edge-Case Calendar Validation");

    // 4/30 valid
    {
        Date d(4, 30, 2021);
        checkInt("4/30 valid - month", 4, d.getMonth());
        checkInt("4/30 valid - day", 30, d.getDay());
    }

    // 4/31 invalid
    {
        Date d(4, 31, 2021);
        checkInt("4/31 invalid -> default month", 1, d.getMonth());
    }

    // 6/30 valid
    {
        Date d(6, 30, 2021);
        checkInt("6/30 valid - day", 30, d.getDay());
    }

    // 6/31 invalid
    {
        Date d(6, 31, 2021);
        checkInt("6/31 invalid -> default", 1, d.getMonth());
    }

    // 2/28 valid in non-leap year
    {
        Date d(2, 28, 2023);
        checkInt("2/28 non-leap valid - day", 28, d.getDay());
    }

    // 2/29 invalid in non-leap year
    {
        Date d(2, 29, 2023);
        checkInt("2/29 non-leap invalid -> default", 1, d.getMonth());
    }

    // 2/29 valid in leap year
    {
        Date d(2, 29, 2024);
        checkInt("2/29 leap valid - day", 29, d.getDay());
    }

    // 2/30 always invalid
    {
        Date d(2, 30, 2024);
        checkInt("2/30 always invalid -> default", 1, d.getMonth());
    }
}

void testPrintFormats()
{
    section("8. Print Format Tests");

    // Date 1: 12/25/2021
    {
        Date d(12, 25, 2021);
        checkStr("Numeric       12/25/2021", "12/25/2021", d.printNumeric());
        checkStr("Long          Dec 25 2021", "December 25, 2021", d.printLongFormat());
        checkStr("Intl          25 Dec 2021", "25 December 2021", d.printInternational());
    }

    // Date 2: 7/4/1776
    {
        Date d(7, 4, 1776);
        checkStr("Numeric       7/4/1776", "7/4/1776", d.printNumeric());
        checkStr("Long          Jul 4 1776", "July 4, 1776", d.printLongFormat());
        checkStr("Intl          4 Jul 1776", "4 July 1776", d.printInternational());
    }

    // Date 3: 2/29/2000 (leap year)
    {
        Date d(2, 29, 2000);
        checkStr("Numeric       2/29/2000", "2/29/2000", d.printNumeric());
        checkStr("Long          Feb 29 2000", "February 29, 2000", d.printLongFormat());
        checkStr("Intl          29 Feb 2000", "29 February 2000", d.printInternational());
    }
}

// -------------------------------------------------------
// Main
// -------------------------------------------------------
int main()
{
    std::cout << "==========================================\n";
    std::cout << "    Date Class - Comprehensive Test\n";
    std::cout << "    CSC 222 - Introduction to Classes\n";
    std::cout << "==========================================\n";

    testDefaultConstructor();
    testValidConstructor();
    testInvalidConstructor();
    testSetDate();
    testLeapYear();
    testLastDay();
    testEdgeCases();
    testPrintFormats();

    std::cout << "\n==========================================\n";
    std::cout << "  RESULTS:  "
        << testsPassed << " passed,  "
        << testsFailed << " failed\n";
    std::cout << "==========================================\n";

    return (testsFailed == 0) ? 0 : 1;
}  