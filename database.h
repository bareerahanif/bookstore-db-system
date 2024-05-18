#ifndef DB_H
#define DB_H

#include"Customer.h"
#include"Book.h"
#include"Author.h"
#include"Sales.h"
#include<sqlite3.h>
#include<iostream>

class DataBase
{
public:
	DataBase(const char* dbPath);
	~DataBase();
	int createDB(const char* s);
	std::vector<Book> getAllBooks();
    std::vector<Author> getAllAuthors();
	void addNewBookRecord(const Book& newBook);
	void addNewCustomerRecord(const Customer& newCustomer);
	void addNewAuthorRecord(const Author& newAuthor);
	void addNewSaleRecord(const Sale& newSale);
	std::vector<std::pair<int, std::string>> getAuthors();
	std::vector<std::pair<int, std::string>> getCustomers();
	std::vector<std::pair<int, std::string>> getBooks();
	std::vector<std::pair<int, std::string>> getSales();
	std::vector<Sale> getBookSales(int bookID);
	std::vector<Book> getAllBookOfAuthor(int authorID);

private:
	sqlite3* DB;
	void createTables();
	void createCustomerTable();
	void createBookTable();
	void createAuthorTable();
	void createSaleTable();
};




#endif
