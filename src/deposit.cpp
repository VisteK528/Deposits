#include "deposit.hpp"

// Deposit::Deposit(const std::istream &is)
// {
//     std::stringstream input;
//     input << is.rdbuf();
//     std::vector<std::string> arguments;
//     while (input.good())
//     {
//         std::string argument;
//         getline(input, argument, ',');
//         argument.erase(std::remove_if(argument.begin(), argument.end(), isspace), argument.end());
//         arguments.push_back(argument);
//     }
//     int id = std::stoi(arguments[0]);
//     double balance = std::stod(arguments[1]);
//     std::string currency = arguments[2];
//     bank_rate rate = std::stod(arguments[3]);
//     int term_months = std::stoi(arguments[4]);
//     int capital_gains_tax = std::stoi(arguments[5]);
//     if(balance < 0)
//     {
//         throw InvalidBalanceInputValueError("Balance value cannot be negative!");
//     }
//     else
//     {
//         this->balance = balance*100;
//     }
//     setCurrency(currency);
//     setRate(rate);
//     setTerm(term_months);
//     setId(id);
//     setCapitalGainsTax(capital_gains_tax);
// }

bank_rate Deposit::getRate() const
{
    return this->rate/10000;
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

bool Deposit::operator==(const Deposit &d) const
{
    if(balance == d.balance && rate == d.rate && currency == d.currency && term.count() == d.term.count() && capital_gains_tax == d.capital_gains_tax) return true;
    return false;
}

bool Deposit::operator!=(const Deposit &d) const
{
    if(!operator==(d)) return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Deposit &d)
{
    d.print(os);
    return os;
}

double Deposit::calculateProfit() const
{
    unsigned int integer_profit = 0;
    double lenth_factor = term.count()/8640.;
    double tax = (100-capital_gains_tax)/100.;
    double double_profit = balance*lenth_factor*rate*tax;
    integer_profit = (int)round(double_profit/1000000);
    return (double)integer_profit/100;
}

void Deposit::saveToFile(std::ostream &os) const
{
    os << std::to_string(id) << '\n';
    os << product_type << '\n';
    os << std::to_string(getBalance()) << '\n';
    os << currency << '\n';
    os << std::to_string(getRate()) << '\n';
    os << std::to_string(term.count()) << '\n';
    os << std::to_string(capital_gains_tax) << '\n';
}

void Deposit::print(std::ostream &os) const
{
    os<<"ID: "<<id<<'\n';
    os<<"Product type: "<< product_type<<'\n';
    os<<"Balance: "<< getBalance()<<' '<<currency<<'\n';
    os<<"Term: "<<getTerm()<<" hours"<<'\n';
    os<<"Rate: "<<getRate()<<"%\n";
    os<<"Capital gains tax: "<<capital_gains_tax<<" %\n";
}

// Traditional Deposit
TraditionalDeposit::TraditionalDeposit(double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax)
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
    this->product_type = "TraditionalDeposit";
}

void TraditionalDeposit::setTerm(int term_months)
{
    if(term_months < 0)
    {
        throw InvalidTermValueError("Time in months cannot be negative!");
    }
    else
    {
        this->term = std::chrono::hours(term_months*720);
        this->term_months = std::chrono::months(term_months);
    }
}

void TraditionalDeposit::print(std::ostream &os) const
{
    os<<"ID: "<<id<<'\n';
    os<<"Product type: "<< product_type<<'\n';
    os<<"Balance: "<< getBalance()<<' '<<currency<<'\n';
    os<<"Term: "<<getTerm()<<" months"<<'\n';
    os<<"Rate: "<<getRate()<<"%\n";
    os<<"Capital gains tax: "<<capital_gains_tax<<" %\n";
}

unsigned int TraditionalDeposit::getTerm() const
{
    return this->term_months.count();
}

double TraditionalDeposit::calculateProfit() const
{
    unsigned int integer_profit = 0;
    double lenth_factor = term_months.count()/12.;
    double tax = (100-capital_gains_tax)/100.;
    double double_profit = balance*lenth_factor*rate*tax;
    integer_profit = (int)round(double_profit/1000000);
    return (double)integer_profit/100;
}

