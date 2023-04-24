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
        virtual void print(std::ostream &os) const override;

    public:
        virtual ~Deposit() = default;
        unsigned int getCapitalGainsTax() const;
        bank_rate getRate() const;
        void setRate(bank_rate rate);

        // Virtual functions
        virtual double calculateProfit() const;
        virtual void saveToFile(std::ostream &os) const override;


        // Operators
        virtual bool operator==(const Deposit &d) const;
        virtual bool operator!=(const Deposit &d) const;
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
    public:
        CurrencyDeposit(){};
        CurrencyDeposit(double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax): TraditionalDeposit(balance, rate, currency, term_months, id, capital_gains_tax){this->product_type="CurrencyDeposit";}
        void convert(std::string currency, bank_rate exchange_rate);
};

class AdditiveDeposit: public TraditionalDeposit
{
    private:
        unsigned int overall_added = 0;
        std::vector<double> added_money;
    public:
        AdditiveDeposit(){};
        AdditiveDeposit(double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax);
        double calculateProfit() const override;
        void addMoney(int addition_month, double amount);
        void saveToFile(std::ostream &os) const override;
};

class ProgressiveDeposit: public Deposit
{
    private:
        using Deposit::getRate;
        std::vector<bank_rate> rate_coefficients;

        std::chrono::months term_months;

        // Overried methods
        virtual void setTerm(int term) override;
        void print(std::ostream &os) const override;
    public:
        ProgressiveDeposit(){};
        ProgressiveDeposit(double balance, std::vector<bank_rate> rate_coefficients, std::string currency, int term_months, int id, int capital_gains_tax);
        std::vector<bank_rate> getRates() const;
        double calculateProfit() const override;
        void setRate(std::vector<bank_rate> rate_coefficients);
        void saveToFile(std::ostream &os) const override;
        unsigned int getTerm() const override;
};

class ShortTimeDeposit: public Deposit
{
    private:
        unsigned int MIN_BALANCE = 2000000;
    public:
        ShortTimeDeposit(){};
        ShortTimeDeposit(double balance, bank_rate rate, std::string currency, int term_hours, int id);
};


#endif