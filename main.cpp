#include "src/deposit.hpp"
#include <iostream>
#include "src/bank_account.hpp"

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
        std::cerr<<"Expected 4 arguments, but insted got "<<argc<<" arguments!"<<std::endl;;
    }
    return 0;
}