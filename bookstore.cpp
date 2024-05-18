#include"bookstore.h"

BookStore::BookStore(const char* dbPath) :database(dbPath) {}

std::vector<std::pair<int, std::string>> BookStore::getAllAuthors()
{
	return database.getAuthors();
}
std::vector<std::pair<int, std::string>> BookStore::getAllBooks()
{
	return database.getBooks();
}
std::vector<std::pair<int, std::string>> BookStore::getAllCustomers()
{
	return database.getCustomers();
}
std::vector<std::pair<int, std::string>> BookStore::getAllSales()
{
	return database.getSales();
}

void BookStore::addNewBook(const std::string title, const std::string ISBN,
	const int author, const std::string publisher, const std::string edition, const std::string price, const std::string year)
{
	Book newBook(title, ISBN, author, publisher, edition, price, year);
	database.addNewBookRecord(newBook);
}
void BookStore::addNewCustomer(const std::string& name,
	const std::string& email, const std::string& address, const std::string& phoneNumber)
{
	Customer newCustomer(name, email, address, phoneNumber);
	database.addNewCustomerRecord(newCustomer);
}
void BookStore::addNewAuthor(const std::string name, const std::string email,
	const std::string genre, const std::string phNum, const std::string address)
{
	const Author newAuthor(name, email, genre, phNum, address);
	database.addNewAuthorRecord(newAuthor);
}
void BookStore::addNewSale(std::string date, int customer,
	int book, std::string disc, std::string price)
{
	Sale newSale(date, customer, book, disc, price);
	database.addNewSaleRecord(newSale);
}

void BookStore::displayAuthors()
{
	std::vector<std::pair<int, std::string>> authors = getAllAuthors();
	std::cout << "\n\nAuthors Available:\n\n" << std::endl;
	for (const auto& author : authors)
	{
		std::cout << author.first << ". " << author.second << std::endl;
	}
}
void BookStore::displayCustomers()
{
	std::vector<std::pair<int, std::string>> customers = getAllCustomers();
	std::cout << "\n\nCustomers Available:\n\n" << std::endl;
	for (const auto& customer : customers)
	{
		std::cout << customer.first << ". " << customer.second << std::endl;
	}
}
void BookStore::displayBooks() {
	std::vector<std::pair<int, std::string>> books = database.getBooks();
	if (books.empty()) {
		std::cout << "No books available." << std::endl;
	}
	else {
		std::cout << "\n\nBooks Available:\n\n" << std::endl;
		for (const auto& book : books) {
			std::cout << book.first << ". " << book.second << std::endl;
		}
	}
}
void BookStore::displaySales()
{
	std::vector<std::pair<int, std::string>> sales = getAllSales();
	std::cout << "\n\nSales Available:\n\n" << std::endl;
	for (const auto& sale : sales)
	{
		std::cout << sale.first << ". " << sale.second << std::endl;
	}
}

void BookStore::inputBook()
{
	std::string bookTitle;
	int authorID;
	std::string bookPublisher;
	std::string bookEdition;
	std::string bookISBN;
	std::string bookPrice;
	std::string bookYear;

	std::getline(std::cin, bookTitle);
	std::cout << "\n\nBook Title: ";
	std::getline(std::cin, bookTitle);

	displayAuthors();
	std::cout << "\nAuthor ID: ";
	std::cin >> authorID;
	std::getline(std::cin, bookPublisher);
	std::cout << "\nPublisherName: ";
	std::getline(std::cin, bookPublisher);
	std::cout << "\nEdition: ";
	std::getline(std::cin, bookEdition);
	std::cout << "\nISBN: ";
	std::getline(std::cin, bookISBN);
	std::cout << "\nPrice: ";
	std::getline(std::cin, bookPrice);
	std::cout << "\nPublication Year: ";
	std::getline(std::cin, bookYear);

	this->addNewBook(bookTitle, bookISBN, authorID, bookPublisher, bookEdition, bookPrice, bookYear);

}
void BookStore::inputCustomer()
{
	std::string name;
	std::string email;
	std::string address;
	std::string phoneNumber;

	std::getline(std::cin, name);
	std::cout << "\nCustomer Name: ";
	std::getline(std::cin, name);
	std::cout << "\nCustomer Email: ";
	std::getline(std::cin, email);
	std::cout << "\nCustomer Address: ";
	std::getline(std::cin, address);
	std::cout << "\nCustomer Phone Number: ";
	std::getline(std::cin, phoneNumber);

	this->addNewCustomer(name, email, address, phoneNumber);


}
void BookStore::inputAuthor()
{
	std::string authorName;
	std::string authorEmail;
	std::string authorGenre;
	std::string authorPhNum;
	std::string authorAddress;

	std::getline(std::cin, authorName);
	std::cout << "\nAuhtor Name: ";
	std::getline(std::cin, authorName);
	std::cout << "\nEmail: ";
	std::getline(std::cin, authorEmail);
	std::cout << "\nAddress: ";
	std::getline(std::cin, authorAddress);
	std::cout << "\nPhone Number: ";
	std::getline(std::cin, authorPhNum);
	std::cout << "\nGenre: ";
	std::getline(std::cin, authorGenre);

	this->addNewAuthor(authorName, authorEmail, authorGenre, authorPhNum, authorAddress);

}
void BookStore::inputSale()
{
	std::string saleDate;
	int saleCustomerID;
	int saleBookID;
	std::string discount;
	std::string totalPrice;

	std::cin.ignore(); 

	std::cout << "\nSale Date: ";
	std::getline(std::cin, saleDate);

	displayCustomers();
	std::cout << "\nCustomer Id: ";
	std::cin >> saleCustomerID;

	displayBooks(); 
	std::cout << "\nBook Id: ";
	std::cin >> saleBookID;

	std::cin.ignore(); 

	std::cout << "\nDiscount: ";
	std::getline(std::cin, discount);
	std::cout << "\nTotal Price: ";
	std::getline(std::cin, totalPrice);

	this->addNewSale(saleDate, saleCustomerID, saleBookID, discount, totalPrice);
}

