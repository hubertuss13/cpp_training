#include <iostream>

// items: {weight, value}
// { {2,3}, {3,4}, {4,5}, {1,2} }
// W = 5
// Oczekiwana odpowiedź: 9  (przedmioty A+D+B = 2+1+3 wagowo = waga 6... sprawdź sam!)


// Przedmioty:
// ┌───────────┬──────┬────────┐
// │ Przedmiot │ Waga │ Wartość│
// ├───────────┼──────┼────────┤
// │ A         │  2   │   3    │
// │ B         │  3   │   4    │
// │ C         │  4   │   5    │
// └───────────┴──────┴────────┘
// Limit wagi plecaka: W = 5
// Cel: wybierz zestaw przedmiotów o maksymalnej wartości nie przekraczając limitu wagi plecaka W


// dp[i][w] = maksymalna wartość
// używając pierwszych i przedmiotów
// przy pojemności plecaka = w

// Algrorytm decyzyjny:
// Dla każdej komórki dp[i][w] zadajesz sobie pytanie:
//     “Czy wziąć przedmiot i do plecaka o pojemności w ? ”
// Masz zawsze dwa wybory :
// 1. NIE bierzesz przedmiotu i:
//    Skoro go nie biorę, wynik jest taki sam jak gdyby go nie było w ogóle (patrzę na wiersz wyżej dla tej samej pojemności)
//    dp[i][w] = dp[i - 1][w]
// 
// 2. BIERZESZ przedmiot i (ale tylko jeśli się mieści! Czyli weight[i] <= w) 
//    dp[i][w] = value[i] + dp[i - 1][w - weight[i]]
//    (dodajesz wartość przedmiotu i + najlepszy wynik dla pozostałej pojemności)
//     value[i] - wartosc przedmiotu i
//     dp[i - 1][w - weight[i]] - najlepszy wynik dla pozostałej pojemnosci bez przedmiotu i
//    Biorę maksimum z obu wyborów:
//       dp[i][w] = max(NIE biore, BIORE)
//       = max(dp[i - 1][w], value[i] + dp[i - 1][w - weight[i]])



// int dp[N+1][W+1] = {};
// pętla zewnętrzna po i (przedmiotach)
// pętla wewnętrzna po w (pojemności 0..W)


int main()
{
    std::cout << "===== Dynamic Programming: Knapsack =====" << std::endl;



    return 0;
}
