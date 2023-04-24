#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "exceptions.hpp"

class Product
{
    protected:
        // Data
        std::string product_type;
        std::string currency;
        unsigned int balance;
        unsigned int id;
        std::chrono::hours term;

        // Methods
        void setCurrency(std::string currency);

        // Virtual methods
        virtual void setTerm(int term);
        virtual void print(std::ostream &os) const;

    public:
        virtual ~Product() = default;
        double getBalance() const;
        unsigned int getId() const;
        std::string getCurrency() const;
        std::string getProductType() const;
        void setId(int id);

        // Virtual methods
        virtual unsigned int getTerm() const;
        virtual void saveToFile(std::ostream &os) const = 0;    // Pure abstract method

        // Operators
        friend std::ostream& operator<<(std::ostream &os, const Product &p);
};

#endif