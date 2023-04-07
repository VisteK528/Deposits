#include "deposit.hpp"

Deposit::Deposit(double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax)
{
    if(balance < 0)
    {
        throw InvalidBalanceInputValueError("Balance value cannot be negative!");
    }
    else
    {
        this->balance = balance*100;
    }
    setCurrency(currency);
    setRate(rate);
    setTerm(term_months);
    setId(id);
    setCapitalGainsTax(capital_gains_tax);
}

double Deposit::getBalance() const
{
    return (double)this->balance/100;
}

bank_rate Deposit::getRate() const
{
    return this->rate/10000;
}

std::string Deposit::getCurrency() const
{
    return this->currency;
}

unsigned int Deposit::getId() const
{
    return this->id;
}

unsigned int Deposit::getTerm() const
{
    return this->term_months;
}

unsigned int Deposit::getCapitalGainsTax() const
{
    return this->capital_gains_tax;
}

void Deposit::setRate(bank_rate rate)
{
    if(rate < 0)
    {
        throw InvalidRateValueError("Rate value cannot be negative!");
    }
    else
    {
        this->rate = rate*10000;
    }
}

void Deposit::setCurrency(std::string currency)
{
    if(currency.length() != 3)
    {
        throw InvalidCurrencySymbolError("Currency symbol does not satisfy ISO 4217 standard!");
    }
    else
    {
        this->currency = currency;
    }
}

void Deposit::setTerm(int term_months)
{
    if(term_months < 0)
    {
        throw InvalidTermValueError("Time cannot be negative!");
    }
    else
    {
        this->term_months = term_months;
    }
}

void Deposit::setId(int id)
{
    if(id < 0)
    {
        throw InvalidIdValueError("Id value should not be negative!");
    }
    else
    {
        this->id = id;
    }
}

void Deposit::setCapitalGainsTax(int capital_gains_tax)
{
    if(capital_gains_tax < 0)
    {
        throw InvalidCapitalGainsTaxValueError("Capital gains tax value has to be greater than 0%!");
    }
    else if(capital_gains_tax > 100)
    {
        throw InvalidCapitalGainsTaxValueError("Capital gains tax cannot be greater than 100%!");
    }
    else
    {
        this->capital_gains_tax = capital_gains_tax;
    }
}

void Deposit::convert(std::string currency, bank_rate exchange_rate)
{
    if(this->currency != currency)
    {
        if(exchange_rate < 0)
        {
            throw InvalidRateValueError("Exchange value cannot be negative!");
        }
        setCurrency(currency);

        // Converting Balance
        double float_balance = (balance/(exchange_rate*100))*100;
        this->balance = round(float_balance);
    }
}

double Deposit::calculateProfit() const
{
    unsigned int integer_profit = 0;
    double lenth_factor = term_months/12.;
    double tax = (100-capital_gains_tax)/100.;
    double double_profit = balance*lenth_factor*rate*tax;
    integer_profit = (int)round(double_profit/1000000);
    return (double)integer_profit/100;
}


std::ostream &operator<<(std::ostream &os, const Deposit &d)
{
    os<<"Deposit with ID: "<<d.id<<std::endl;
    os<<"\tBalance: "<<d.balance/100.<<' '<<d.currency<<std::endl;
    os<<"\tAnnual interest rate: "<<d.rate/10000.<<'%'<<std::endl;
    os<<"\tTerm: "<<d.term_months<<" months";
    return os;
}

bool Deposit::operator==(const Deposit &d) const
{
    if(balance == d.balance && rate == d.rate && currency == d.currency && term_months == d.term_months && capital_gains_tax == d.capital_gains_tax) return true;
    return false;
}

bool Deposit::operator!=(const Deposit &d) const
{
    if(!operator==(d)) return true;
    return false;
}