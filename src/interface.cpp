#include "interface.hpp"

Interface::Interface(std::string name, std::string surname, std::string birth_date, int capital_gains_tax)
{
    this->account = std::make_unique<BankAccount>(name, surname, birth_date);
    this->factory = std::make_unique<DepositFactory>();
    if(capital_gains_tax < 0)
    {
        throw InvalidCapitalGainsTaxValueError("Capital gains tax has to be greater than or equal to 0!");
    }
    this->capital_gains_tax = capital_gains_tax;
}

void Interface::waitForResponse() const
{
    std::cin.ignore();
    std::cout<<"Please, press enter to continue...";
    std::cin.ignore();
}

int Interface::getDepositId() const
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

int Interface::getChoiceValue(int min_value, int max_value) const
{
    int choice = 0;
    std::string string_choice;
    try
    {
        std::cin>>string_choice;
        choice = std::stoi(string_choice);
        if(choice < min_value || choice > max_value)
        {
            throw InvalidChoiceValue("Choice value has to be a number from "+std::to_string(min_value)+" to "+std::to_string(max_value)+"!");
        }
    }
    catch(const InvalidChoiceValue& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr <<"Please try again!"<<'\n';
        waitForResponse();
        system("clear");
    }
    catch(const std::exception& e)
    {
        std::cerr<<"Choice value cannot be a character or string! Please try again!"<<std::endl;
        waitForResponse();
        system("clear");
    }
    return choice;
}

