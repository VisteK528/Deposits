#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/exceptions.hpp"
#include "../src/bank_account.hpp"
#include "../src/deposit.hpp"

TEST_CASE("Create a bank account", "[bank_account]")
{
    BankAccount account("Jan", "Kowalski", "01-01-2000");
    SECTION("Test getters", "[bank_account]")
    {
        REQUIRE(account.getName() == "Jan");
        REQUIRE(account.getSurname() == "Kowalski");
        REQUIRE(account.getBirthDate() == "01-01-2000");
    }
}

TEST_CASE("Adding deposits to bank account", "[bank_account]")
{
    BankAccount account("Jan", "Kowalski", "01-01-2000");
    SECTION("Add deposits and count them", "[bank_account]")
    {
        account.addDeposit(972, 3.14, "PLN", 6);
        account.addDeposit(1364, 2.71, "PLN", 6);
        account.addDeposit(1410, 3.14, "EUR", 6);
        account.addDeposit(1945, 3.14, "USD", 6);
        REQUIRE(account.countDeposits() == 4);
    }
    SECTION("Search for deposit", "[bank_account]")
    {
        account.addDeposit(972, 3.14, "PLN", 12);
        account.addDeposit(1364, 2.71, "PLN", 6);
        account.addDeposit(1410, 3.14, "EUR", 3);
        account.addDeposit(1945, 3.14, "USD", 9);
        Deposit test_deposit = account.findDeposit(3);
        REQUIRE(test_deposit.getId() == 3);
        REQUIRE(test_deposit.getBalance() == 1410);
        REQUIRE(test_deposit.getCurrency() == "EUR");
        REQUIRE(test_deposit.getRate() == 3.14);
        REQUIRE(test_deposit.getTerm() == 3);
    }
    SECTION("Add new deposit with id of removed deposit", "[bank_account]")
    {
        account.addDeposit(972, 3.14, "PLN", 6);
        account.addDeposit(1364, 2.71, "PLN", 6);
        account.addDeposit(1410, 3.14, "EUR", 6);
        account.addDeposit(1945, 3.14, "USD", 6);
        REQUIRE(account.countDeposits() == 4);
        account.removeDeposit(3);
        REQUIRE(account.countDeposits() == 3);
        account.addDeposit(1989, 2.71, "CHF", 12);
        REQUIRE(account.countDeposits() == 4);
        Deposit test_deposit = account.findDeposit(3);
        REQUIRE(test_deposit.getId() == 3);
        REQUIRE(test_deposit.getBalance() == 1989);
        REQUIRE(test_deposit.getCurrency() == "CHF");
        REQUIRE(test_deposit.getRate() == 2.71);
        REQUIRE(test_deposit.getTerm() == 12);
    }

}


TEST_CASE("Remove deposits from bank account", "[bank_account]")
{
    BankAccount account("Jan", "Kowalski", "01-01-2000");
    SECTION("Add 4 deposits and then remove one of them", "[bank_account]")
    {
        account.addDeposit(972, 3.14, "PLN", 6);
        account.addDeposit(1364, 2.71, "PLN", 6);
        account.addDeposit(1410, 3.14, "EUR", 6);
        account.addDeposit(1945, 3.14, "USD", 6);
        REQUIRE(account.countDeposits() == 4);
        account.removeDeposit(4);
        REQUIRE(account.countDeposits() == 3);
    }
    SECTION("Remove all deposits", "[bank_account]")
    {
        account.addDeposit(972, 3.14, "PLN", 12);
        account.addDeposit(1364, 2.71, "PLN", 6);
        account.addDeposit(1410, 3.14, "EUR", 3);
        account.addDeposit(1945, 3.14, "USD", 9);
        REQUIRE(account.countDeposits() == 4);
        account.removeDeposit(1);
        account.removeDeposit(2);
        account.removeDeposit(3);
        account.removeDeposit(4);
        REQUIRE(account.countDeposits() == 0);
    }

}