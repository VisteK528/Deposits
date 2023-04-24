#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "factory.hpp"
#include "bank_account.hpp"
#include <memory>
#include <iostream>

class Interface
{
    private:
        typedef enum {DATA=1, FIND, ADD, REMOVE, MODIFY, PROFITS, EXIT} choices;
        bool running = true;
        std::unique_ptr<BankAccount> account;
        std::unique_ptr<DepositFactory> factory;
        unsigned int capital_gains_tax;
        int getChoiceValue(int min_value, int max_value) const;
        void waitForResponse() const;
        int getDepositId() const;
    public:
        Interface(std::string name, std::string surname, std::string birth_date, int capital_gains_tax);
        void run();

};

#endif