void Interface::run()
{
    // Dodaję tutaj parę lokat, aby łatwiej można było testować funkcjonalność programu
    account->addDeposit(factory->createTraditionalDeposit(TRADITIONAL, 972.71, 3.14, "PLN", 6, 19));
    account->addDeposit(factory->createTraditionalDeposit(CURRENCY, 1410.43, 3.14, "EUR", 6, 19));
    account->addDeposit(factory->createTraditionalDeposit(TRADITIONAL, 1364.12, 2.71, "PLN", 6, 19));
    account->addDeposit(factory->createProgressiveDeposit(2000, {3.14, 3.14, 3.14, 3.14, 3.14, 3.14}, "PLN", 6, 19));
    account->addDeposit(factory->createTraditionalDeposit(ADDITIVE, 2000, 3.14, "PLN", 6, 19));

    std::cout<<"Hello, "<< account->getName() <<' '<<account->getSurname()<<'!'<<std::endl;
    std::cout<<"Thank you for choosing PROI Financial Services©!"<<std::endl;
    while(running)
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
        choices choice = static_cast<choices>(getChoiceValue(1, 7));


        try
        {
            switch(choice)
            {
                case DATA:
                {
                    std::cout<<*account<<std::endl;
                    break;
                }

                case FIND:
                {
                    int id = getDepositId();
                    const Deposit& found_deposit = account->findDeposit(id);
                    std::cout<<"Successfully found the deposit with given ID number"<<std::endl;
                    std::cout<<found_deposit<<std::endl;
                    break;
                }

                case ADD:
                {
                    std::cout<<"List of available deposit types: "<<std::endl;
                    std::cout<<"1. Traditional Deposit"<<std::endl;
                    std::cout<<"2. Currency Deposit"<<std::endl;
                    std::cout<<"3. Additive Deposit"<<std::endl;
                    std::cout<<"4. Progressive Deposit"<<std::endl;
                    std::cout<<"5. ShorTerm Deposit"<<std::endl;
                    std::cout<<"Your choice: ";
                    DEPOSITS deposit_choice = static_cast<DEPOSITS>(getChoiceValue(1, 5));


                    double balance;
                    std::string currency;
                    std::string balance_string;

                    std::cout<<"Please, type the amount you want to locate on the deposit: ";
                    std::cin>>balance_string;
                    balance = std::stod(balance_string);
                    std::cout<<"Please, type the currency of the deposit: ";
                    std::cin>>currency;
                    switch(deposit_choice)
                    {
                        case TRADITIONAL:
                        case CURRENCY:
                        case ADDITIVE:
                        {
                            int term;
                            double rate;
                            std::string term_string;
                            std::string rate_string;

                            std::cout<<"Please, type the rate of the deposit: ";
                            std::cin>>rate_string;
                            rate = std::stod(rate_string);


                            std::cout<<"Please, type the term of the deposit in months: ";
                            std::cin>>term_string;
                            term = std::stoi(term_string);
                            switch(deposit_choice)
                            {
                            case DEPOSITS::TRADITIONAL:
                                account->addDeposit(factory->createTraditionalDeposit(deposit_choice, balance, rate, currency, term, capital_gains_tax));
                                break;
                            case DEPOSITS::CURRENCY:
                                account->addDeposit(factory->createTraditionalDeposit(deposit_choice, balance, rate, currency, term, capital_gains_tax));
                                break;
                            case DEPOSITS::ADDITIVE:
                                account->addDeposit(factory->createTraditionalDeposit(deposit_choice, balance, rate, currency, term, capital_gains_tax));
                                break;
                            default:
                                break;
                            }
                            break;
                        }
                        case PROGRESSIVE:
                        {
                            std::vector<bank_rate> rate_coefficients;
                            int term;
                            std::string term_string;
                            std::cout<<"Please, type the term of the deposit in months: ";
                            std::cin>>term_string;
                            term = std::stoi(term_string);
                            std::string coefficient_str;
                            bank_rate coefficient;
                            rate_coefficients.reserve(term);
                            for(int i=0; i<term; i++)
                            {
                                std::cout<<"Please type "<<i+1<<" rate coefficient: ";
                                std::cin>>coefficient_str;
                                coefficient = std::stod(coefficient_str);
                                if(coefficient < 0)
                                {
                                    throw InvalidRateCoefficientValueError("Rate coefficient has to be number greater than 0!");
                                }
                                rate_coefficients[i] = coefficient;
                            }
                            account->addDeposit(factory->createProgressiveDeposit(balance, rate_coefficients, currency, term, capital_gains_tax));
                            break;
                        }
                        case SHORTTERM:
                        {
                            int term;
                            double rate;
                            std::string term_string;
                            std::string rate_string;

                            std::cout<<"Please, type the rate of the deposit: ";
                            std::cin>>rate_string;
                            rate = std::stod(rate_string);

                            std::cout<<"Please, type the term of the deposit in hours: ";
                            std::cin>>term_string;
                            term = std::stoi(term_string);

                            account->addDeposit(factory->createShortTimeDeposit(balance, rate, currency, term));
                            break;
                        }
                    }
                    break;
                }

                case REMOVE:
                {
                    int id = getDepositId();
                    account->removeDeposit(id);
                    std::cout<<"Successfully removed the deposit with given ID"<<std::endl;
                    break;
                }

                case MODIFY:
                {
                    int id = getDepositId();
                    const Deposit& found_deposit = account->findDeposit(id);
                    std::string deposit_type = found_deposit.getProductType();
                    std::cout<<"Deposit to be modified: "<<std::endl;
                    std::cout<<found_deposit<<std::endl<<std::endl;

                    int choice;
                    std::cout<<"List of possible modifications: "<<std::endl;
                    std::cout<<"\t1. Change rate of the deposit"<<std::endl;
                    if(deposit_type == "CurrencyDeposit")
                    {
                        std::cout<<"\t2. Convert the deposit to specified currency"<<std::endl;
                        std::cout<<"\t3. Go back"<<std::endl;
                        std::cout<<"Your choice: ";
                        choice = getChoiceValue(1, 3);
                    }
                    else if(deposit_type == "AdditiveDeposit")
                    {
                        std::cout<<"\t2. Add money to the deposit"<<std::endl;
                        std::cout<<"\t3. Go back"<<std::endl;
                        std::cout<<"Your choice: ";
                        choice = getChoiceValue(1, 3);
                    }
                    else
                    {
                        std::cout<<"\t2. Go back"<<std::endl;
                        std::cout<<"Your choice: ";
                        choice = getChoiceValue(1, 2);
                    }

                    if (choice == 1 && deposit_type == "ProgressiveDeposit")
                    {
                        std::shared_ptr<ProgressiveDeposit> progressive_deposit = std::dynamic_pointer_cast<ProgressiveDeposit>(account->findDepositPointer(id));
                        std::vector<bank_rate> rates = progressive_deposit->getRates();

                        std::string term_str;
                        std::string rate_str;
                        int term;
                        bank_rate rate;

                        std::cout<<"Please, type the number of rate you would like to change: ";
                        std::cin>>term_str;
                        std::cout<<"Please, type the new value of rate: ";
                        std::cin>>rate_str;
                        term = std::stoi(term_str);
                        if(term < 1 or abs(term) > rates.size())
                        {
                            throw InvalidTermValueError("Cannot change the specified rate number, less than 1 or greater than size of rates!");
                        }
                        rate = std::stod(rate_str);
                        rates[term-1] = rate;
                        progressive_deposit->setRate(rates);
                        std::cout<<"Successfully changed specified rate!"<<std::endl;

                    }
                    else if(choice == 1)
                    {
                        std::string string_rate;
                        double rate;
                        std::cout<<"Please, type new rate value: ";
                        std::cin>>string_rate;
                        rate = std::stod(string_rate);
                        account->setDepositRate(id, rate);
                        std::cout<<"Successfully changed the rate of the deposit"<<std::endl;
                    }
                    else if(choice == 2 && deposit_type == "CurrencyDeposit")
                    {
                        double exchange_rate;
                        std::string currency_symbol;
                        std::cout<<"Please, type currency symbol: ";
                        std::cin>>currency_symbol;
                        std::string string_exchange_rate;
                        std::cout<<"Please, type exchange rate of "<<currency_symbol<<'/';
                        std::cout<<found_deposit.getCurrency()<<": ";
                        std::cin>>string_exchange_rate;
                        exchange_rate = std::stod(string_exchange_rate);
                        account->convertDeposit(id, currency_symbol, exchange_rate);
                        std::cout<<"Successfully converted the deposit to "<<currency_symbol<<std::endl;
                    }
                    else if(choice == 2 && deposit_type == "AdditiveDeposit")
                    {
                        double new_money;
                        int term;
                        std::string new_money_str;
                        std::string term_str;
                        std::cout<<"Please, type number of month from the start of you Deposit when you would like to add money: ";
                        std::cin>>term_str;
                        std::cout<<"Please, type the amount of money you would like to add: ";
                        std::cin>>new_money_str;
                        new_money = std::stod(new_money_str);
                        term = std::stoi(term_str);
                        std::shared_ptr<AdditiveDeposit> additive_deposit = std::dynamic_pointer_cast<AdditiveDeposit>(account->findDepositPointer(id));
                        additive_deposit->addMoney(term, new_money);
                        std::cout<<"Balance has been updated successfully"<<std::endl;
                    }
                    break;
                }

                case PROFITS:
                {
                    int id = getDepositId();
                    std::shared_ptr<Deposit> found_deposit = account->findDepositPointer(id);
                    std::cout<<"Properties of the deposit with ID: "<<id<<std::endl;
                    std::cout<<*found_deposit<<std::endl;
                    if(found_deposit->getProductType() == "ShortTermDeposit")
                    {
                        std::cout<<"Expected profits after "<<found_deposit->getTerm()<<" hours: ";
                    }
                    else
                    {
                        std::cout<<"Expected profits after "<<found_deposit->getTerm()<<" months: ";
                    }
                    std::cout<<found_deposit->calculateProfit()<<' '<<found_deposit->getCurrency()<<std::endl;
                    break;
                }

                case EXIT:
                {
                    running = false;
                    std::cout<<"Thank you for choosing PROI Financial Services©!"<<std::endl;
                    continue;
                    break;
                }

                default:
                    break;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }


        waitForResponse();
        std::system("clear");
    }
}