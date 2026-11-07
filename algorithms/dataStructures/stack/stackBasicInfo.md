# Stos (Stack)

**Stos (stack)** – struktura danych typu **LIFO** (*Last In, First Out* – ostatni wszedł, pierwszy wychodzi).

## Jak działa stos?

```text
  push(1)      push(2)      push(3)       pop()        pop()
                           | 3 |
              | 2 |        | 2 |         | 2 |
  | 1 |        | 1 |        | 1 |         | 1 |        | 1 |
  ‾‾‾‾‾        ‾‾‾‾‾        ‾‾‾‾‾         ‾‾‾‾‾        ‾‾‾‾‾
                                         zdjęto 3     zdjęto 2
```

Masz dostęp tylko do elementu na szczycie.

- Nie możesz zajrzeć do środka.
- Nie możesz wziąć elementu z dołu.

To ograniczenie jest celowe: stos robi jedną rzecz i robi ją w czasie **O(1)**.

## Operacje w `std::stack`

```cpp
#include <stack>

std::stack<int> s;

s.push(5);       // połóż 5 na szczycie
s.top();         // podejrzyj szczyt (NIE zdejmuje)
s.pop();         // zdejmij szczyt (NIC NIE ZWRACA!)
s.empty();       // czy pusty?
s.size();        // ile elementów
```

Wszystkie podstawowe operacje mają złożoność **O(1)**.

### Ważne!

`top()` i `pop()` wywołane na pustym stosie powodują **undefined behavior**.

`pop()` zwraca `void`. Dlatego potrzebne są dwa kroki:

```cpp
int x = s.top();   // najpierw odczytaj
s.pop();           // potem zdejmij
```

## Kiedy sięgnąć po stos? (Clue)

Stos jest właściwym narzędziem, gdy w zadaniu chodzi o to, że:

- ostatnia rzecz, którą otworzyłeś, musi zostać zamknięta jako pierwsza,
- musisz wrócić do najświeższego elementu, który jeszcze nie został obsłużony.

### Przykłady zastosowania

1. **Nawiasy**

   `( [ ] )`

   Nawias `[` otworzył się później niż `(`, więc musi zamknąć się wcześniej.

2. **Rekurencja**

   Każde wywołanie funkcji trafia na stos wywołań (*call stack*).

   Funkcja wywołana jako ostatnia kończy się jako pierwsza.

   Dlatego rekurencyjny DFS można przepisać na pętlę z użyciem `std::stack`.

3. **Cofnij (Ctrl+Z)**

   Cofasz najpierw ostatnią zmianę.

4. **Obliczanie wyrażeń**

   Przykładowo: `3 + 4 * 2`.