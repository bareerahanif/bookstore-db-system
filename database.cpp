#include"database.h"
#include <sqlite3.h>

DataBase::DataBase(const char* dbPath)
{
    createDB(dbPath);
    createTables();
}
int DataBase::createDB(const char* s)
{
    int rc{ 0 };
    rc = sqlite3_open(s, &DB);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return 1;
    }
    return rc;
}
void DataBase::createTables()
{
    createCustomerTable();
    createBookTable();
    createAuthorTable();
    createSaleTable();
}

std::vector<std::pair<int, std::string>> DataBase::getAuthors()
{
    std::vector<std::pair<int, std::string>> authors;

    std::string sql = "SELECT AuthorID, Name FROM Authors;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return authors;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int authorId = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        authors.push_back({ authorId, std::string(reinterpret_cast<const char*>(name)) });
    }

    sqlite3_finalize(stmt);
    return authors;
}

std::vector<std::pair<int, std::string>> DataBase::getCustomers()
{
    std::vector<std::pair<int, std::string>> customers;

    std::string sql = "SELECT CustomerID, Name FROM Customers;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return customers;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int customerId = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        customers.push_back({ customerId, std::string(reinterpret_cast<const char*>(name)) });
    }

    sqlite3_finalize(stmt);
    return customers;
}

std::vector<std::pair<int, std::string>> DataBase::getBooks()
{
    std::vector<std::pair<int, std::string>> books;

    std::string sql = "SELECT BookID, Name FROM Books;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return books;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int bookId = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        books.push_back({ bookId, std::string(reinterpret_cast<const char*>(name)) });
    }

    sqlite3_finalize(stmt);
    return books;
}

std::vector<std::pair<int, std::string>> DataBase::getSales()
{
    std::vector<std::pair<int, std::string>> sales;

    std::string sql = "SELECT SaleID, Name FROM Sales;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return sales;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int saleId = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        sales.push_back({ saleId, std::string(reinterpret_cast<const char*>(name)) });
    }

    sqlite3_finalize(stmt);
    return sales;
}

void DataBase::createCustomerTable()
{
    const char* sqlCommand = R"(CREATE TABLE IF NOT EXISTS Customers (
        CustomerId INTEGER PRIMARY KEY AUTOINCREMENT,
        Name TEXT,
        Email TEXT,
        Address TEXT,
        PhoneNumber TEXT
        );)";

    char* errMsg = nullptr;


    int rc = sqlite3_exec(DB, sqlCommand, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating Customer table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}
