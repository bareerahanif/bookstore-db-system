#ifndef SALES_H
#define SALES_H
#include"customer.h"
#include"book.h"
#include"author.h"

class Sale
{
public:
	Sale(std::string date, int customer, int book, std::string disc, std::string price);
	std::string getSaleDate() const;
	int getSaleCustomer() const;
	int getSaleBook() const;
	std::string getDiscount() const;
	std::string getTotalPrice()const;
private:
	std::string saleDate;
	int saleCustomerID;
	int saleBookID;
	std::string discount;
	std::string totalPrice;
};


#endif

