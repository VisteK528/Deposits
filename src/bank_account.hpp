#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <iostream>
#include "deposit.hpp"
#include <vector>

class BankAccount
{
    private:
        unsigned int createUniqeIndex(const std::vector<Deposit> &d);
        std::string name;
        std::string surname;
        std::string birth_date;
        std::vector<Deposit> possesed_products;
    public:
        BankAccount(std::string name, std::string surname, std::string birth_date);
        std::string getName();
        std::string getSurname();
        std::string getBirthDate();
        void addDeposit(double balance, bank_rate rate, std::string currency, int term_months);
        void removeDeposit(unsigned int id);
        Deposit& findDeposit(unsigned int id);
        std::vector<Deposit> getDeposits();
        unsigned int countDeposits(){return possesed_products.size();};
};


#endif