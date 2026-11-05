Stos (stack) - struktura LIFO (Last In, First Out: ostatni wszedł, pierwszy wychodzi).
push(1)      push(2)      push(3)      pop()        pop()
                        | 3 |
            | 2 |        | 2 |        | 2 |
| 1 |        | 1 |        | 1 |        | 1 |        | 1 |
‾‾‾‾‾        ‾‾‾‾‾        ‾‾‾‾‾        ‾‾‾‾‾        ‾‾‾‾‾
                                    zdjęto 3     zdjęto 2

Masz dostęp tylko do elementu na szczycie.
Nie możesz zajrzeć do środka ani wziąć elementu z dołu.
To ograniczenie jest celowe: stos robi jedną rzecz i robi ją w czasie O(1).

Operacje w std::stack
#include <stack>
std::stack<int> s;

s.push(5);       // połóż 5 na szczycie
s.top();         // podejrzyj szczyt (NIE zdejmuje)
s.pop();         // zdejmij szczyt (NIC NIE ZWRACA!)
s.empty();       // czy pusty?
s.size();        // ile elementów
Wszystkie operacje mają złożoność O(1).

top() i pop() na pustym stosie to undefined behavior.
pop() zwraca void. Dlatego potrzebne 2 kroki: 
int x = s.top();   // najpierw odczytaj
s.pop();           // potem zdejmij

Kiedy sięgnąć po stos? (clue)

Stos jest właściwym narzędziem, gdy w zadaniu chodzi o to, że ostatnia rzecz,
którą otworzyłeś, musi zostać zamknięta jako pierwsza,
albo gdy musisz wrócić do najświeższego elementu, który jeszcze nie został obsłużony.

Przykłady:

-> Nawiasy: ( [ ] ). Nawias [ otworzył się później niż (, więc musi zamknąć się wcześniej.
-> Rekurencja: każde wywołanie funkcji trafia na stos wywołań. 
   Funkcja wywołana jako ostatnia kończy się jako pierwsza. 
   Dlatego rekurencyjny DFS można przepisać na pętlę z std::stack.
-> Cofnij (Ctrl+Z): cofasz najpierw ostatnią zmianę.
-> Obliczanie wyrażeń, np. 3 + 4 * 2.