void DataBase::addNewCustomerRecord(const Customer& newCustomer)
{
    const std::string sql = "INSERT INTO Customers (Name, Email, Address, PhoneNumber) VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
        return;
    }
    std::string name = newCustomer.getName();
    std::string email = newCustomer.getEmail();
    std::string address = newCustomer.getAddress();
    std::string phone = newCustomer.getPhoneNumber();

    sqlite3_bind_text(stmt, 1, name.c_str(), static_cast<int>(name.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email.c_str(), static_cast<int>(email.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, address.c_str(), static_cast<int>(address.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, phone.c_str(), static_cast<int>(phone.length()), SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting record into Customers table: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
        std::cout << "\n\nCustomer Added Successfully...\n\n\n";

    sqlite3_finalize(stmt);
}

void DataBase::createBookTable()
{
    const char* sqlCommand = R"(CREATE TABLE IF NOT EXISTS Books (
        BookId INTEGER PRIMARY KEY AUTOINCREMENT,
        Book_Title TEXT,
        Author_ID INTEGER,
        Publisher TEXT,
        Edition TEXT,
        ISBN TEXT,
        Price TEXT,
        Year TEXT
        );)";

    char* errMsg = nullptr;


    int rc = sqlite3_exec(DB, sqlCommand, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating Book table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}
void DataBase::addNewBookRecord(const Book& newBook)
{
    const std::string sql = "INSERT INTO Books (Book_Title, Author_ID, Publisher, Edition, ISBN, Price, Year) VALUES (?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
        return;
    }

    std::string bookTitle = newBook.getBookTitle();
    int authorID = newBook.getBookAuthor();
    std::string bookPublisher = newBook.getBookPublisher();
    std::string bookEdition = newBook.getBookEdition();
    std::string bookISBN = newBook.getBookISBN();
    std::string bookPrice = newBook.getBookPrice();
    std::string bookYear = newBook.getBookYear();

    sqlite3_bind_text(stmt, 1, bookTitle.c_str(), static_cast<int>(bookTitle.length()), SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, authorID);
    sqlite3_bind_text(stmt, 3, bookPublisher.c_str(), static_cast<int>(bookPublisher.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, bookEdition.c_str(), static_cast<int>(bookEdition.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, bookISBN.c_str(), static_cast<int>(bookISBN.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, bookPrice.c_str(), static_cast<int>(bookPrice.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, bookYear.c_str(), static_cast<int>(bookYear.length()), SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting record into Books table: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
        std::cout << "\n\nBook Added Successfully...\n\n\n";

    sqlite3_finalize(stmt);
}


void DataBase::createAuthorTable()
{
    const char* sqlCommand = R"(CREATE TABLE IF NOT EXISTS Authors (
        AuthorId INTEGER PRIMARY KEY AUTOINCREMENT,
        Name TEXT,
        Email TEXT,
        Address TEXT,
        PhoneNumber TEXT,
        Genre TEXT
        );)";

    char* errMsg = nullptr;


    int rc = sqlite3_exec(DB, sqlCommand, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating Author table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}
void DataBase::addNewAuthorRecord(const Author& newAuthor)
{
    const std::string sql = "INSERT INTO Authors (Name, Email, Address, PhoneNumber, Genre) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
        return;
    }

    std::string name = newAuthor.getAuthorName();
    std::string email = newAuthor.getAuthorEmail();
    std::string address = newAuthor.getAuthorAddress();
    std::string phone = newAuthor.getAuthorPhNum();
    std::string genre = newAuthor.getAuthorGenre();

    sqlite3_bind_text(stmt, 1, name.c_str(), static_cast<int>(name.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email.c_str(), static_cast<int>(email.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, address.c_str(), static_cast<int>(address.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, phone.c_str(), static_cast<int>(phone.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, genre.c_str(), static_cast<int>(genre.length()), SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting record into Authors table: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
        std::cout << "\n\nAuthor Added Successfully...\n\n\n";

    sqlite3_finalize(stmt);
}


void DataBase::createSaleTable()
{
    const char* sqlCommand = R"(CREATE TABLE IF NOT EXISTS Sales (
        SaleId INTEGER PRIMARY KEY AUTOINCREMENT,
        Date TEXT,
        CustomerID INTEGER,
        BookID INTEGER,
        Discount TEXT,
        Total_Price TEXT
        );)";

    char* errMsg = nullptr;


    int rc = sqlite3_exec(DB, sqlCommand, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating Sales table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}
void DataBase::addNewSaleRecord(const Sale& newSale)
{
    const std::string sql = "INSERT INTO Sales (Date, CustomerID, BookID, Discount, Total_Price) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
        return;
    }

    std::string saleDate = newSale.getSaleDate();
    int saleCustomer = newSale.getSaleCustomer();
    int saleBook = newSale.getSaleBook();
    std::string discount = newSale.getDiscount();
    std::string totalPrice = newSale.getTotalPrice();

    sqlite3_bind_text(stmt, 1, saleDate.c_str(), static_cast<int>(saleDate.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, discount.c_str(), static_cast<int>(discount.length()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, totalPrice.c_str(), static_cast<int>(totalPrice.length()), SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting record into Sales table: " << sqlite3_errmsg(DB) << std::endl;
    }
    else
        std::cout << "\n\nSale Added Successfully...\n\n\n";

    sqlite3_finalize(stmt);
}

DataBase::~DataBase()
{
    sqlite3_close(DB);
}


std::vector<Sale> DataBase::getBookSales(int bookID)
{
    std::vector<Sale> Sales;
    std::string sql = "SELECT * FROM Sales WHERE BookID = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
        return Sales;
    }

    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW)
    {
        std::string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int customerID = sqlite3_column_int(stmt, 2);
        int bookID = sqlite3_column_int(stmt, 3);
        std::string discount = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        std::string totalPrice = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        Sales.push_back(Sale(date, customerID, bookID, discount, totalPrice));
    }

    sqlite3_finalize(stmt);
    return Sales;
}

std::vector<Book> DataBase::getAllBookOfAuthor(int authorID)
{
    std::vector<Book> Books;
    std::string sql = "SELECT * FROM Books WHERE Author_ID = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
        return Books;
    }

    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW)
    {
        std::string bookTitle = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int authorid = sqlite3_column_int(stmt, 2);
        std::string bookPublisher = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string bookEdition = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        std::string bookISBN = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        std::string bookPrice = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        std::string bookYear = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));

        Books.push_back(Book(bookTitle, bookISBN, authorid, bookPublisher, bookEdition, bookPrice, bookYear));
    }

    sqlite3_finalize(stmt);
    return Books;
}

std::vector<Book> DataBase::getAllBooks()
{
    std::vector<Book> books;

    std::string sql = "SELECT * FROM Books;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return books;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string bookTitle = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int authorId = sqlite3_column_int(stmt, 2);
        std::string publisher = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string edition = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        std::string ISBN = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        std::string price = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        std::string year = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));

        books.push_back(Book(bookTitle, ISBN, authorId, publisher, edition, price, year));
    }

    sqlite3_finalize(stmt);
    return books;
}
std::vector<Author> DataBase::getAllAuthors()
{
	std::vector<Author> authors;

	std::string sql = "SELECT * FROM Authors;";
	sqlite3_stmt* stmt;
	if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
		return authors;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
		std::string address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
		std::string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
		std::string genre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

		authors.push_back(Author(name, email, address, phone, genre));
	}

	sqlite3_finalize(stmt);
	return authors;
}
