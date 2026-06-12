#include "Comment.h"
#include "Models/Users/User.h"
#include "Exceptions/JiraInvalidArgumentException.h"
#include <format>

Comment::Comment(const User* author, const std::string& content, const Date& date)
	: author(author), content(content), creationDate(date) {

	if (!this->author) {
		throw JiraInvalidArgumentException(std::string(CommentConstants::ERROR_NULL_AUTHOR));
	}
	if (this->content.empty()) {
		throw JiraInvalidArgumentException(std::string(CommentConstants::ERROR_EMPTY_CONTENT));
	}
}

const User* Comment::getAuthor() const {
	return author;
}

const std::string& Comment::getContent() const {
	return content;
}

const Date& Comment::getCreationDate() const {
	return creationDate;
}

std::ostream& operator<<(std::ostream& os, const Comment& comment) {
	os << std::format("[{}] {}: {}",
		comment.creationDate.toString(),
		comment.author->getUsername(),
		comment.content);
	return os;
}