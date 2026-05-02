#include <iostream>
#include <vector>

namespace target_sum
{
    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    std::vector<int> current;
    int currentSubsetSum = 0;
    const int targetSum = 6;
    int cnt = 0;


    void printTargetSubset()
    {
        cnt++;
        std::cout << "[ ";
        for (int x : current)
            std::cout << x << " ";
        std::cout << "]\n";
    }

    void genSubset(int index)
    {
        // PRUNING 1: suma przekroczyła target – ta gałąź nie ma sensu.
        // Nie ma potrzeby schodzić głębiej, bo elementy są dodatnie
        // i suma będzie tylko rosnąć.
        if (currentSubsetSum > targetSum)
        {
            return;
        }

        // PRUNING 2: suma == target – znaleźliśmy poprawny subset.
        // Nie ma sensu dokładać kolejnych elementów, więc wypisujemy i wracamy.
        if (currentSubsetSum == targetSum)
        {
            printTargetSubset();
            return;
        }

        // WARUNEK STOPU: przeszliśmy wszystkie elementy.
        // Jeśli doszliśmy tutaj, to suma != TARGET – nic nie robimy.
        if (index == N)
        {
            return;
        }

        // DECYZJA 1: bierzemy collection[index]
        current.push_back(collection[index]);
        currentSubsetSum += collection[index];

        genSubset(index + 1);                       // idziemy głębiej

        current.pop_back();                         // cofamy
        currentSubsetSum -= collection[index];      // cofamy sumę

        genSubset(index + 1);
    }

    void test_gen_subset_with_target_sum_equal_to_target()
    {
        std::cout << "Initial set: [ ";
        for (int i : target_sum::collection) std::cout << i << " ";
        std::cout << "]\n";
        std::cout << "Subsets with target sum equal to 6:\n";
        target_sum::genSubset(0);
        std::cout << "Cnt: " << target_sum::cnt << std::endl;
    }
}

int main()
{
    target_sum::test_gen_subset_with_target_sum_equal_to_target();
    return 0;
}
