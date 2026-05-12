#include <iostream>
#include <vector>
#include <climits>   // INT_MAX, INT_MIN
#include <iterator>
//#include <cstdlib>   // abs() dla int


// Zadania - Kategoria 2 – Optymalizacja (znajdź najlepszy subset)
// 1. Subset o sumie najbliższej wartości docelowej
// 2, Najkrótszy subset o sumie >= target
// 3. Maksymalna suma nieprzekraczająca limitu – klasyczny problem plecakowy (knapsack)


namespace sum_closest_to_target
{
    // Cel: Ze zbioru collection znajdź subset, ktorego suma jest najblizsza TARGET
    // (może być równa, może być mniejsza, może być większa)

    const std::vector<int> collection = {3, 4, 5, 7};
    const int N = collection.size();
    const int target = 11;

    std::vector<int> current;
    std::vector<int> bestSubset;
    int currentSum;
    int bestSum = INT_MAX;

    void genSubset(int index)
    {
        if (index == N)
        {
            if (abs(target - currentSum) < abs(target - bestSum))
            {
                bestSum = currentSum;
                bestSubset = current;
            }
            return;
        }

        current.push_back(collection[index]);
        currentSum += collection[index];
        genSubset(index + 1);
        current.pop_back();
        currentSum -= collection[index];

        genSubset(index + 1);
    }

    void test_subset_sum_closest_to_target()
    {
        genSubset(0);
        std::cout << "Best subset with target=" << target << " from original set [ ";
        std::copy(collection.begin(), collection.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "] is: \n[ ";
        std::copy(bestSubset.begin(), bestSubset.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "] and bestSum is:" << bestSum << std::endl;
    }

}  // namespace sum_closest_to_target


namespace shortest_subset_with_target_sum
{
    // Cel: Ze zbioru collection znajdź subset o najmniejszej liczbie elementów
    // którego suma jest większa lub równa TARGET

    const std::vector<int> collection = {2, 3, 5, 7, 1};
    const int N = collection.size();
    const int target = 8;

    std::vector<int> current;
    int currentSum = 0;
    std::vector<int> bestSubset;
    int bestLength = N;

    void genSubset(int index)
    {
        if ((int)current.size() >= bestLength) return;

        if (index == N)
        {
            if (currentSum >= target && (int)current.size() < bestLength)
            {
                bestLength = current.size();
                bestSubset = current;
            }
            return;
        }

        current.push_back(collection[index]);
        currentSum += collection[index];

        genSubset(index + 1);

        current.pop_back();
        currentSum -= collection[index];

        genSubset(index + 1);
    }

    void test_best_subset_with_shortest_length_and_target_sum_greater_than_condition()
    {
        genSubset(0);
        std::cout << "Original subset: [ ";
        std::copy(collection.begin(), collection.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "]\n";
        std::cout << "The shortest subset with sum >= " << target << " and shortest length = " << bestLength << " is: [ ";
        std::copy(bestSubset.begin(), bestSubset.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "]\n";
    }

}   // namespace shortest_subset_with_target_sum


namespace knapsack
{
//Przedmioty:
//┌─────────────┬──────┬────────┐
//│ Przedmiot   │ Waga │ Wartość│
//├─────────────┼──────┼────────┤
//│ laptop      │  3   │   4    │
//│ telefon     │  1   │   3    │
//│ ksiazka     │  2   │   2    │
//│ słuchawki   │  2   │   3    │
//└─────────────┴──────┴────────┘
// Limit wagi plecaka: W = 4
// Cel: wybierz subset przedmiotów o maksymalnej wartości nie przekraczając limitu wagi W

struct Item
{
    std::string name;
    int weight;
    int value;
};

const std::vector<Item> ITEMS = {
    {"laptop", 3, 4},
    {"telefon", 1, 3},
    {"ksiazka", 2, 2},
    {"sluchawki", 2, 3}
};
const int N = ITEMS.size();
const int W = 4;    // limit wagi plecaka

// Stan aktualnie budowanego subsetu
std::vector<int> current;   // indeksy wybranych przedmiotów
int currentWeight = 0;
int currentValue = 0;

// Najlepszy wynik znaleziony do tej pory
std::vector<int> bestSubset;    // indeksy najlepszego subsetu
int bestValue = 0;              // jego wartość

// ─────────────────────────────────────────────
// Trzymamy indeksy zamiast nazw/wartości –
// dzięki temu z bestSubset możemy później
// odczytać dowolną informację o przedmiocie
// ─────────────────────────────────────────────
void genSubset(int index)
{
    // PRUNING: waga przekroczyła limit –
    // dodawanie kolejnych elementów tylko pogorszy sytuację i nie ma sensu
    if (currentWeight > W) return;

    // WARUNEK STOPU: rozpatrzyliśmy wszystkie przedmioty
    if (index == N)
    {
        // warunek aktualizacji najlepszego subsetu
        if (currentWeight <= W && currentValue > bestValue)
        {
            bestSubset = current;
            bestValue = currentValue;
        }
        return;
    }

    // DECYZJA 1: bierzemy ITEMS[index] do plecaka
    current.push_back(index);
    currentWeight += ITEMS[index].weight;
    currentValue += ITEMS[index].value;

    genSubset(index + 1);   // idziemy głębiej

    current.pop_back();     // cofamy
    currentWeight -= ITEMS[index].weight;
    currentValue -= ITEMS[index].value;

    // DECYZJA 2: pomijamy ITEMS[index]
    genSubset(index + 1);
}

void test_knapsack()
{
    genSubset(0);
    std::cout << "The best subset (W=" << W << "):" << std::endl;
    int totalWeight = 0, totalValue = 0;
    for (int i : bestSubset) {
        std::cout << "  " << ITEMS[i].name
            << "  weight=" << ITEMS[i].weight
            << "  value=" << ITEMS[i].value << std::endl;
        totalWeight += ITEMS[i].weight;
        totalValue += ITEMS[i].value;
    }
    std::cout << "Total: weight=" << totalWeight << "  value=" << totalValue << std::endl;
}

}   // namespace knapsack


int main()
{
    sum_closest_to_target::test_subset_sum_closest_to_target();
    shortest_subset_with_target_sum::test_best_subset_with_shortest_length_and_target_sum_greater_than_condition();
    knapsack::test_knapsack();
    return 0;
}