void TraditionalDeposit::saveToFile(std::ostream &os) const
{
    os << std::to_string(id) << '\n';
    os << product_type << '\n';
    os << std::to_string(getBalance()) << '\n';
    os << currency << '\n';
    os << std::to_string(getRate()) << '\n';
    os << std::to_string(term_months.count()) << '\n';
    os << std::to_string(capital_gains_tax) << '\n';
}

// Currency deposit
void CurrencyDeposit::convert(std::string currency, bank_rate exchange_rate)
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

// Additive deposit

void AdditiveDeposit::addMoney(int month, double amount)
{
    if(month < 0)
    {
        throw InvalidMonthValueError("Cannot add money on negative month!");
    }
    else if(month > term_months.count())
    {
        throw InvalidMonthValueError("Cannot add money when deposit term elapsed!");
    }

    if(amount < 0)
    {
        throw InvalidAddMoneyAmountError("Cannot add negative amount of money to the deposit!");
    }
    overall_added += amount*100;
    std::fill(added_money.begin()+month, added_money.end(), amount*100);
}

double AdditiveDeposit::calculateProfit() const
{
    double profit = 0;
    double tax = (100-capital_gains_tax)/100.;
    for(double money: added_money)
    {
        profit += (balance-overall_added+money*100)*(1/12.)*rate;
    }
    double new_balance = balance/100. + profit*tax;
    return new_balance;
}

// Progressive deposit
ProgressiveDeposit::ProgressiveDeposit(double balance, std::vector<bank_rate> rate_coefficients, std::string currency, int term_months, int id, int capital_gains_tax)
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
    setTerm(term_months);
    setRate(rate_coefficients);
    setId(id);
    setCapitalGainsTax(capital_gains_tax);
    this->product_type = "ProgressiveDeposit";
}

void ProgressiveDeposit::setRate(std::vector<bank_rate> rate_coefficients)
{
    this->rate_coefficients = rate_coefficients;
}

void ProgressiveDeposit::saveToFile(std::ostream &os) const
{
    os << std::to_string(id) << '\n';
    os << product_type << '\n';
    os << std::to_string(getBalance()) << '\n';
    os << currency << '\n';
    for(auto &r: rate_coefficients)
    {
        os<<r<<',';
    }
    os<<'\n';
    os << std::to_string(term.count()) << '\n';
    os << std::to_string(capital_gains_tax) << '\n';
}

void ProgressiveDeposit::print(std::ostream &os) const
{
    os<<"ID: "<<id<<'\n';
    os<<"Product type: "<< product_type<<'\n';
    os<<"Balance: "<< getBalance()<<' '<<currency<<'\n';
    os<<"Term: "<<getTerm()<<" months"<<'\n';
    os<<"Rate Coefficients: ";
    int i = 1;
    for(auto &r: rate_coefficients)
    {
        os<<"\tMonth number: "<<i<<'\t'<<"Rate: "<<r<<'\n';
    }
    os<<"Capital gains tax: "<<capital_gains_tax<<" %\n";
}

double ProgressiveDeposit::calculateProfit() const
{
    double profit = 0;
    double tax = (100-capital_gains_tax)/100.;
    for(bank_rate month_rate: rate_coefficients)
    {
        profit += balance*(1/12.)*month_rate;
    }
    double new_balance = balance/100. + profit*tax;
    return new_balance;
}

// ShortTerm deposit
ShortTimeDeposit::ShortTimeDeposit(double balance, bank_rate rate_coefficients, std::string currency, int term_months, int id)
{
    if(balance < 0)
    {
        throw InvalidBalanceInputValueError("Balance value cannot be negative!");
    }
    else if(balance*100 < MIN_BALANCE)
    {
        throw InvalidBalanceInputValueError("Balance value is not sufficient to create ShortTermDeposit!");
    }
    else
    {
        this->balance = balance*100;
    }
    setCurrency(currency);
    setTerm(term_months);
    setRate(rate_coefficients);
    setId(id);
    setCapitalGainsTax(0);
    this->product_type = "ShortTermDeposit";
}
