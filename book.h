#ifndef BOOK_H
#define BOOK_H
#include<iostream>
#include"author.h"

class Book
{
public:
	Book(std::string title, std::string ISBN, int author, std::string publisher, std::string edition, std::string price, std::string year);
	std::string getBookTitle() const;
	std::string getBookPublisher() const;
	std::string getBookEdition() const;
	std::string getBookISBN() const;
	std::string getBookPrice() const;
	std::string getBookYear() const;
	int getBookAuthor() const;

private:
	std::string bookTitle;
	int authorid;
	std::string bookPublisher;
	std::string bookEdition;
	std::string bookISBN;
	std::string bookPrice;
	std::string bookYear;
};


#endif
