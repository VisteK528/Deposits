#include "bank_account.hpp"

BankAccount::BankAccount(std::string name, std::string surname, std::string birth_date)
{
    this->name = name;
    this->surname = surname;
    this->birth_date = birth_date;
}