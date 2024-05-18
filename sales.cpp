#include"sales.h"

Sale::Sale(std::string date, int customer, int book, std::string disc, std::string price) :
	saleDate{ date }, saleCustomerID{ customer }, saleBookID{ book }, discount{ disc }, totalPrice{ price } {}
std::string Sale::getSaleDate() const
{
	return saleDate;
}
int Sale::getSaleCustomer() const
{
	return saleCustomerID;
}
int Sale::getSaleBook() const
{
	return saleBookID;
}
std::string Sale::getDiscount() const
{
	return discount;
}
std::string Sale::getTotalPrice() const
{
	return totalPrice;
}
