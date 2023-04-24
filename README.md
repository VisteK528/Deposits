# Zadanie 4
W tym zadaniu zdecydowałem się na dalszą modyfikację zadania 2. Jednakże ze względu na wymóg wykorzystania polimorfizmu, inteligentnych wskaźników oraz wybranego wzorca projektowego mój program przeszedł wiele zmian, głównie struktutalnych.

1. Przede wszystkim zamiast pojedyńczej klasy `Deposit` posiadającej wiele różnych metod, wydzieliłem z niej abstrakcyjną klasę bazową `Product`. Zrobiłem to z myślą o integracji możliwości integracji mojego systemu oraz klasy/klas `Loan` tworzonych w ramach 2 zadania przez innych. Wracając jednak do lokat, stworzyłem dla nich klasę bazową `Deposit` oraz 5 klas specjalistycznych.
    1. `TraditionalDeposit` - podstawowa klasa reprezentujaca lokatę tradycyjną ze stałym oprocentowaniem
        * `CurrencyDeposit` - względem lokaty tradycyjnej posiada możliwość tworzenia lokat w innych walutach oraz przewalutowywanie
        * `AdditiveDeposit` - względem lokaty tradycyjnej posiada możliwość wpłacenia dodatkowych środków w określonym terminie
    2. `ProgressiveDeposit` - lokata progresywna ze zmiennym oprocentowaniem, posiada minimalny czas trwania lokaty
    3. `ShortTermDeposit` - lokata krótkoterminowa ze stałym oprocentowaniem, skierowana głównie do instytucji, posiada wyższą kwotę minimalną oraz nie obowiązuje dla niej podatek od zysków kapitałowych (tzw. podatek Belki). W rzeczywistości ta luka prawna została już usunięta, jednak na potrzeby zadania stwierdziłem, że może ciekawie urozmaicić projekt.

2. Stworzyłem klasę `DepositFactory`, która realizuje strukturalny wzorzec projektowy "Fabryka" tworząc na bazie podanych parametrów odpowiednie obiekty, realizuje regułę Single Responsibility Principle z SOLID
3. Zmodyfikowałem klasę `BankAccount`
    * Przechowywany jest inteligentny wskaźnik (`std::shared_ptr`) do odpowiedniego obiektu klasy `Deposit`
    * Wykorzystałem szablony, aby zamiast tworzyć szereg metod `addDeposit` dla każdego typu obiektu oddzielnie robił to za mnie kompilator. Zwiększa to przejrzystość kodu oraz realizuje regułę DRY
    ```cpp
    template<class T>
    void addDeposit(std::shared_ptr<T> t)
    {
        t->setId(getUniqueIndex());
        possesed_products.push_back(t);
    }
    ```
    * Dla wykorzystania metod takich jak `convert()` lub `addMoney()` wykorzystałem dynamiczne rzutowanie wskaźnika obiektu przechowywanego jako wskaźnik do klasy bazowej na wskaźnik do rzeczywistej klasy obiektu, umożliwiając korzystanie z wyżej wymienionych metod.
    * Inne zmiany w klasie `BankAccount` w celu przystosowania jej do zmian w projekcie
4. Zmiany w pliku `main.cpp` umożliwiające podawanie różnych zestawów danych w celu tworzenia różnych typów lokat
5. Reorganizacja i napisanie nowych testów dla nowych klas powstałych w ramach zadania 4
6. Implementacja w nowej formie metod `void saveToFile` umożliwiających zapis klasy do strumienia oraz implementacja metod w klasie `DepositFactory` umożliwiających stworzenie obiektu i zwrócenie go na podstawie strumienia wejściowego.

Poniżej przestawiam schemat klas, który próbowałem stworzyć w UML
![image](untitled_workspace.png)

