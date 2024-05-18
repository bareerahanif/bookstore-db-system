#ifndef BS_H
#define BS_H
#include"database.h"

class BookStore
{
public:
	BookStore(const char* dbPath);
	void addNewBook(const std::string title, const std::string ISBN, const int author, const std::string publisher, const std::string edition, const std::string price, const std::string year);
	void addNewCustomer(const std::string& name, const std::string& email, const std::string& address, const std::string& phoneNumber);
	void addNewAuthor(const std::string name, const std::string email, const std::string genre, const std::string phNum, const std::string address);
	void addNewSale(std::string date, int customer, int book, std::string disc, std::string price);
	void inputBook();
	void inputCustomer();
	void inputSale();
	void inputAuthor();
	std::vector<std::pair<int, std::string>> getAllAuthors();
	std::vector<std::pair<int, std::string>> getAllBooks();
	std::vector<std::pair<int, std::string>> getAllCustomers();
	std::vector<std::pair<int, std::string>> getAllSales();
	void generateBookReport();
	void generateAuthorReport();
	void booksReport();
	void authorsReport();
	void salesDetails(Sale Sale);
	void booksDetails(Book book);


	void displayAuthors();
	void displayCustomers();
	void displayBooks();
	void displaySales();
private:
	DataBase database;
};



#endif

