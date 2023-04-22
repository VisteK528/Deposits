#ifndef BANK_ACCOUNT_HPP
#define BANK_ACCOUNT_HPP

#include <iostream>
#include "factory.hpp"
#include "deposit.hpp"
#include "date.hpp"
#include <vector>
#include <algorithm>
#include <chrono>
#include <memory>

/*

Zrealizować wzorzec projektowy fabryki jako klasy tworzącej lokaty roznych rodzajow,
aby nastepnie moc dodac je jako elementy kolekcji std::vector przechowującej wskazania

*/

class BankAccount
{
    private:
        Deposit& findDepositReference(unsigned int id);
        std::shared_ptr<Deposit> findDepositPointer(unsigned int id);
        std::string name;
        std::string surname;
        std::vector<std::shared_ptr<Deposit>> possesed_products;

        std::unique_ptr<DepositFactory> factory;

        // Birthdate
        void setBirthdate(std::string birth_date_str);
        year_month_day birth_date;
    public:
        BankAccount(std::string name, std::string surname, std::string birth_date);
        std::string getName() const;
        std::string getSurname() const;
        std::chrono::year_month_day getBirthDate() const;
        std::string getBirthDateString() const;
        void addDeposit(double balance, bank_rate rate, std::string currency, int term_months, int capital_gains_tax);
        template<class T>
        void addDeposit(const T &t)
        {
            possesed_products.push_back(std::make_shared<T>(t));
        }
        template<class T>
        void addDeposit(std::shared_ptr<T> t)
        {
            possesed_products.push_back(t);
        }
        void removeDeposit(unsigned int id);
        void setDepositRate(unsigned int id, bank_rate rate);
        void convertDeposit(unsigned int id, std::string currency_symbol, bank_rate exchange_rate);
        const Deposit& findDeposit(unsigned int id);
        std::vector<std::shared_ptr<Deposit>> getDeposits() const;
        unsigned int countDeposits()const{return possesed_products.size();};
        unsigned int getUniqueIndex();

        //Operator overloading
        friend std::ostream& operator<<(std::ostream &os, const BankAccount &b);
};


#endif