#include"bookstore.h"
#include<iostream>

int displayMenu()
{
	int choice;
	std::cout << "\n\n\n________________WELCOME TO THE BOOKSTORE MANAGEMENT SYSTEM_________________\n" << std::endl << std::endl;
	std::cout << "01. Add a New Book" << std::endl;
	std::cout << "02. Add a New Customer" << std::endl;
	std::cout << "03. Add a New Author" << std::endl;
	std::cout << "04. Enter a Sale" << std::endl;
	std::cout << "05. Book Report" << std::endl;
	std::cout << "06. Author Report" << std::endl;
	std::cout << "09. Exit" << std::endl;
	std::cout << "\n\nEnter Choice: ";
	std::cin >> choice;
	return choice;
}

int main()
{
	BookStore bookstore("D:\\oop\\splite\\splite\\newdb.db");
	do
	{
		int choice = displayMenu();
		switch (choice)
		{
		case 1:
			bookstore.inputBook();
			break;
		case 2:
			bookstore.inputCustomer();
			break;
		case 3:
			bookstore.inputAuthor();
			break;
		case 4:
			bookstore.inputSale();
			break;
		case 5:
			bookstore.generateBookReport();
			break;
		case 6:
			bookstore.generateAuthorReport();
			break;

		case 9:
			return 0;
	
		}
	} while (1);

	return 0;
}