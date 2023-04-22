#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "deposit.hpp"

typedef enum {TRADITIONAL=1, CURRENCY=2, ADDITIVE=3, PROGRESSIVE=4, SHORTTERM=5} DEPOSITS;

class DepositFactory
{
    public:
        std::shared_ptr<TraditionalDeposit> createTraditionalDeposit(DEPOSITS deposit_type, double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax) const;
        std::shared_ptr<ProgressiveDeposit> createProgressiveDeposit(double balance, std::vector<double> rate_coefficients, std::string currency, int term_months, int id, int capital_gains_tax) const;
        std::shared_ptr<ShortTimeDeposit> createShortTimeDeposit(double balance, bank_rate rate, std::string currency, int term_hours, int id) const;
};


#endif