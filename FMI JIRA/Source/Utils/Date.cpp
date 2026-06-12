#include "Date.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include "Exceptions/JiraDateFormatException.h"
#include<format>
bool Date::isLeapYear(int y) {
	bool is_div_by_4 = (y % DateConstants::LEAP_YEAR_DIVISOR_4 == DateConstants::REMAINDER_ZERO);
	bool is_div_by_100 = (y % DateConstants::LEAP_YEAR_DIVISOR_100 == DateConstants::REMAINDER_ZERO);
	bool is_div_by_400 = (y % DateConstants::LEAP_YEAR_DIVISOR_400 == DateConstants::REMAINDER_ZERO);

	return (is_div_by_4 && !is_div_by_100) || is_div_by_400;
}

int Date::daysInMonth(int m, int y) {
	if (m == DateConstants::MONTH_APR ||
		m == DateConstants::MONTH_JUN ||
		m == DateConstants::MONTH_SEP ||
		m == DateConstants::MONTH_NOV) {
		return DateConstants::DAYS_SHORT_MONTH;
	}
	if (m == DateConstants::MONTH_FEB) {
		return isLeapYear(y) ? DateConstants::DAYS_FEB_LEAP : DateConstants::DAYS_FEB_NORMAL;
	}
	return DateConstants::DAYS_LONG_MONTH;
}

bool Date::isValidDate(int d, int m, int y) {
	if (y < DateConstants::MIN_VALID_YEAR || y > DateConstants::MAX_VALID_YEAR) return false;
	if (m < DateConstants::MIN_VALID_MONTH || m > DateConstants::MAX_VALID_MONTH) return false;
	return d >= DateConstants::MIN_VALID_DAY && d <= daysInMonth(m, y);
}

int Date::toAbsoluteDays() const {
	int total_days = day;

	for (int y = DateConstants::MIN_VALID_YEAR; y < year; ++y) {
		total_days += isLeapYear(y) ? DateConstants::DAYS_IN_LEAP_YEAR : DateConstants::DAYS_IN_NORMAL_YEAR;
	}
	for (int m = DateConstants::MIN_VALID_MONTH; m < month; ++m) {
		total_days += daysInMonth(m, year);
	}
	return total_days;
}


Date::Date() : day(DateConstants::MIN_VALID_DAY),
month(DateConstants::MIN_VALID_MONTH),
year(DateConstants::DEFAULT_SYSTEM_YEAR) {
}

Date::Date(int day, int month, int year) {
	if (!isValidDate(day, month, year)) {
		throw JiraInvalidArgumentException(std::string(DateConstants::ERROR_INVALID_DATE_VALUES));
	}
	this->day = day;
	this->month = month;
	this->year = year;
}


int Date::getDay() const {
	return day;
}
int Date::getMonth() const {
	return month;
}
int Date::getYear() const {
	return year;
}

std::string Date::toString() const {
	return std::format(DateConstants::DATE_FORMAT_TEMPLATE, day, month, year);
}

Date Date::parse(const std::string& str) {
	if (str.size() != DateConstants::EXPECTED_STR_SIZE) {
		throw JiraDateFormatException(std::string(DateConstants::ERROR_PARSE_FORMAT) + str);
	}


	if (str[DateConstants::DOT_INDEX_1] != DateConstants::DOT_CHAR ||
		str[DateConstants::DOT_INDEX_2] != DateConstants::DOT_CHAR) {
		throw JiraDateFormatException(std::string(DateConstants::ERROR_PARSE_FORMAT) + str);
	}

	try {

		int day = std::stoi(str.substr(DateConstants::DAY_START, DateConstants::DAY_LEN));
		int month = std::stoi(str.substr(DateConstants::MONTH_START, DateConstants::MONTH_LEN));
		int year = std::stoi(str.substr(DateConstants::YEAR_START, DateConstants::YEAR_LEN));

		return Date(day, month, year);
	}
	catch (const std::exception&) {

		throw JiraDateFormatException(std::string(DateConstants::ERROR_PARSE_FORMAT) + str);
	}
}

bool Date::isBefore(const Date& other) const {
	return *this < other;
}

bool Date::isAfter(const Date& other) const {
	return *this > other;
}

int Date::daysUntil(const Date& other) const {
	return other.toAbsoluteDays() - this->toAbsoluteDays();
}