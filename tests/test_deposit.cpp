#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/deposit.hpp"

TEST_CASE("Create TraditionalDeposit", "[TraditionalDeposit]")
{
    TraditionalDeposit my_deposit(2569, 1.14, "PLN", 12, 1, 19);
    SECTION("Test getters", "[TraditionalDeposit]")
    {
        REQUIRE(my_deposit.getBalance() == 2569);
        REQUIRE(my_deposit.getId() == 1);
        REQUIRE(my_deposit.getRate() == 1.14);
        REQUIRE(my_deposit.getCurrency() == "PLN");
        REQUIRE(my_deposit.getTerm() == 12);
        REQUIRE(my_deposit.getCapitalGainsTax() == 19);
    }

    SECTION("Test setters", "[TraditionalDeposit]")
    {
        REQUIRE(my_deposit.getRate() == 1.14);
        my_deposit.setRate(2.72);
        REQUIRE(my_deposit.getRate() == 2.72);
    }
}

TEST_CASE("Test calulcating profits 1", "[TraditionalDeposit]")
{
    SECTION("Calculate profits with 3 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(2569, 1.14, "PLN", 3, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 5.93);
    }

    SECTION("Calculate profits with 6 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(2569, 1.14, "PLN", 6, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 11.86);
    }
    SECTION("Calculate profits with 9 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(2569, 1.14, "PLN", 9, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 17.79);
    }
    SECTION("Calculate profits with 12 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(2569, 1.14, "PLN", 12, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 23.72);
    }
    SECTION("Calculate profits with 15 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(2569, 1.14, "PLN", 15, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 29.65);
    }
    SECTION("Calculate profits with 18 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(2569, 1.14, "PLN", 18, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 35.58);
    }
}

TEST_CASE("Test calulcating profits 2", "[TraditionalDeposit]")
{
    SECTION("Calculate profits with 3 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(152678, 3.14, "PLN", 3, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 970.80);
    }
    SECTION("Calculate profits with 6 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(152678, 3.14, "PLN", 6, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 1941.61);
    }
    SECTION("Calculate profits with 9 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(152678, 3.14, "PLN", 9, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 2912.41);
    }
    SECTION("Calculate profits with 12 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(152678, 3.14, "PLN", 12, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 3883.21);
    }
    SECTION("Calculate profits with 15 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(152678, 3.14, "PLN", 15, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 4854.02);
    }
    SECTION("Calculate profits with 18 month term", "[TraditionalDeposit]")
    {
        TraditionalDeposit my_deposit(152678, 3.14, "PLN", 18, 1, 19);
        REQUIRE(my_deposit.calculateProfit() == 5824.82);
    }
}

TEST_CASE("Create deposit with invalid values", "[TraditionalDeposit]")
{
    SECTION("Create deposit with negative balance", "[TraditionalDeposit]")
    {
        REQUIRE_THROWS(TraditionalDeposit(-512, 3.14, "PLN", 12, 2, 19));
    }
    SECTION("Create deposit with negative rate", "[TraditionalDeposit]")
    {
        REQUIRE_THROWS(TraditionalDeposit(512, -3.14, "PLN", 12, 2, 19));
    }
    SECTION("Create deposit with negative deposit term", "[TraditionalDeposit]")
    {
        REQUIRE_THROWS(TraditionalDeposit(512, 3.14, "PLN", -12, 2, 19));
    }
    SECTION("Create deposit with invalid currency symbol", "[TraditionalDeposit]")
    {
        REQUIRE_THROWS(TraditionalDeposit(512, 3.14, "PLNfewafa", 12, 2, 19));
    }
    SECTION("Create deposit with invalid id", "[TraditionalDeposit]")
    {
        REQUIRE_THROWS(TraditionalDeposit(512, 3.14, "PLN", 12, -2, 19));
    }
}

