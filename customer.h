#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>


class Customer
{
public:
    Customer(const std::string& name, const std::string& email, const std::string& address, const std::string& phoneNumber);
    Customer();
    std::string getName() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getPhoneNumber() const;
private:
    std::string name;
    std::string email;
    std::string address;
    std::string phoneNumber;
};
#endif
