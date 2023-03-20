#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/deposit.hpp"

TEST_CASE("Create deposit", "[deposit]")
{
    Deposit my_deposit(2569, 1.14, "PLN", 12, 1);
    SECTION("Test getters", "[deposit]")
    {
        REQUIRE(my_deposit.getBalance() == 2569);
        REQUIRE(my_deposit.getId() == 1);
        REQUIRE(my_deposit.getRate() == 1.14);
        REQUIRE(my_deposit.getCurrency() == "PLN");
        REQUIRE(my_deposit.getTerm() == 12);
    }

    SECTION("Test setters", "[deposit]")
    {
        REQUIRE(my_deposit.getRate() == 1.14);
        my_deposit.setRate(2.72);
        REQUIRE(my_deposit.getRate() == 2.72);
    }
}

TEST_CASE("Test calulcating profits 1", "[deposit]")
{
    SECTION("Calculate profits with 3 month term", "[deposit]")
    {
        Deposit my_deposit(2569, 1.14, "PLN", 3, 1);
        REQUIRE(my_deposit.calculateProfit() == 7.32);
    }
    SECTION("Calculate profits with 6 month term", "[deposit]")
    {
        Deposit my_deposit(2569, 1.14, "PLN", 6, 1);
        REQUIRE(my_deposit.calculateProfit() == 14.64);
    }
    SECTION("Calculate profits with 9 month term", "[deposit]")
    {
        Deposit my_deposit(2569, 1.14, "PLN", 9, 1);
        REQUIRE(my_deposit.calculateProfit() == 21.96);
    }
    SECTION("Calculate profits with 12 month term", "[deposit]")
    {
        Deposit my_deposit(2569, 1.14, "PLN", 12, 1);
        REQUIRE(my_deposit.calculateProfit() == 29.29);
    }
    SECTION("Calculate profits with 15 month term", "[deposit]")
    {
        Deposit my_deposit(2569, 1.14, "PLN", 15, 1);
        REQUIRE(my_deposit.calculateProfit() == 36.61);
    }
    SECTION("Calculate profits with 18 month term", "[deposit]")
    {
        Deposit my_deposit(2569, 1.14, "PLN", 18, 1);
        REQUIRE(my_deposit.calculateProfit() == 43.93);
    }
}

TEST_CASE("Test calulcating profits 2", "[deposit]")
{
    SECTION("Calculate profits with 3 month term", "[deposit]")
    {
        Deposit my_deposit(152678, 3.14, "PLN", 3, 1);
        REQUIRE(my_deposit.calculateProfit() == 1198.52);
    }
    SECTION("Calculate profits with 6 month term", "[deposit]")
    {
        Deposit my_deposit(152678, 3.14, "PLN", 6, 1);
        REQUIRE(my_deposit.calculateProfit() == 2397.04);
    }
    SECTION("Calculate profits with 9 month term", "[deposit]")
    {
        Deposit my_deposit(152678, 3.14, "PLN", 9, 1);
        REQUIRE(my_deposit.calculateProfit() == 3595.57);
    }
    SECTION("Calculate profits with 12 month term", "[deposit]")
    {
        Deposit my_deposit(152678, 3.14, "PLN", 12, 1);
        REQUIRE(my_deposit.calculateProfit() == 4794.09);
    }
    SECTION("Calculate profits with 15 month term", "[deposit]")
    {
        Deposit my_deposit(152678, 3.14, "PLN", 15, 1);
        REQUIRE(my_deposit.calculateProfit() == 5992.61);
    }
    SECTION("Calculate profits with 18 month term", "[deposit]")
    {
        Deposit my_deposit(152678, 3.14, "PLN", 18, 1);
        REQUIRE(my_deposit.calculateProfit() == 7191.13);
    }
}

TEST_CASE("Create deposit with invalid values", "[deposit]")
{
    SECTION("Create deposit with negative balance", "[deposit]")
    {
        REQUIRE_THROWS(Deposit(-512, 3.14, "PLN", 12, 2));
    }
    SECTION("Create deposit with negative rate", "[deposit]")
    {
        REQUIRE_THROWS(Deposit(512, -3.14, "PLN", 12, 2));
    }
    SECTION("Create deposit with negative deposit term", "[deposit]")
    {
        REQUIRE_THROWS(Deposit(512, 3.14, "PLN", -12, 2));
    }
    SECTION("Create deposit with invalid currency symbol", "[deposit]")
    {
        REQUIRE_THROWS(Deposit(512, 3.14, "PLNfewafa", 12, 2));
    }
    SECTION("Create deposit with invalid id", "[deposit]")
    {
        REQUIRE_THROWS(Deposit(512, 3.14, "PLN", 12, -2));
    }
}

TEST_CASE("Test converting the currency of the deposit", "[deposit]")
{
    Deposit my_deposit(2569, 1.14, "PLN", 12, 1);
    SECTION("Test converting to PLN", "[deposit]")
    {
        bank_rate exchange_rate = 1;
        std::string exchange_currency = "PLN";
        REQUIRE(my_deposit.getBalance() == 2569);
        REQUIRE(my_deposit.getRate() == 1.14);
        REQUIRE(my_deposit.getCurrency() == "PLN");
        my_deposit.convert(exchange_currency, exchange_rate);
        REQUIRE(my_deposit.getBalance() == 2569);
        REQUIRE(my_deposit.getRate() == 1.14);
        REQUIRE(my_deposit.getCurrency() == "PLN");
    }
    SECTION("Test converting to USD", "[deposit]")
    {
        bank_rate exchange_rate = 4.39;
        std::string exchange_currency = "USD";
        REQUIRE(my_deposit.getBalance() == 2569);
        REQUIRE(my_deposit.getRate() == 1.14);
        REQUIRE(my_deposit.getCurrency() == "PLN");
        my_deposit.convert(exchange_currency, exchange_rate);
        REQUIRE(my_deposit.getBalance() == 585.19);
        REQUIRE(my_deposit.getRate() == 0.26);
        REQUIRE(my_deposit.getCurrency() == exchange_currency);
    }
    SECTION("Test converting to GBP", "[deposit]")
    {
        bank_rate exchange_rate = 5.39;
        std::string exchange_currency = "GBP";
        REQUIRE(my_deposit.getBalance() == 2569);
        REQUIRE(my_deposit.getRate() == 1.14);
        REQUIRE(my_deposit.getCurrency() == "PLN");
        my_deposit.convert(exchange_currency, exchange_rate);
        REQUIRE(my_deposit.getBalance() == 476.62);
        REQUIRE(my_deposit.getRate() == 0.21);
        REQUIRE(my_deposit.getCurrency() == exchange_currency);
    }
    SECTION("Test converting to EUR", "[deposit]")
    {
        bank_rate exchange_rate = 4.7;
        std::string exchange_currency = "EUR";
        REQUIRE(my_deposit.getBalance() == 2569);
        REQUIRE(my_deposit.getRate() == 1.14);
        REQUIRE(my_deposit.getCurrency() == "PLN");
        my_deposit.convert(exchange_currency, exchange_rate);
        REQUIRE(my_deposit.getBalance() == 546.6);
        REQUIRE(my_deposit.getRate() == 0.24);
        REQUIRE(my_deposit.getCurrency() == exchange_currency);
    }
}