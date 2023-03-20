#ifndef DEPOSIT_HPP
#define DEPOSIT_HPP

#include <string>
#include "exceptions.hpp"
#include <math.h>

typedef double bank_rate;

class Date
{
    private:
        unsigned int day;
        unsigned int month;
        unsigned int year;
    public:
        Date();
        Date(std::string iso_date);
};

class Deposit
{
    private:
        unsigned int income_tax = 19;
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
        unsigned int getId();
        unsigned int getTerm();
        double getBalance();
        bank_rate getRate();
        std::string getCurrency();
        void setRate(bank_rate rate);
        void convert(std::string currency, bank_rate exchange_rate);
        double calculateProfit();

};

#endif