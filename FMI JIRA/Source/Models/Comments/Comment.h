#pragma once

#include <string>
#include <iostream>
#include <string_view>
#include "Utils/Date.h"
class User;

namespace CommentConstants {
    constexpr std::string_view ERROR_EMPTY_CONTENT = "Comment content cannot be empty.";
    constexpr std::string_view ERROR_NULL_AUTHOR = "Comment author cannot be null.";
}

class Comment {
private:
    const User* author = nullptr;
    std::string content;
    Date creationDate;

public:
    Comment() = default;
    Comment(const User* author, const std::string& content, const Date& date);

    const User* getAuthor() const;
    const std::string& getContent() const;
    const Date& getCreationDate() const;

    void save(std::ostream& os) const;
    static Comment load(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const Comment& comment);
};