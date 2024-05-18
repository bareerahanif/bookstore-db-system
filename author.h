#ifndef AUTHOR_H
#define AUTHOR_H
#include<string>

class Author
{
public:
	Author(std::string name, std::string email, std::string genre, std::string phNum, std::string address);
	std::string getAuthorName() const;
	std::string getAuthorEmail() const;
	std::string getAuthorGenre() const;
	std::string getAuthorPhNum() const;
	std::string getAuthorAddress() const;

private:
	std::string authorName;
	std::string authorEmail;
	std::string authorGenre;
	std::string authorPhNum;
	std::string authorAddress;

};


#endif
