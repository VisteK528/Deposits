#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/exceptions.hpp"
#include "../src/bank_account.hpp"
#include "../src/deposit.hpp"

TEST_CASE("Create a bank account", "[bank_account]")
{
    BankAccount account("Jan", "Kowalski", "2000-01-01");
    SECTION("Test getters", "[bank_account]")
    {
        REQUIRE(account.getName() == "Jan");
        REQUIRE(account.getSurname() == "Kowalski");
        REQUIRE(account.getBirthDateString() == "2000-01-01");
    }
}

TEST_CASE("Adding deposits to bank account", "[bank_account]")
{
    DepositFactory factory;
    BankAccount account("Jan", "Kowalski", "2000-01-01");
    SECTION("Add deposits and count them", "[bank_account]")
    {
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 972, 3.14, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1364, 2.71, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1410, 3.14, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1945, 3.14, "PLN", 6, 19));
        REQUIRE(account.countDeposits() == 4);
    }
    SECTION("Search for deposit", "[bank_account]")
    {
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 972, 3.14, "PLN", 12, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1364, 2.71, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1410, 3.14, "PLN", 3, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1945, 3.14, "PLN", 9, 19));
        const Deposit& test_deposit = account.findDeposit(3);
        REQUIRE(test_deposit.getId() == 3);
        REQUIRE(test_deposit.getBalance() == 1410);
        REQUIRE(test_deposit.getCurrency() == "PLN");
        REQUIRE(test_deposit.getRate() == 3.14);
        REQUIRE(test_deposit.getTerm() == 3);
    }
    SECTION("Add new deposit with id of removed deposit", "[bank_account]")
    {
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 972, 3.14, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1364, 2.71, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1410, 3.14, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1945, 3.14, "PLN", 6, 19));
        REQUIRE(account.countDeposits() == 4);
        account.removeDeposit(3);
        REQUIRE(account.countDeposits() == 3);
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1989, 2.71, "PLN", 12, 19));
        REQUIRE(account.countDeposits() == 4);
        const Deposit& test_deposit = account.findDeposit(3);
        REQUIRE(test_deposit.getId() == 3);
        REQUIRE(test_deposit.getBalance() == 1989);
        REQUIRE(test_deposit.getCurrency() == "PLN");
        REQUIRE(test_deposit.getRate() == 2.71);
        REQUIRE(test_deposit.getTerm() == 12);
    }

}


TEST_CASE("Remove deposits from bank account", "[bank_account]")
{
    DepositFactory factory;
    BankAccount account("Jan", "Kowalski", "2000-01-01");
    SECTION("Add 4 deposits and then remove one of them", "[bank_account]")
    {
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 972, 3.14, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1364, 2.71, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1410, 3.14, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1945, 3.14, "PLN", 6, 19));
        REQUIRE(account.countDeposits() == 4);
        account.removeDeposit(4);
        REQUIRE(account.countDeposits() == 3);
    }
    SECTION("Remove all deposits", "[bank_account]")
    {
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 972, 3.14, "PLN", 12, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1364, 2.71, "PLN", 6, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1410, 3.14, "PLN", 3, 19));
        account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1945, 3.14, "PLN", 9, 19));
        REQUIRE(account.countDeposits() == 4);
        account.removeDeposit(1);
        account.removeDeposit(2);
        account.removeDeposit(3);
        account.removeDeposit(4);
        REQUIRE(account.countDeposits() == 0);
    }

}


TEST_CASE("Modify deposits", "[bank_account]")
{
    DepositFactory factory;
    BankAccount account("Jan", "Kowalski", "2000-01-01");
    account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 972, 3.14, "PLN", 12, 19));
    account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1364, 2.71, "PLN", 6, 19));
    account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1410, 3.14, "PLN", 3, 19));
    account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1945, 3.14, "PLN", 9, 19));

    SECTION("Change deposit annual interest rate", "[bank_account]")
    {
        const Deposit& test_deposit = account.findDeposit(3);
        REQUIRE(test_deposit.getBalance() == 1410);
        REQUIRE(test_deposit.getCurrency() == "PLN");
        REQUIRE(test_deposit.getRate() == 3.14);
        REQUIRE(test_deposit.getTerm() == 3);
        account.setDepositRate(3, 2.71);
        const Deposit& converted_test_deposit = account.findDeposit(3);
        REQUIRE(converted_test_deposit.getBalance() == 1410);
        REQUIRE(converted_test_deposit.getCurrency() == "PLN");
        REQUIRE(converted_test_deposit.getRate() == 2.71);
        REQUIRE(converted_test_deposit.getTerm() == 3);
    }
}

