#include <iostream>
#include <vector>
#include <string>
#include <algorithm>    // std::max

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

// Przedmioty:
// ┌───────────┬──────┬────────┐
// │ Przedmiot │ Waga │ Wartość│
// ├───────────┼──────┼────────┤
// │ A         │  2   │   3    │
// │ B         │  3   │   4    │
// │ C         │  4   │   5    │
// │ D         │  1   │   2    │
// └───────────┴──────┴────────┘
// Limit wagi plecaka: W = 6
// Cel: wybierz zestaw przedmiotów o maksymalnej wartości nie przekraczając limitu wagi plecaka W
// Test     W       Oczekiwana wartość     Przedmioty
// 1        5             7                    A+B (waga 5)
// 2        6             9                    A+B+D (waga 6)


struct Item {
    std::string name;
    int weight;
    int value;
};

std::vector<Item> items = {
    {"A", 2, 3},
    {"B", 3, 4},
    {"C", 4, 5},
    {"D", 1, 2}
};

constexpr int N = 4;
constexpr int W = 6;

int dp[N + 1][W + 1] = {};

// Stoisz w dp[i][w].
// Jeśli dp[i][w] == dp[i - 1][w]  →  przedmiot i NIE był wzięty, idź do dp[i - 1][w]
// Jeśli dp[i][w] != dp[i - 1][w]  →  przedmiot i BYŁ wzięty, idź do dp[i - 1][w - weight[i]]
//
//Dla przykładu, startujemy w dp[3][5] = 7:
//dp[3][5] = 7  vs  dp[2][5] = 7  →  równe → C nie wzięte  →  idź do dp[2][5]
//dp[2][5] = 7  vs  dp[1][5] = 3  →  różne → B wzięte!→  idź do dp[1][5 - 3] = dp[1][2]
//dp[1][2] = 3  vs  dp[0][2] = 0  →  różne → A wzięte!→  idź do dp[0][2 - 2] = dp[0][0]
//i = 0 → koniec
void printItems(int i, int w)
{
    if (i == 0 || w == 0) return;

    if (dp[i][w] == dp[i - 1][w]) {
        printItems(i - 1, w);          // nie wzięty
    }
    else {
        printItems(i - 1, w - items[i - 1].weight);  // wzięty
        std::cout << "Item " << items[i - 1].name << "\n";
    }
}


int dp_knapsack()
{
    for (int i = 1; i <= N; ++i)
    {
        for (int w = 1; w <= W; ++w)
        {
            if (items[i - 1].weight <= w)
            {
                // przedmiot sie miesci - bierzemy max z 2 wyborow
                dp[i][w] = std::max((items[i - 1].value + dp[i - 1][w - items[i - 1].weight]), (dp[i - 1][w]));
            }
            else
            {
                // nie bierzemy
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[N][W];
}

int main()
{
    std::cout << "===== Dynamic Programming: Knapsack =====" << std::endl;
    std::cout << "Items:\n";
    for (const auto & x : items)
    {
        std::cout << "Name(" << x.name << "), weight(" << x.weight << "), value(" << x.value << ")\n";
    }
    int res = dp_knapsack();
    std::cout << "Respose: for W = " << W << ", max value = " << res << std::endl;
    std::cout << "Knapsack taken items:\n";
    printItems(N, W);

    return 0;
}
