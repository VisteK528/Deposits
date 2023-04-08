#include "date.hpp"

year_month_day::year_month_day(std::chrono::year year, std::chrono::month month, std::chrono::day day)
{
    this->ymd = std::chrono::year_month_day(year, month, day);
}

std::string year_month_day::getAsString() const
{
    std::stringstream stream;

    unsigned int day = unsigned(ymd.day());
    unsigned int month = unsigned(ymd.month());
    unsigned int year = int(ymd.year());
    stream << std::setw(4) << year;
    stream << '-';
    stream << std::setw(2) << std::setfill('0') << month;
    stream << '-';
    stream << std::setw(2) << std::setfill('0') << day;
    return stream.str();
}

std::ostream& operator<<(std::ostream &os, const year_month_day &d)
{
    os << d.getAsString();
    return os;
}