#include "bank_account.hpp"

BankAccount::BankAccount(std::string name, std::string surname, std::string birth_date)
{
    this->name = name;
    this->surname = surname;
    this->birth_date = birth_date;
}

std::string BankAccount::getName()
{
    return this->name;
}

std::string BankAccount::getSurname()
{
    return this->surname;
}

std::string BankAccount::getBirthDate()
{
    return this->birth_date;
}

std::vector<Deposit> BankAccount::getDeposits()
{
    return this->possesed_products;


}

unsigned int BankAccount::createUniqeIndex(const std::vector<Deposit> &d)
{
    std::vector<unsigned int> indexes;
    indexes.reserve(possesed_products.size());
    for(auto x: possesed_products)
    {
        indexes.push_back(x.getId());
    }
    struct
    {
        bool operator()(int a, int b){return a < b;}
    }
    less_than;
    std::sort(indexes.begin(), indexes.end(), less_than);
    unsigned int index = 1;
    for(auto x: indexes)
    {
        if(index != x)
        {
            break;
        }
        index++;
    }
    return index;
}

void BankAccount::addDeposit(double balance, bank_rate rate, std::string currency, int term_months)
{
    unsigned int index = createUniqeIndex(possesed_products);
    possesed_products.push_back(Deposit(balance, rate, currency, term_months, index));
}

Deposit& BankAccount::findDeposit(unsigned int id)
{
    auto it = std::find_if(possesed_products.begin(), possesed_products.end(), [&id](Deposit &d){return d.getId() == id;});
    if(it != possesed_products.end())
    {
        int index = std::distance(possesed_products.begin(), it);
        return possesed_products[index];
    }
    else
    {
        throw ProductsInvalidIndexError("Program could not find a Deposit with given id number!");
    }

}

void BankAccount::removeDeposit(unsigned int id)
{
    auto it = std::find_if(possesed_products.begin(), possesed_products.end(), [&id](Deposit &d){return d.getId() == id;});
    if(it != possesed_products.end())
    {
        possesed_products.erase(it);
    }
    else
    {
        throw ProductsInvalidIndexError("Program could not find a Deposit with given id number!");
    }
}