#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

class year_month_day
{
    private:
        std::chrono::year_month_day ymd;
    public:
        year_month_day(){};
        year_month_day(std::chrono::year year, std::chrono::month month, std::chrono::day day);
        std::string getAsString() const;
        std::chrono::year_month_day date()const{return ymd;}
        friend std::ostream& operator<<(std::ostream &os, const year_month_day &d);

};

#endif