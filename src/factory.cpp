#include "factory.hpp"


std::shared_ptr<TraditionalDeposit> DepositFactory::createTraditionalDeposit(DEPOSITS deposit_type, double balance, bank_rate rate, std::string currency, int term_months, int capital_gains_tax, int id) const
{
    switch (deposit_type)
    {
    case CURRENCY:
        return std::make_shared<CurrencyDeposit>(balance, rate, currency, term_months, id, capital_gains_tax);
        break;
    case ADDITIVE:
        return std::make_shared<AdditiveDeposit>(balance, rate, currency, term_months, id, capital_gains_tax);
        break;
    default:
        return std::make_shared<TraditionalDeposit>(balance, rate, currency, term_months, id, capital_gains_tax);
        break;
    }
}

std::shared_ptr<ProgressiveDeposit> DepositFactory::createProgressiveDeposit(double balance, std::vector<bank_rate> rate_coefficients, std::string currency, int term_months, int capital_gains_tax, int id) const
{
   return std::make_shared<ProgressiveDeposit>(balance, rate_coefficients,currency, term_months, id, capital_gains_tax);
}

std::shared_ptr<ShortTimeDeposit> DepositFactory::createShortTimeDeposit(double balance, bank_rate rate, std::string currency, int term_hours, int id) const
{
    return std::make_shared<ShortTimeDeposit>(balance, rate, currency, term_hours, id);
}

std::shared_ptr<TraditionalDeposit> DepositFactory::createTraditionalDeposit(DEPOSITS deposit_type, const std::istream &is) const
{
    std::vector<std::string> arguments = extractArguments(is);
    int id = std::stoi(arguments[0]);
    double balance = std::stod(arguments[2]);
    std::string currency = arguments[3];
    if(deposit_type != ADDITIVE)
    {
        bank_rate rate = std::stod(arguments[4]);
        int term_months = std::stoi(arguments[5]);
        int capital_gains_tax = std::stoi(arguments[6]);
        return createTraditionalDeposit(deposit_type, balance, rate, currency, term_months, capital_gains_tax, id);
    }
    else
    {
        double overall_added = std::stod(arguments[4]);
        bank_rate rate = std::stod(arguments[6]);
        int term_months = std::stoi(arguments[7]);
        int capital_gains_tax = std::stoi(arguments[8]);

        std::vector<double> added_money_by_months;
        std::stringstream added_money_by_months_stream(arguments[5]);
        for(int i = 0; i < term_months; i++)
        {
            std::string addded_money_str;
            getline(added_money_by_months_stream, addded_money_str, ',');
            addded_money_str.erase(std::remove_if(addded_money_str.begin(), addded_money_str.end(), isspace), addded_money_str.end());
            added_money_by_months.push_back(std::stod(addded_money_str));
        }
        return std::make_shared<AdditiveDeposit>(balance, rate, currency, term_months, id, capital_gains_tax, overall_added, added_money_by_months);
    }
}

std::shared_ptr<ProgressiveDeposit> DepositFactory::createProgressiveDeposit(const std::istream &is) const
{
    std::vector<std::string> arguments = extractArguments(is);
    int id = std::stoi(arguments[0]);
    double balance = std::stod(arguments[2]);
    std::string currency = arguments[3];
    int term_months = std::stoi(arguments[5]);
    int capital_gains_tax = std::stoi(arguments[6]);

    std::vector<bank_rate> rates;
    std::stringstream rates_stream(arguments[4]);
    for(int i = 0; i<term_months; i++)
    {
        std::string rate_str;
        getline(rates_stream, rate_str, ',');
        rate_str.erase(std::remove_if(rate_str.begin(), rate_str.end(), isspace), rate_str.end());
        rates.push_back(std::stod(rate_str));
    }
    return createProgressiveDeposit( balance, rates, currency, term_months, capital_gains_tax, id);
}

std::shared_ptr<ShortTimeDeposit> DepositFactory::createShortTimeDeposit(const std::istream &is) const
{
    std::vector<std::string> arguments = extractArguments(is);
    int id = std::stoi(arguments[0]);
    double balance = std::stod(arguments[2]);
    std::string currency = arguments[3];
    bank_rate rate = std::stod(arguments[4]);
    int term_hours = std::stoi(arguments[5]);
    return createShortTimeDeposit(balance, rate, currency, term_hours, id);
}

std::vector<std::string> DepositFactory::extractArguments(const std::istream &is) const
{
    std::stringstream input;
    input << is.rdbuf();
    std::vector<std::string> arguments;
    while (input.good())
    {
        std::string argument;
        getline(input, argument, '\n');
        argument.erase(std::remove_if(argument.begin(), argument.end(), isspace), argument.end());
        arguments.push_back(argument);
    }
    return arguments;
}