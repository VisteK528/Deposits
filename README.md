# Zmiany wprowadzone w programie w zadaniu 3

1. Dodano obsługę podatek od zysków kapitałowych (tzw. podatek Belki)
2. Dodano ```const``` tam gdzie się dało
3. Dodano przeciążenie ```operator==``` oraz ```operator!=``` dla klasy Deposit
4. Dodano przeciążenie ```operator<<``` dla klasy BankAccount
5. Dodano przyjmowanie argumentu ```capital_gains_tax```, wyrażonego jako typ ```int``` (w procentach), wraz z wywołaniem programu
6. Dodano możliwość zapisu stanu obiektu klasy ```Deposit``` do pliku oraz odczyt z pliku i stworzenie na jego podstawie obiekt klasy ```Deposit```
    - Zapis i odczyt do pliku z rozszerzeniem ```.csv``` lub ```.txt```, zgodnie z kolejnością:
    ```csv
    id, balance, currency, rate, term_months, capital_gains_tax,
    ```
    - Zapis do pliku za pomocą funkcji zaprzyjaźnionej
    ```cpp
    friend void saveToFile(std::ostream &os, const Deposit &d);
    ```
    - Odczyt i inicjalizacja za pomocą specjalnego konstruktora
    ```cpp
    Deposit(const std::istream &is);
    ```
7. Zmieniono przechowywanie daty jako stringa na przechowywanie obiektu nowej klasy `year_month_date`
    - Zdecydowałem się na stworzenie oddzielnej klasy, ponieważ orginalna klasa ```year_month_date``` z biblioteki ```std::chrono``` nie wspiera w obecnej chwili operatora ```operator<<```, a także nie jest możliwa w łatwy sposób konwersja tego typu na obiekt klasy ```std::string```. Możliwość łatwego wyprowadznia zawartości obiektu klasy ```year_month_date``` jest określona jako wspierana od standardu ```since c++20```, aczkolwiek zakładam, że w rzeczywistości stanie się to częścią biblioteki standardowej wraz ze standardem c++23. W moich plikach biblioteki ```std::chrono``` operatory ```operator<<``` oraz metody ```to_stream```, ```from_stream``` są określone w pliku jako "//TODO"
    - Moja klasa year_month_date enkapsuluje obiekt klasy ```year_month_date```, wspiera konwersję do obiektu ```std::string``` oraz posiada przeciążenie operatora ```operator<<```
8. Dodano nowe wyjątki obsługujące zmiany w programie
9. Dodano nowe testy jednostkowe sprawdzajace zmiany wprowadzone w programie
10. Zmieniono typ ```term_months``` z ```unsigned int``` na ```std::chrono::months```


