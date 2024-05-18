#include"author.h"

Author::Author(std::string name, std::string email, std::string genre, std::string phNum, std::string address) :
	authorName{ name }, authorEmail{ email }, authorGenre{ genre }, authorPhNum{ phNum }, authorAddress{ address } {}
std::string Author::getAuthorName() const
{
	return authorName;
}
std::string Author::getAuthorEmail() const
{
	return authorEmail;
}
std::string Author::getAuthorGenre() const
{
	return authorGenre;
}
std::string Author::getAuthorPhNum() const
{
	return authorPhNum;
}
std::string Author::getAuthorAddress() const
{
	return authorAddress;
}
