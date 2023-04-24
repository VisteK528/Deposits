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

std::vector<std::shared_ptr<Deposit>> BankAccount::getDeposits() const
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

unsigned int BankAccount::getUniqueIndex()
{
    std::vector<unsigned int> indexes;
    indexes.reserve(possesed_products.size());
    for(auto const &x: possesed_products)
    {
        indexes.push_back(x->getId());
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


std::shared_ptr<Deposit> BankAccount::findDepositPointer(unsigned int id)
{
    auto it = std::find_if(possesed_products.begin(), possesed_products.end(), [&](const std::shared_ptr<Deposit> d){return d->getId() == id;});
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

Deposit& BankAccount::findDepositReference(unsigned int id)
{
    return *findDepositPointer(id);
}

const Deposit& BankAccount::findDeposit(unsigned int id)
{
    const Deposit &d = findDepositReference(id);
    return d;
}

void BankAccount::removeDeposit(unsigned int id)
{
    auto it = std::find_if(possesed_products.begin(), possesed_products.end(), [&](const std::shared_ptr<Deposit> d){return d->getId() == id;});
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

void BankAccount::setDepositRate(unsigned int id, std::vector<bank_rate> rates)
{
    std::shared_ptr<Deposit> deposit = findDepositPointer(id);
    if(deposit->getProductType() != "ProgressiveDeposit")
    {
        throw IncompatibleDepositTypeError("Deposit with given ID is not compatible with this operation!");
    }
    std::shared_ptr<ProgressiveDeposit> progressive_deposit = std::dynamic_pointer_cast<ProgressiveDeposit>(deposit);
    progressive_deposit->setRate(rates);
}

void BankAccount::addMoneyToDeposit(unsigned int id, int addition_month, double amount)
{
    std::shared_ptr<Deposit> deposit = findDepositPointer(id);
    if(deposit->getProductType() != "AdditiveDeposit")
    {
        throw IncompatibleDepositTypeError("Deposit with given ID is not compatible with this operation!");
    }
    std::shared_ptr<AdditiveDeposit> additive_deposit = std::dynamic_pointer_cast<AdditiveDeposit>(deposit);
    additive_deposit->addMoney(addition_month, amount);
}

void BankAccount::convertDeposit(unsigned int id, std::string currency_symbol, bank_rate exchange_rate)
{
    std::shared_ptr<Deposit> deposit = findDepositPointer(id);
    if(deposit->getProductType() != "CurrencyDeposit")
    {
        throw IncompatibleDepositTypeError("Deposit with given ID is not compatible with this operation!");
    }
    std::shared_ptr<CurrencyDeposit> c = std::dynamic_pointer_cast<CurrencyDeposit>(deposit);
    c->convert(currency_symbol, exchange_rate);
}

std::ostream& operator<<(std::ostream &os, const BankAccount &b)
{
    os<<"Owner's data"<<std::endl;
    os<<"\t1. Name: "<<b.name<<std::endl;
    os<<"\t2. Surname: "<<b.surname<<std::endl;
    os<<"\t3. Birthdate: "<<b.birth_date<<std::endl;
    os<<"Posessed products:"<<std::endl<<std::endl;
    for(auto const &i : b.possesed_products)
    {
        os<<*i<<std::endl;
    }
    return os;
}