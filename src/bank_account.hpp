#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <iostream>
#include "deposit.hpp"
#include <vector>

class BankAccount
{
    private:
        std::string name;
        std::string surname;
        std::string birth_date;
        std::vector<Deposit> possesed_products;
    public:
        BankAccount(std::string name, std::string surname, std::string birth_date);
        void addDeposit(double balance, double rate, std::string currency);
        void removeDeposit(int id);
        void findDeposit(int id);
        void editDeposit(int id);
        void showDeposits();
        void countDeposits();
};


#endif