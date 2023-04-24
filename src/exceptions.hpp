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

class InvalidAddMoneyAmountError: public BaseException
{
    public:
        InvalidAddMoneyAmountError(const std::string &message): BaseException(message){};
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

class InvalidMonthValueError: public BaseException
{
    public:
        InvalidMonthValueError(const std::string &message): BaseException(message){};
};

class InvalidIdValueError: public BaseException
{
    public:
        InvalidIdValueError(const std::string &message): BaseException(message){};
};

class InvalidCapitalGainsTaxValueError: public BaseException
{
    public:
        InvalidCapitalGainsTaxValueError(const std::string &message): BaseException(message){};
};

class InvalidRatesCoefficientsNumberError: public BaseException
{
    public:
            InvalidRatesCoefficientsNumberError(const std::string &message): BaseException(message){};
};

// Deposit

class ProductsInvalidIndexError: public BaseException
{
    public:
        ProductsInvalidIndexError(const std::string &message): BaseException(message){};
};

class IncompatibleDepositTypeError: public BaseException
{
    public:
        IncompatibleDepositTypeError(const std::string &message): BaseException(message){};
};


// BankAccount

class InvalidDateFormatError: public BaseException
{
    public:
        InvalidDateFormatError(const std::string &message): BaseException(message){};
};

// Main program

class InvalidChoiceValue: public BaseException
{
    public:
        InvalidChoiceValue(const std::string &message): BaseException(message){};
};

class InvalidRateCoefficientValueError: public BaseException
{
    public:
        InvalidRateCoefficientValueError(const std::string &message): BaseException(message){};
};
#endif
