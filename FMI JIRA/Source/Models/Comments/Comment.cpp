#include "Comment.h"
#include "Models/Users/User.h"
#include "App/AppData.h"
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
void Comment::save(std::ostream& os) const {
    os << author->getUsername() << "\n"
        << content << "\n"
        << creationDate.getDay() << " "
        << creationDate.getMonth() << " "
        << creationDate.getYear() << "\n";
}

Comment Comment::load(std::istream& is, const AppData& context) {
    std::string username, content;

   
    std::getline(is, username);
    std::getline(is, content);

    int d, m, y;
    is >> d >> m >> y;
    is.ignore(); 

    Date date(d, m, y);

    
    const User* userPtr = context.findUser(username);

   
    return Comment(userPtr, content, date);
}


std::ostream& operator<<(std::ostream& os, const Comment& comment) {
	os << std::format("[{}] {}: {}",
		comment.creationDate.toString(),
		comment.author->getUsername(),
		comment.content);
	return os;
}