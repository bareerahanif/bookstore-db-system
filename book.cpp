#include"book.h"

Book::Book(std::string title, std::string ISBN, int author,
	std::string publisher, std::string edition, std::string price, std::string year) :
	bookTitle{ title }, bookISBN{ ISBN }, authorid{ author }, bookPublisher{ publisher },
	bookEdition{ edition }, bookPrice{ price }, bookYear{ year } {}
std::string Book::getBookTitle() const
{
	return bookTitle;
}
std::string Book::getBookPublisher() const
{
	return bookPublisher;
}
std::string Book::getBookEdition() const
{
	return bookEdition;
}
std::string Book::getBookISBN() const
{
	return bookISBN;
}
std::string Book::getBookPrice() const
{
	return bookPrice;
}
std::string Book::getBookYear() const
{
	return bookYear;
}
int Book::getBookAuthor() const
{
	return authorid;
}
