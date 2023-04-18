#ifndef DEPOSIT_HPP
#define DEPOSIT_HPP

#include <iostream>
#include <string>
#include "exceptions.hpp"
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <chrono>

typedef double bank_rate;

class Deposit
{
    private:
        void setCurrency(std::string currency);
        void setTerm(int term_months);
        void setId(int id);
        void setCapitalGainsTax(int capital_gains_tax);
        unsigned int id;
        unsigned int balance;
        unsigned int capital_gains_tax;
        std::string currency;
        std::chrono::months term_months;
        bank_rate rate;
    public:
        Deposit(){};
        Deposit(double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax);
        unsigned int getId() const;
        std::chrono::months getTerm() const;
        unsigned int getTermUnsignedInt() const;
        unsigned int getCapitalGainsTax() const;
        double getBalance() const;
        bank_rate getRate() const;
        std::string getCurrency() const;
        void setRate(bank_rate rate);
        void convert(std::string currency, bank_rate exchange_rate);
        double calculateProfit() const;

        // Overloading operators
        friend std::ostream& operator<<(std::ostream &os, const Deposit &d);
        bool operator==(const Deposit &d) const;
        bool operator!=(const Deposit &d) const;

        // Reading and saving from file
        Deposit(const std::istream &is);
        friend void saveToFile(std::ostream &os, const Deposit &d);

};

#endif