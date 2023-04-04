#ifndef DEPOSIT_HPP
#define DEPOSIT_HPP

#include <iostream>
#include <string>
#include "exceptions.hpp"
#include <math.h>

typedef double bank_rate;

class Deposit
{
    private:
        void setCurrency(std::string currency);
        void setTerm(int term_months);
        void setId(int id);
        unsigned int id;
        unsigned int balance;
        std::string currency;
        unsigned int term_months;
        bank_rate rate;
    public:
        Deposit(){};
        Deposit(double balance, bank_rate rate, std::string currency, int term_months, int id);
        unsigned int getId() const;
        unsigned int getTerm() const;
        double getBalance() const;
        bank_rate getRate() const;
        std::string getCurrency() const;
        void setRate(bank_rate rate);
        void convert(std::string currency, bank_rate exchange_rate);
        double calculateProfit() const;
        friend std::ostream& operator<<(std::ostream &os, const Deposit &d);

};

#endif