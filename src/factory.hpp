#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "deposit.hpp"

enum DEPOSIT_TYPE{TRADITIONAL, CURRENCY, ADDITIVE};

class DepositFactory
{
    public:
        std::shared_ptr<TraditionalDeposit> createTraditionalDeposit(DEPOSIT_TYPE deposit_type, double balance, bank_rate rate, std::string currency, int term_months, int id, int capital_gains_tax) const;
        std::shared_ptr<ProgressiveDeposit> createProgressiveDeposit(double balance, std::vector<double> rate_coefficients, std::string currency, int term_months, int id, int capital_gains_tax) const;
        std::shared_ptr<ShortTimeDeposit> createShortTimeDeposit(double balance, bank_rate rate, std::string currency, int term_hours, int id) const;
};


#endif