// TEST_CASE("Test converting the currency of the deposit", "[deposit]")
// {
//     Deposit my_deposit(2569, 1.14, "PLN", 12, 1, 19);
//     SECTION("Test converting to PLN", "[deposit]")
//     {
//         bank_rate exchange_rate = 1;
//         std::string exchange_currency = "PLN";
//         REQUIRE(my_deposit.getBalance() == 2569);
//         REQUIRE(my_deposit.getRate() == 1.14);
//         REQUIRE(my_deposit.getCurrency() == "PLN");
//         my_deposit.convert(exchange_currency, exchange_rate);
//         REQUIRE(my_deposit.getBalance() == 2569);
//         REQUIRE(my_deposit.getRate() == 1.14);
//         REQUIRE(my_deposit.getCurrency() == "PLN");
//     }
//     SECTION("Test converting to USD", "[deposit]")
//     {
//         bank_rate exchange_rate = 4.39;
//         std::string exchange_currency = "USD";
//         REQUIRE(my_deposit.getBalance() == 2569);
//         REQUIRE(my_deposit.getRate() == 1.14);
//         REQUIRE(my_deposit.getCurrency() == "PLN");
//         my_deposit.convert(exchange_currency, exchange_rate);
//         REQUIRE(my_deposit.getBalance() == 585.19);
//         REQUIRE(my_deposit.getRate() == 1.14);
//         REQUIRE(my_deposit.getCurrency() == exchange_currency);
//     }
//     SECTION("Test converting to GBP", "[deposit]")
//     {
//         bank_rate exchange_rate = 5.39;
//         std::string exchange_currency = "GBP";
//         REQUIRE(my_deposit.getBalance() == 2569);
//         REQUIRE(my_deposit.getRate() == 1.14);
//         REQUIRE(my_deposit.getCurrency() == "PLN");
//         my_deposit.convert(exchange_currency, exchange_rate);
//         REQUIRE(my_deposit.getBalance() == 476.62);
//         REQUIRE(my_deposit.getRate() == 1.14);
//         REQUIRE(my_deposit.getCurrency() == exchange_currency);
//     }
//     SECTION("Test converting to EUR", "[deposit]")
//     {
//         bank_rate exchange_rate = 4.7;
//         std::string exchange_currency = "EUR";
//         REQUIRE(my_deposit.getBalance() == 2569);
//         REQUIRE(my_deposit.getRate() == 1.14);
//         REQUIRE(my_deposit.getCurrency() == "PLN");
//         my_deposit.convert(exchange_currency, exchange_rate);
//         REQUIRE(my_deposit.getBalance() == 546.6);
//         REQUIRE(my_deposit.getRate() == 1.14);
//         REQUIRE(my_deposit.getCurrency() == exchange_currency);
//     }
// }


TEST_CASE("Test deposit equality", "[TraditionalDeposit]")
{
    TraditionalDeposit first_deposit(2569, 1.14, "PLN", 12, 1, 19);
    TraditionalDeposit second_deposit(2569, 1.14, "PLN", 12, 2, 19);
    TraditionalDeposit third_deposit(2500, 1.14, "PLN", 12, 3, 19);
    SECTION("Test equality of deposits' properties except for ID", "[deposit]")
    {
        REQUIRE(first_deposit == second_deposit);
        REQUIRE_FALSE(first_deposit == third_deposit);
    }
}


// TEST_CASE("Test creating deposit from stream", "[deposit]")
// {
//     std::string line = "1,972.56,PLN,3.14,6,19,";
//     std::stringstream stream(line);
//     Deposit my_deposit(stream);

//     REQUIRE(my_deposit.getBalance() == 972.56);
//     REQUIRE(my_deposit.getId() == 1);
//     REQUIRE(my_deposit.getRate() == 3.14);
//     REQUIRE(my_deposit.getCurrency() == "PLN");
//     REQUIRE(my_deposit.getTermUnsignedInt() == 6);
//     REQUIRE(my_deposit.getCapitalGainsTax() == 19);

// }

// TEST_CASE("Test saving Deposit to stream", "[deposit]")
// {
//     std::stringstream stream;
//     Deposit my_deposit(2569, 1.14, "PLN", 12, 1, 19);
//     saveToFile(stream, my_deposit);
//     REQUIRE(stream.str() == "1,2569.000000,PLN,1.140000,12,19,");

// }

//ShortTerm Deposit

TEST_CASE("Test ShortTerm Deposit", "[ShortTermDeposit]")
{
    SECTION("Test ShortTermDeposit creation", "[ShortTermDeposit]")
    {
        // Negative balance
        REQUIRE_THROWS(ShortTimeDeposit(-50, 3.14, "PLN", 24, 1));

        // Not sufficient balance
        REQUIRE_THROWS(ShortTimeDeposit(1000, 3.14, "PLN", 24, 1));

        // Negative Rate
        REQUIRE_THROWS(ShortTimeDeposit(25000, -2, "PLN", 24, 1));

        // Not valid currency
        REQUIRE_THROWS(ShortTimeDeposit(25000, 3.14, "PLNNNN", 24, 1));

        // Negative term
        REQUIRE_THROWS(ShortTimeDeposit(25000, 3.14, "PLN", -24, 1));

        // Negative id
        REQUIRE_THROWS(ShortTimeDeposit(25000, 3.14, "PLN", 24, -1));

        // Valid creation
        REQUIRE_NOTHROW(ShortTimeDeposit(25000, 3.14, "PLN", 24, 1));
    }

    SECTION("Test ShortTermDeposit getters and setters")
    {
        ShortTimeDeposit deposit(25000, 3.14, "PLN", 24, 1);
        REQUIRE(deposit.getBalance() == 25000.);
        REQUIRE(deposit.getId() == 1);
        REQUIRE(deposit.getRate() == 3.14);
        REQUIRE(deposit.getCurrency() == "PLN");
        REQUIRE(deposit.getTerm() == 24);
        REQUIRE(deposit.getCapitalGainsTax() == 0);
        REQUIRE(deposit.getProductType() == "ShortTermDeposit");
    }
}