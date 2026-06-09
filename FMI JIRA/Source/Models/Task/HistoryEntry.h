#pragma once

#include <string>
#include <iostream>
#include <string_view>
#include "Utils/Date.h"
class User;

namespace HistoryConstants {
    constexpr std::string_view ERROR_NULL_USER = "History modifier cannot be null.";
    constexpr std::string_view ERROR_EMPTY_FIELD = "History field name cannot be empty.";
}

class HistoryEntry {
private:
    const User* changedBy = nullptr;
    std::string field;
    std::string oldValue;
    std::string newValue;
    Date timestamp;

public:
    HistoryEntry() = default;

    HistoryEntry(const User* changedBy,
        const std::string& field,
        const std::string& oldValue,
        const std::string& newValue,
        const Date& timestamp);

    const User* getChangedBy() const;
    const std::string& getField() const;
    const std::string& getOldValue() const;
    const std::string& getNewValue() const;
    const Date& getTimestamp() const;

    void save(std::ostream& os) const;
    static HistoryEntry load(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const HistoryEntry& entry);
};