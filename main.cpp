#include <iostream>
#include "src/interface.hpp"

int main(int argc, char* argv[])
{
    if(argc != 5)
    {
        std::cerr<<"Expected 5 arguments, but insted got "<<argc<<" arguments!"<<std::endl;
        return 1;
    }
    std::string name;
    std::string surname;
    std::string birth_date;
    std::string capital_gains_tax_string;
    int capital_gains_tax = 0;
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
    stream<<argv[4];
    stream>>capital_gains_tax_string;
    stream.clear();
    try
    {
        capital_gains_tax = std::stoi(capital_gains_tax_string);
    }
    catch(const std::exception& e)
    {
        std::cerr<<"Capital gains tax value cannot be a string!"<<std::endl;
        return 1;
    }

    Interface interface(name, surname, birth_date, capital_gains_tax);
    interface.run();
    return 0;
}