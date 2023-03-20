#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class BaseException: public std::exception
{
    private:
        std::string _msg;
    public:
        BaseException(const std::string &msg): _msg(msg){};
        const char* what() const noexcept {return _msg.c_str();}
};

class InvalidBalanceInputValueError: public BaseException
{
    public:
        InvalidBalanceInputValueError(const std::string &message): BaseException(message){};
};

class InvalidRateValueError: public BaseException
{
    public:
        InvalidRateValueError(const std::string &message): BaseException(message){};
};

class InvalidCurrencySymbolError: public BaseException
{
    public:
        InvalidCurrencySymbolError(const std::string &message): BaseException(message){};
};

class InvalidTermValueError: public BaseException
{
    public:
        InvalidTermValueError(const std::string &message): BaseException(message){};
};

class InvalidIdValueError: public BaseException
{
    public:
        InvalidIdValueError(const std::string &message): BaseException(message){};
};
#endif