TEST_CASE("Calculate profits after term", "[bank_account]")
{
    DepositFactory factory;
    BankAccount account("Jan", "Kowalski", "2000-01-01");
    account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 972, 3.14, "PLN", 12, 19));
    const Deposit& test_deposit = account.findDeposit(1);
    REQUIRE(test_deposit.calculateProfit() == 24.72);
}

TEST_CASE("Test different types of deposit", "[BankAccount]")
{
    DepositFactory factory;
    BankAccount account("Jan", "Kowalski", "2000-01-01");
    std::vector<bank_rate> rates = {3.14, 3.14, 3.14, 3.14, 3.14, 3.14};
    account.addDeposit(factory.createTraditionalDeposit(TRADITIONAL, 1364, 2.71, "PLN", 6, 19));
    account.addDeposit(factory.createTraditionalDeposit(CURRENCY, 972, 3.14, "EUR", 12, 19));
    account.addDeposit(factory.createTraditionalDeposit(ADDITIVE, 1945, 3.14, "PLN", 9, 19));
    account.addDeposit(factory.createShortTimeDeposit(30000, 2.71, "PLN", 6, 19));
    account.addDeposit(factory.createProgressiveDeposit(1364, rates, "PLN", 6, 19));
    SECTION("Try invalid operations on different types of Deposits", "[BankAccount]")
    {
        REQUIRE_THROWS(account.convertDeposit(1, "EUR", 4.7));
        REQUIRE_THROWS(account.convertDeposit(3, "EUR", 4.7));
        REQUIRE_THROWS(account.convertDeposit(4, "EUR", 4.7));
        REQUIRE_THROWS(account.convertDeposit(5, "EUR", 4.7));
        REQUIRE_THROWS(account.addMoneyToDeposit(1, 6, 2500));
        REQUIRE_THROWS(account.addMoneyToDeposit(2, 6, 2500));
        REQUIRE_THROWS(account.addMoneyToDeposit(4, 6, 2500));
        REQUIRE_THROWS(account.addMoneyToDeposit(5, 6, 2500));
    }
    SECTION("Convert deposit to other currency", "[bank_account]")
    {
        const Deposit& test_deposit = account.findDeposit(2);
        REQUIRE(test_deposit.getBalance() == 972);
        REQUIRE(test_deposit.getCurrency() == "EUR");
        REQUIRE(test_deposit.getRate() == 3.14);
        REQUIRE(test_deposit.getTerm() == 12);
        REQUIRE(test_deposit.getCapitalGainsTax() == 19);
        account.convertDeposit(2, "USD", 0.91);
        const Deposit& converted_test_deposit = account.findDeposit(2);
        REQUIRE(converted_test_deposit.getBalance() == 1068.13);
        REQUIRE(converted_test_deposit.getCurrency() == "USD");
        REQUIRE(converted_test_deposit.getRate() == 3.14);
        REQUIRE(converted_test_deposit.getTerm() == 12);
        REQUIRE(test_deposit.getCapitalGainsTax() == 19);
    }
    SECTION("Convert deposit to other currency v2", "[bank_account]")
    {
        const Deposit& test_deposit = account.findDeposit(2);
        REQUIRE(test_deposit.getBalance() == 972);
        REQUIRE(test_deposit.getCurrency() == "EUR");
        REQUIRE(test_deposit.getRate() == 3.14);
        REQUIRE(test_deposit.getTerm() == 12);
        REQUIRE(test_deposit.getCapitalGainsTax() == 19);
        account.convertDeposit(2, "GBP", 1.13);
        const Deposit& converted_test_deposit = account.findDeposit(2);
        REQUIRE(converted_test_deposit.getBalance() == 860.18);
        REQUIRE(converted_test_deposit.getCurrency() == "GBP");
        REQUIRE(converted_test_deposit.getRate() == 3.14);
        REQUIRE(converted_test_deposit.getTerm() == 12);
        REQUIRE(test_deposit.getCapitalGainsTax() == 19);
    }
}