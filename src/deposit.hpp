#ifndef DEPOSIT_HPP
#define DEPOSIT_HPP

#include "product.hpp"
#include <math.h>
#include <vector>
#include <sstream>
#include <algorithm>

/*

Rodzaje lokat i przedmiotow finansowych

Klasa bazowa:
1. Product - dziedziczą po niej klasy Deposit oraz potencjalnie klasa Loan

Klasy Deposit:
1. Deposit - klasa bazowa lokat
1.1. Traditional Deposit - lokata tradycyjna
1.1.1. Lokata walutowa - lokata tradycyjna z możliwością ustawienia waluty na inną niż bazowa plus z możliwością przewalutowywania
1.2. Dynamic Deposit - lokata z dynamicznie zmieniającym się oprocentowaniem
1.2.1 Progressive Deposit - lokata z progresywnie narastającym oprocentowaniem
1.2.2 Degressive Deposit - lokata z sukcesywnie zmniejszającym się oprocentowaniem
1.3. OneDayDeposit - lokata jednodniowa, nie podlega podatkowi Belki
1.3.1 OvernightDeposit - lokata nocna, trwa 12h

*/

/*
Lokata progresywna działanie


*/

typedef double bank_rate;

class Deposit: public Product
{
    protected:
        // Base Deposit variables
        unsigned int capital_gains_tax;
        bank_rate rate;

        // Methods
        void setCapitalGainsTax(int capital_gains_tax);

        // Overrried methods
        virtual void print(std::ostream &os) const override {os<<"Hello";}

    public:
        virtual ~Deposit() = default;
        unsigned int getCapitalGainsTax() const;
        bank_rate getRate() const;
        void setRate(bank_rate rate);

        //Overried methods
        //virtual unsigned int getTerm() const override;

        // Virtual functions
        virtual double calculateProfit() const {return 5.;}
        virtual void saveToFile(std::ostream &os) const override {os<<"Hello World";}


        // Operators
        bool operator==(const Deposit &d) const;
        bool operator!=(const Deposit &d) const;
        friend std::ostream& operator<<(std::ostream& os, const Deposit &d);

};
class TraditionalDeposit: public Deposit
{
    protected:
        std::chrono::months term_months;

        // Overried methods
        virtual void setTerm(int term) override;
        virtual void print(std::ostream &os) const override;

    public:
        // Constructors
        TraditionalDeposit(){};
        TraditionalDeposit(double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax);
        virtual ~TraditionalDeposit() = default;

        // Overried methods
        unsigned int getTerm() const override;
        double calculateProfit() const override;

        // Saving to file
        virtual void saveToFile(std::ostream &os) const override;
};

class CurrencyDeposit: public TraditionalDeposit
{
    private:
        //virtual void print(std::ostream &os) const override;
    public:
        CurrencyDeposit(){};
        CurrencyDeposit(double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax): TraditionalDeposit(balance, rate, currency, term_months, id, capital_gains_tax){this->product_type="CurrencyDeposit";}
        void convert(std::string currency, bank_rate exchange_rate);
};

// class DynamicDeposit: public Deposit
// {
//     protected:
//         virtual void print(std::ostream &os) const override;
//     public:
//         double calculateProfit() const override;
//         unsigned int getTerm() const override;
// };

// class OneDayDeposit: public Deposit
// {
//     protected:
//         virtual void print(std::ostream &os) const override;
//     public:
//         double calculateProfit() const override;
// };

// class OvernightDeposit: public OneDayDeposit
// {
//     public:

// };


#endif