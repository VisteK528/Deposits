#include "src/deposit.hpp"
#include <iostream>
#include "src/bank_account.hpp"
#include <sstream>
#include "src/exceptions.hpp"

void wait_for_response()
{
    std::cin.ignore();
    std::cout<<"Please, press enter to continue...";
    std::cin.ignore();
}

int getID()
{
    std::string string_id;
    int id;
    std::cout<<"Please, type the ID of the deposit: ";
    std::cin>>string_id;
    try
    {
        id = std::stoi(string_id);
        if(id < 0)
        {
            throw InvalidIdValueError("ID number cannot be negative!");
        }
    }
    catch(const InvalidIdValueError& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << "ID number has to be a number!" << '\n';
    }
    return id;
}

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cerr<<"Expected 4 arguments, but insted got "<<argc<<" arguments!"<<std::endl;
        return 1;
    }
    std::string name;
    std::string surname;
    std::string birth_date;
    std::stringstream stream;
    stream<<argv[1];
    stream>>name;
    stream.clear();

    stream<<argv[2];
    stream>>surname;
    stream.clear();
    stream<<argv[3];
    stream>>birth_date;
    stream.clear();
    BankAccount account(name, surname, birth_date);
    account.addDeposit(972.71, 3.14, "PLN", 6);
    account.addDeposit(1364.12, 2.71, "PLN", 6);
    account.addDeposit(1410.43, 3.14, "EUR", 6);
    account.addDeposit(1945.01, 3.14, "USD", 6);
    std::cout<<"Hello, "<< account.getName() <<' '<<account.getSurname()<<'!'<<std::endl;
    std::cout<<"Thank you for choosing PROI Financial Services©!"<<std::endl;
    while(true)
    {
        std::cout<<"Please select an action from the list:"<<std::endl;
        std::cout<<"\t1. Show account data"<<std::endl;
        std::cout<<"\t2. Find deposit by ID"<<std::endl;
        std::cout<<"\t3. Add new deposit"<<std::endl;
        std::cout<<"\t4. Remove deposit"<<std::endl;
        std::cout<<"\t5. Modify deposit"<<std::endl;
        std::cout<<"\t6. Show expected profits"<<std::endl;
        std::cout<<"\t7. Exit"<<std::endl<<std::endl;
        std::cout<<"Your choice: ";
        int choice;
        try
        {
            std::string string_choice;
            std::cin>>string_choice;
            choice = std::stoi(string_choice);
            if(choice < 1 || choice > 8)
            {
                throw InvalidChoiceValue("Choice value has to be a number from 1 to 8!");
            }
        }
        catch(const InvalidChoiceValue& e)
        {
            std::cerr << e.what() << '\n';
            std::cerr <<"Please try again!"<<'\n';
            wait_for_response();
            system("clear");
            continue;
        }
        catch(const std::exception& e)
        {
            std::cerr<<"Choice value cannot be a character or string! Please try again!"<<std::endl;
            wait_for_response();
            system("clear");
            continue;
        }

        if(choice == 1)
        {
            std::cout<<"Owner's data"<<std::endl;
            std::cout<<"\t1. Name: "<<account.getName()<<std::endl;
            std::cout<<"\t2. Surname: "<<account.getSurname()<<std::endl;
            std::cout<<"\t3. Birthdate: "<<account.getBirthDate()<<std::endl<<std::endl;
            std::cout<<"Posessed products:"<<std::endl<<std::endl;
            std::vector<Deposit> products = account.getDeposits();
            for(auto product: products)
            {
                std::cout<<product<<std::endl;
            }
        }
        else if(choice == 2)
        {
            int id = getID();
            try
            {
                const Deposit found_deposit = account.findDeposit(id);
                std::cout<<"Successfully found the deposit with given ID number"<<std::endl;
                std::cout<<found_deposit<<std::endl;
            }
            catch(const ProductsInvalidIndexError& e)
            {
                std::cerr<<e.what()<<'\n';
            }
        }
        else if(choice == 3)
        {
            double balance;
            int term;
            double rate;
            std::string balance_string;
            std::string term_string;
            std::string rate_string;
            try
            {
                std::string currency;
                std::cout<<"Please, type the amount you want to locate on the deposit: ";
                std::cin>>balance_string;
                try
                {
                    balance = std::stod(balance_string);
                }
                catch(const std::exception& e)
                {
                    throw InvalidBalanceInputValueError("Balance value cannot be a string!");
                }

                std::cout<<"Please, type the currency of the deposit: ";
                std::cin>>currency;
                std::cout<<"Please, type the rate of the deposit: ";
                std::cin>>rate_string;
                try
                {
                    rate = std::stod(rate_string);
                }
                catch(const std::exception& e)
                {
                    throw InvalidRateValueError("Rate value cannot be a string!");
                }

                std::cout<<"Please, type the term of the deposit in months: ";
                std::cin>>term_string;
                try
                {
                    term = std::stoi(term_string);
                }
                catch(const std::exception& e)
                {
                    throw InvalidTermValueError("Term value cannot be a string!");
                }

                account.addDeposit(balance, rate, currency, term);
                std::cout<<"Successfully added new deposit to your account!"<<std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr<<"Failed to create a deposit due to en error: "<< '\n';
                std::cerr << e.what() << '\n';
            }
        }
        else if(choice == 4)
        {
            int id = getID();

            try
            {
                account.removeDeposit(id);
                std::cout<<"Successfully removed the deposit with given ID"<<std::endl;
            }
            catch(const ProductsInvalidIndexError& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else if(choice == 5)
        {
            int id = getID();
            try
            {
                const Deposit& found_deposit = account.findDeposit(id);
                std::cout<<"Deposit to be modified: "<<std::endl;
                std::cout<<found_deposit<<std::endl<<std::endl;

                int choice;
                std::cout<<"List of possible modifications: "<<std::endl;
                std::cout<<"\t1. Change rate of the deposit"<<std::endl;
                std::cout<<"\t2. Convert the deposit to specified currency"<<std::endl;
                std::cout<<"\t3. Go back"<<std::endl;
                std::cout<<"Your choice: ";
                try
                {
                    std::string string_choice;
                    std::cin>>string_choice;
                    choice = std::stoi(string_choice);
                    if(choice < 1 || choice > 8)
                    {
                        throw InvalidChoiceValue("Choice value has to be a number from 1 to 8!");
                    }
                }
                catch(const InvalidChoiceValue& e)
                {
                    std::cerr<<e.what()<<'\n';
                }
                catch(const std::exception& e)
                {
                    std::cerr<<"Choice value cannot be a character or string! Please try again!"<<std::endl;
                }
                std::cout<<"\n\n";

                if(choice == 1)
                {
                    std::string string_rate;
                    double rate;
                    std::cout<<"Please, type new rate value: ";
                    try
                    {
                        std::cin>>string_rate;
                        try
                        {
                            rate = std::stod(string_rate);
                        }
                        catch(const std::exception& e)
                        {
                            throw InvalidRateValueError("Rate value cannot be a string!");
                        }
                        account.setDepositRate(id, rate);
                        std::cout<<"Successfully changed the rate of the deposit"<<std::endl;
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                else if(choice == 2)
                {
                    double exchange_rate;
                    std::string currency_symbol;
                    std::cout<<"Please, type currency symbol: ";
                    std::cin>>currency_symbol;
                    try
                    {
                        std::string string_exchange_rate;
                        std::cout<<"Please, type exchange rate of "<<currency_symbol<<'/';
                        std::cout<<found_deposit.getCurrency()<<": ";
                        std::cin>>string_exchange_rate;
                        try
                        {
                            exchange_rate = std::stod(string_exchange_rate);
                        }
                        catch(const std::exception& e)
                        {
                            throw InvalidRateValueError("Exchange rate cannot be a string!");
                        }
                        account.convertDeposit(id, currency_symbol, exchange_rate);
                        std::cout<<"Successfully converted the deposit to "<<currency_symbol<<std::endl;
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                }
                else
                {
                    std::system("clear");
                    continue;
                }
            }
            catch(const ProductsInvalidIndexError& e)
            {
                std::cerr << e.what() << '\n';
            }

        }
        else if(choice == 6)
        {
            int id = getID();
            try
            {
                Deposit found_deposit = account.findDeposit(id);
                std::cout<<"Properties of the deposit with ID: "<<id<<std::endl;
                std::cout<<found_deposit<<std::endl;
                std::cout<<"Expected profits after "<<found_deposit.getTerm()<<" months: ";
                std::cout<<found_deposit.calculateProfit()<<' '<<found_deposit.getCurrency()<<std::endl;
            }
            catch(const ProductsInvalidIndexError& e)
            {
                std::cerr << e.what() << '\n';
            }

        }
        else if(choice == 7)
        {
            std::cout<<"Thank you for choosing PROI Financial Services©!"<<std::endl;
            break;
        }
        wait_for_response();
        std::system("clear");
    }
    return 0;

}