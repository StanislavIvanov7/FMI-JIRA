#pragma once
#include<string>
#include <string_view>
#include<compare>
namespace DateConstants {
    constexpr std::string_view DATE_FORMAT_TEMPLATE = "{:02d}.{:02d}.{:04d}";
    constexpr std::string_view ERROR_INVALID_DATE_VALUES = "Provided day, month or year are outside valid calendar bounds.";
    constexpr std::string_view ERROR_PARSE_FORMAT = "Date parse error! Expected format is DD.MM.YYYY, but received: ";

    constexpr int MIN_VALID_YEAR = 1900;
    constexpr int MAX_VALID_YEAR = 2100;
    constexpr int DEFAULT_SYSTEM_YEAR = 2026;
    constexpr int MIN_VALID_MONTH = 1;
    constexpr int MAX_VALID_MONTH = 12;
    constexpr int MIN_VALID_DAY = 1;

    constexpr int MONTH_FEB = 2;
    constexpr int MONTH_APR = 4;
    constexpr int MONTH_JUN = 6;
    constexpr int MONTH_SEP = 9;
    constexpr int MONTH_NOV = 11;

    constexpr int LEAP_YEAR_DIVISOR_4 = 4;
    constexpr int LEAP_YEAR_DIVISOR_100 = 100;
    constexpr int LEAP_YEAR_DIVISOR_400 = 400;
    constexpr int REMAINDER_ZERO = 0;

    constexpr int DAYS_IN_LEAP_YEAR = 366;
    constexpr int DAYS_IN_NORMAL_YEAR = 365;

    constexpr int DAYS_SHORT_MONTH = 30;
    constexpr int DAYS_LONG_MONTH = 31;
    constexpr int DAYS_FEB_NORMAL = 28;
    constexpr int DAYS_FEB_LEAP = 29;

    constexpr int EXPECTED_STR_SIZE = 10;
    constexpr int DOT_INDEX_1 = 2;
    constexpr int DOT_INDEX_2 = 5;

    constexpr int DAY_START = 0;
    constexpr int DAY_LEN = 2;
    constexpr int MONTH_START = 3;
    constexpr int MONTH_LEN = 2;
    constexpr int YEAR_START = 6;
    constexpr int YEAR_LEN = 4;

    constexpr char DOT_CHAR = '.';

}

class Date {
private:
    int day = DateConstants::MIN_VALID_DAY;
    int month = DateConstants::MIN_VALID_MONTH;
    int year = DateConstants::DEFAULT_SYSTEM_YEAR;

    static bool isLeapYear(int y);
    static bool isValidDate(int d, int m, int y);
    static int daysInMonth(int m, int y);

  
    int toAbsoluteDays() const;

public:
    
    Date();
    Date(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    auto operator<=>(const Date& other) const; 
    bool operator==(const Date& other) const;

    std::string toString() const;
    static Date parse(const std::string& str);

    bool isBefore(const Date& other) const;
    bool isAfter(const Date& other) const;
    int daysUntil(const Date& other) const;
};