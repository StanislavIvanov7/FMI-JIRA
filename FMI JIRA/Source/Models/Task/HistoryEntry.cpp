#include "HistoryEntry.h"
#include "Models/Users/User.h"
#include "App/AppData.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include <format>

HistoryEntry::HistoryEntry(const User* changedBy,
	const std::string& field,
	const std::string& oldValue,
	const std::string& newValue,
	const Date& timestamp) 
	: changedBy(changedBy),field(field),
	oldValue(oldValue),newValue(newValue),
	timestamp(timestamp) {

	
	if (!this->changedBy) {
		throw JiraInvalidArgumentException(std::string(HistoryConstants::ERROR_NULL_USER));
	}
	if (this->field.empty()) {
		throw JiraInvalidArgumentException(std::string(HistoryConstants::ERROR_EMPTY_FIELD));
	}
}

const User* HistoryEntry::getChangedBy() const {
	return changedBy;
}

const std::string& HistoryEntry::getField() const {
	return field;
}

const std::string& HistoryEntry::getOldValue() const {
	return oldValue;
}

const std::string& HistoryEntry::getNewValue() const {
	return newValue;
}

const Date& HistoryEntry::getTimestamp() const {
	return timestamp;
}

void HistoryEntry::save(std::ostream& os) const {
	
	os << changedBy->getUsername() << "\n"
		<< field << "\n"
		<< oldValue << "\n"
		<< newValue << "\n"
		<< timestamp.getDay() << " " << timestamp.getMonth() << " " << timestamp.getYear() << "\n";
}

HistoryEntry HistoryEntry::load(std::istream& is, const AppData& context) {
	std::string username, field, oldValue, newValue;

	std::getline(is, username);
	std::getline(is, field);
	std::getline(is, oldValue);
	std::getline(is, newValue);

	
	int d, m, y;
	is >> d >> m >> y;
	is.ignore(); 
	Date timestamp(d, m, y);

	
	const User* user = context.findUser(username);


	return HistoryEntry(user, field, oldValue, newValue, timestamp);
}

std::ostream& operator<<(std::ostream& os, const HistoryEntry& entry) {
	os << std::format("[{}] {} changed '{}' from '{}' to '{}'",
		entry.timestamp.toString(),
		entry.changedBy->getUsername(),
		entry.field,
		entry.oldValue.empty() ? "None" : entry.oldValue,
		entry.newValue);
	return os;
}