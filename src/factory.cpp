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