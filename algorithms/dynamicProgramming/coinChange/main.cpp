#include <iostream>

// Treść zadania:
// Masz nominały monet, np. {1, 3, 4}, i kwotę do wydania, np. 6.
// Szukasz najmniejszej liczby monet, które sumują się dokładnie do tej kwoty.
// Monet każdego nominału masz nieograniczenie wiele.
// Wejście:
//    coins[] : lista nominałów(dodatnie liczby całkowite, bez powtórzeń)
//    amount : kwota do uzyskania(liczba całkowita ≥ 0)
// Wyjście:
//    minimalna liczba monet albo - 1, jeśli kwoty nie da się wydać(np.monety{ 2 }, kwota 3)
//
// Jak rozbić problem na mniejsze
// Zadaj sobie pytanie : “Jaka jest OSTATNIA moneta, którą dokładam, żeby dojść do kwoty 6?”
// Nie wiesz tego, więc sprawdzasz każdą możliwość:
//
// Ostatnia moneta = 1  →  wcześniej musiałem uzbierać 6 - 1 = 5  →  monety(5) + 1
// Ostatnia moneta = 3  →  wcześniej musiałem uzbierać 6 - 3 = 3  →  monety(3) + 1
// Ostatnia moneta = 4  →  wcześniej musiałem uzbierać 6 - 4 = 2  →  monety(2) + 1
//
// Wybierasz najmniejszą z tych opcji.
// Duży problem(kwota 6) sprowadził się do mniejszych(kwoty 5, 3, 2).
// One rozbijają się dalej, aż do kwoty 0, która wymaga 0 monet.
//
// dp[a] = najmniejsza liczba monet, którymi da się uzyskać kwotę a
//
// Dlaczego 1D, skoro plecak był 2D ?
// W plecaku każdy przedmiot można wziąć tylko raz.
// Musiałeś pamiętać, z których przedmiotów już korzystasz stąd wymiar i : “pierwsze i przedmiotów”.
// Natomiast dp[i - 1] oznaczało “bez przedmiotu i”.
// Tutaj monet jest nieskończenie wiele.Nie ma czego pamiętać, bo każdą monetę możesz użyć ponownie.
// Liczy się tylko to, ile jeszcze zostało do uzbierania.Jeden parametr daje jeden wymiar.
//
// Wzor:
// dp[0] = 0   (kwota 0 → zero monet)
// dp[a] = min po wszystkich monetach c, gdzie c <= a: dp[a - c] + 1
//
// Wartość “nieosiągalne”: jeśli kwoty nie da się uzyskać, w komórce trzeba trzymać “nieskończoność”. 
// W praktyce bierze się amount + 1, bo żadne rozwiązanie nie potrzebuje więcej monet niż amount.
//
// Odpowiedź: dp[6] (tak jak w LCS i plecaku, leży w ostatniej komórce).
// Na koniec sprawdzasz : jeśli dp[amount] nadal równa się INF, zwracasz - 1.
//
// Które monety dały wymaganą resztę amout? (odtwarzanie)
//
// Mamy ten sam problem co w plecaku : dp[6] = 2 mówi ile monet, a nie jakie
// Rozwiązanie jest prostsze niż tam.
// Przy liczeniu każdej komórki zapamiętujesz w drugiej tablicy, która moneta dała minimum :
//         lastCoin[a] = moneta c, która dała najmniejsze dp[a]
// Potem idziesz od końca :
// a = 6 : lastCoin[6] = 3  →  wypisz 3, idź do a = 6 - 3 = 3
// a = 3 : lastCoin[3] = 3  →  wypisz 3, idź do a = 3 - 3 = 0
// a = 0 : koniec
//

int main()
{
    std::cout << "===== Dynamic Programming: Coin Change =====" << std::endl;

    return 0;
}
