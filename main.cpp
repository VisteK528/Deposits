#include "src/deposit.hpp"
#include <iostream>
#include "src/bank_account.hpp"
#include <sstream>
#include "src/exceptions.hpp"

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cerr<<"Expected 4 arguments, but insted got "<<argc<<" arguments!"<<std::endl;;
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
    std::cout<<"Witaj, "<< account.getName() <<' '<<account.getSurname()<<'!'<<std::endl;
    std::cout<<"Cieszymy się, że wybrałeś usługi PROI Financial Services©!"<<std::endl;
    while(true)
    {
        std::cout<<"Proszę wybierz akcję z listy:"<<std::endl;
        std::cout<<"\t1. Wyświetl dane o koncie"<<std::endl;
        std::cout<<"\t2. Wyświetl listę lokat"<<std::endl;
        std::cout<<"\t3. Wyświetl liczbę posiadanych lokat"<<std::endl;
        std::cout<<"\t4. Znajdź lokatę"<<std::endl;
        std::cout<<"\t5. Dodaj lokatę"<<std::endl;
        std::cout<<"\t6. Usuń lokatę"<<std::endl;
        std::cout<<"\t7. Modyfikuj lokatę"<<std::endl;
        std::cout<<"\t8. Wyjście z programu"<<std::endl;
        int choice = 0;
        try
        {
            std::string string_choice;
            std::cin>>string_choice;
            choice = std::stoi(string_choice);
        }
        catch(const std::exception& e)
        {
            std::cerr<<"Choice value cannot be a character or string! Please try again!"<<std::endl;
            continue;
        }
        try
        {
            if(choice < 1 || choice > 8)
            {
                throw InvalidChoiceValue("Choice value has to be a number from 1 to 8!");
            }
        }
        catch(const InvalidChoiceValue& e)
        {
            std::cerr << e.what() << '\n';
            std::cerr <<"Please try again!"<<'\n';
            continue;
        }

        if(choice == 1)
        {
            std::cout<<"Owner's data"<<std::endl;
            std::cout<<"\t1. Name: "<<account.getName()<<std::endl;
            std::cout<<"\t2. Surname: "<<account.getSurname()<<std::endl;
            std::cout<<"\t3. Birthdate: "<<account.getBirthDate()<<std::endl;
            std::cout<<"Posessed products:"<<std::endl;
            std::vector<Deposit> products = account.getDeposits();
            for(auto product: products)
            {
                std::cout<<product<<std::endl;
            }
            std::cin.ignore();
            std::cout<<"Please, press enter to continue...";
            std::cin.ignore();
        }
        else if(choice == 2)
        {

        }
        else if(choice == 3)
        {

        }
        else if(choice == 4)
        {

        }
        else if(choice == 5)
        {

        }
        else if(choice == 6)
        {

        }
        else if(choice == 7)
        {

        }
        else if(choice == 8)
        {
            std::cout<<"Thank you for choosing PROI Financial Services©!"<<std::endl;
            break;
        }
        std::system("clear");
    }
    return 0;

}