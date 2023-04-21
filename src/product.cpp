#include "product.hpp"

void Product::setCurrency(std::string currency)
{
    if(currency.length() != 3)
    {
        throw InvalidCurrencySymbolError("Currency symbol does not satisfy ISO 4217 standard!");
    }
    else
    {
        this->currency = currency;
    }
}

void Product::setId(int id)
{
    if(id < 0)
    {
        throw InvalidIdValueError("Id value should not be negative!");
    }
    else
    {
        this->id = id;
    }
}

void Product::setTerm(int term)
{
    if(term < 0)
    {
        throw InvalidTermValueError("Time cannot be negative!");
    }
    else
    {
        this->term = std::chrono::hours(term);
    }
}

double Product::getBalance() const
{
    return (double)this->balance/100;
}

unsigned int Product::getId() const
{
    return this->id;
}

std::string Product::getCurrency() const
{
    return this->currency;
}

std::string Product::getProductType() const
{
    return this->product_type;
}

void Product::print(std::ostream &os) const
{
    os<<"Product class object\n";
    os<<"ID: "<<id;
    os<<"Balance: "<<getBalance()<<' '<<currency;
    os<<"Term: "<<getTerm()<<' '<<"hours";
}

unsigned int Product::getTerm() const
{
    return term.count();
}

std::ostream& operator<<(std::ostream& os, const Product &p)
{
    p.print(os);
    return os;
}