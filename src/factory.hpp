#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "deposit.hpp"

typedef enum {TRADITIONAL=1, CURRENCY=2, ADDITIVE=3, PROGRESSIVE=4, SHORTTERM=5} DEPOSITS;

class DepositFactory
{
    private:
        std::vector<std::string> extractArguments(const std::istream &is) const;
    public:
        std::shared_ptr<TraditionalDeposit> createTraditionalDeposit(DEPOSITS deposit_type, double balance, bank_rate rate, std::string currency, int term_months, int capital_gains_tax, int id=1) const;
        std::shared_ptr<ProgressiveDeposit> createProgressiveDeposit(double balance, std::vector<double> rate_coefficients, std::string currency, int term_months, int capital_gains_tax, int id=1) const;
        std::shared_ptr<ShortTimeDeposit> createShortTimeDeposit(double balance, bank_rate rate, std::string currency, int term_hours, int id=1) const;
        std::shared_ptr<TraditionalDeposit> createTraditionalDeposit(DEPOSITS deposit_type, const std::istream &is) const;
        std::shared_ptr<ProgressiveDeposit> createProgressiveDeposit(const std::istream &is) const;
        std::shared_ptr<ShortTimeDeposit> createShortTimeDeposit(const std::istream &is) const;
};


#endif