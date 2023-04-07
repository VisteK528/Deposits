#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <iostream>
#include "deposit.hpp"
#include <vector>
#include <algorithm>

class BankAccount
{
    private:
        unsigned int createUniqeIndex(const std::vector<Deposit> &d);
        Deposit& findDepositReference(unsigned int id);
        std::string name;
        std::string surname;
        std::string birth_date;
        std::vector<Deposit> possesed_products;
    public:
        BankAccount(std::string name, std::string surname, std::string birth_date);
        std::string getName() const;
        std::string getSurname() const;
        std::string getBirthDate() const;
        void addDeposit(double balance, bank_rate rate, std::string currency, int term_months, int capital_gains_tax);
        void removeDeposit(unsigned int id);
        void setDepositRate(unsigned int id, bank_rate rate);
        void convertDeposit(unsigned int id, std::string currency_symbol, bank_rate exchange_rate);
        const Deposit& findDeposit(unsigned int id);
        std::vector<Deposit> getDeposits();
        unsigned int countDeposits(){return possesed_products.size();};
        //Operator overloading
        friend std::ostream& operator<<(std::ostream &os, const BankAccount &b);
};


#endif