# Zmiany wprowadzone w programie w zadaniu 3

1. Dodano obsługę podatek od zysków kapitałowych (tzw. podatek Belki)
2. Zamieniono przechowywanie daty jako stringa, na przechowywanie obiektu Daty(Stworzono klasę Date)
3. Dodano ```const``` tam gdzie się dało
4. Dodano przeciążenie ```operator==``` oraz ```operator!=``` dla klasy Deposit
5. Dodano przeciążenie ```operator<<``` dla klasy BankAccount
6. Dodano przyjmowanie argumentu ```capital_gains_tax```, wyrażonego jako typ ```int``` (w procentach), wraz z wywołaniem programu
7. Dodano możliwość zapisu stanu obiektu klasy ```Deposit``` do pliku oraz odczyt z pliku i stworzenie na jego podstawie obiekt klasy ```Deposit```
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

