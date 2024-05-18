#include "customer.h"

Customer::Customer(const std::string& name, const std::string& email, const std::string& address, const std::string& phoneNumber)
    : name(name), email(email), address(address), phoneNumber(phoneNumber) {}

Customer::Customer() :name(""), email(""), address(""), phoneNumber("") {}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getEmail() const {
    return email;
}

std::string Customer::getAddress() const {
    return address;
}

std::string Customer::getPhoneNumber() const {
    return phoneNumber;
}