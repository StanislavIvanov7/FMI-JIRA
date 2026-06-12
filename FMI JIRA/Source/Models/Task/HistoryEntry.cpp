#include "HistoryEntry.h"
#include "Models/Users/User.h"
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

std::ostream& operator<<(std::ostream& os, const HistoryEntry& entry) {
	os << std::format("[{}] {} changed '{}' from '{}' to '{}'",
		entry.timestamp.toString(),
		entry.changedBy->getUsername(),
		entry.field,
		entry.oldValue.empty() ? "None" : entry.oldValue,
		entry.newValue);
	return os;
}