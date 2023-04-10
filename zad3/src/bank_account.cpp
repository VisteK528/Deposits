#include "bank_account.hpp"

BankAccount::BankAccount(std::string name, std::string surname, std::string birth_date)
{
    this->name = name;
    this->surname = surname;
    setBirthdate(birth_date);
}

std::string BankAccount::getName() const
{
    return this->name;
}

std::string BankAccount::getSurname() const
{
    return this->surname;
}

std::chrono::year_month_day BankAccount::getBirthDate() const
{
    return this->birth_date.date();
}

std::string BankAccount::getBirthDateString() const
{
    return this->birth_date.getAsString();
}

std::vector<Deposit> BankAccount::getDeposits() const
{
    return this->possesed_products;


}

void BankAccount::setBirthdate(std::string birth_date_str)
{
    if(birth_date_str.length() != 10)
    {
        throw InvalidDateFormatError("According to ISO 8601 norm date should be expressed as YYYY-MM-DD, thus it should consist of 10 characters!");
    }
    else if(birth_date_str[4] != '-' || birth_date_str[7] != '-')
    {
        throw InvalidDateFormatError("Passed date format does not satisfy ISO 8601 norm! Date format should be YYYY-MM-DD");
    }
    std::chrono::year year(std::stoi(birth_date_str.substr(0, 4)));
    std::chrono::month month(std::stoi(birth_date_str.substr(5, 6)));
    std::chrono::day day(std::stoi(birth_date_str.substr(8, 9)));

    this->birth_date = year_month_day(year, month, day);
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

void BankAccount::addDeposit(double balance, bank_rate rate, std::string currency, int term_months, int capital_gains_tax)
{
    unsigned int index = createUniqeIndex(possesed_products);
    possesed_products.push_back(Deposit(balance, rate, currency, term_months, index, capital_gains_tax));
}

Deposit& BankAccount::findDepositReference(unsigned int id)
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

const Deposit& BankAccount::findDeposit(unsigned int id)
{
    const Deposit &d = findDepositReference(id);
    return d;
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

void BankAccount::setDepositRate(unsigned int id, bank_rate rate)
{
    Deposit &d = findDepositReference(id);
    d.setRate(rate);
}

void BankAccount::convertDeposit(unsigned int id, std::string currency_symbol, bank_rate exchange_rate)
{
    Deposit &d = findDepositReference(id);
    d.convert(currency_symbol, exchange_rate);
}

std::ostream& operator<<(std::ostream &os, const BankAccount &b)
{
    os<<"Owner's data"<<std::endl;
    os<<"\t1. Name: "<<b.name<<std::endl;
    os<<"\t2. Surname: "<<b.surname<<std::endl;
    os<<"\t3. Birthdate: "<<b.birth_date<<std::endl;
    os<<"Posessed products:"<<std::endl<<std::endl;
    for(const Deposit &product: b.possesed_products)
    {
        os<<product<<std::endl;
    }
    return os;
}