void BookStore::salesDetails(Sale Sale)
{
	std::cout << "\n\n";
	std::cout << "Sale Date: " << Sale.getSaleDate();
	std::cout << "Customer ID: " << Sale.getSaleCustomer();
	std::cout << "Book ID: " << Sale.getSaleBook();
	std::cout << "Discount: " << Sale.getDiscount();
	std::cout << "Total Price: " << Sale.getTotalPrice();
	std::cout << "\n\n";
}
void BookStore::booksDetails(Book book)
{
	std::cout << "\n\n";
	std::cout << "Book Title: " << book.getBookTitle();
	std::cout << "Book Publisher: " << book.getBookPublisher();
	std::cout << "Book Edition: " << book.getBookEdition();
	std::cout << "Book ISBN: " << book.getBookISBN();
	std::cout << "Book Price: " << book.getBookPrice();
	std::cout << "Book Year: " << book.getBookYear();
	std::cout << "Author ID: " << book.getBookAuthor();
	std::cout << "\n\n";
}


void BookStore::booksReport()
{
	displayBooks();
	int bookID;
	std::cout << "Book Id: ";
	std::cin >> bookID;
	std::vector<Sale> bookSales = database.getBookSales(bookID);
	if (bookSales.size() == 0)
		std::cout << "\n\nNo Sales Exits of this BookId...\n\n";
	for (auto& Sale : bookSales)
	{
		salesDetails(Sale);
	}
}
void BookStore::authorsReport()
{
	displayAuthors();
	int authorID;
	std::cout << "Author Id: ";
	std::cin >> authorID;
	std::vector<Book> allBooks = database.getAllBookOfAuthor(authorID);
	if (allBooks.size() == 0)
		std::cout << "\n\nNo Books Exits of this AuthorId...\n\n";
	for (auto& Book : allBooks)
	{
		booksDetails(Book);
	}
}
void BookStore::generateBookReport()
{
	std::vector<Book> books = database.getAllBooks();

	std::cout << "Book Report:\n";
	for (const auto& book : books)
	{
		std::cout << "Title: " << book.getBookTitle() << "\n";
		std::cout << "Author ID: " << book.getBookAuthor() << "\n";
		std::cout << "Publisher: " << book.getBookPublisher() << "\n";
		std::cout << "Edition: " << book.getBookEdition() << "\n";
		std::cout << "ISBN: " << book.getBookISBN() << "\n";
		std::cout << "Price: " << book.getBookPrice() << "\n";
		std::cout << "Year: " << book.getBookYear() << "\n\n";
	}
}
void BookStore::generateAuthorReport()
{
	std::vector<Author> authors = database.getAllAuthors();

	std::cout << "Author Report:\n";
	for (const auto& author : authors)
	{
		std::cout << "Name: " << author.getAuthorName() << "\n";
		std::cout << "Email: " << author.getAuthorEmail() << "\n";
		std::cout << "Genre: " << author.getAuthorGenre() << "\n";
		std::cout << "Phone Number: " << author.getAuthorPhNum() << "\n";
		std::cout << "Address: " << author.getAuthorAddress() << "\n\n";
	}
}