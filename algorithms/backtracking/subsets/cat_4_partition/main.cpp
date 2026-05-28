#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits> 


// Zadania - Kategoria 4 – Podział zbioru (partition problem)
// 1. Partition problem – czy da się podzielić zbiór na dwie grupy o równej sumie?
// 2. Balanced partition – podziel na dwie grupy z minimalną różnicą sum
// 3. Podział na k grup o równej sumie


namespace equal_partition
{
    // Cel: podziel zbior collection na dwie grupy o równej sumie

    const std::vector<int> collection = {1, 5, 5, 11};
    const int N = collection.size();
    const int TOTAL = std::accumulate(collection.begin(), collection.end(), 0);
    std::vector<int> current;   // keep indexes here
    int currentSum = 0;
    bool found = false;

    void printPartition()
    {
        std::cout << "Partition:\n" << "First subset: [ ";
        for (auto i : current)
            std::cout << collection[i] << " ";
        std::cout << "]\n";

        std::cout << "Second subset: [ ";
        for (int i = 0; i < N; ++i)
        {
            if (std::find(current.begin(), current.end(), i) == current.end())
                std::cout << collection[i] << " ";
        }
        std::cout << "]\n";
    }

    void genSubset(int index)
    {
        if (true == found) return;

        if (currentSum > (TOTAL / 2)) return;

        if (index == N)
        {
            if (currentSum == (TOTAL / 2))
            {
                found = true;
                printPartition();
            }
            return;
        }

        current.push_back(index);
        currentSum += collection[index];
        genSubset(index + 1);
        current.pop_back();
        currentSum -= collection[index];

        genSubset(index + 1);
    }

    void test_partition()
    {
        std::cout << "Original set: [ ";
        for (auto x : collection)
            std::cout << x << " ";
        std::cout << "]\n";

        if (TOTAL % 2 != 0)
        {
            std::cout << "Cannot partition - total is odd\n";
            return;
        }

        genSubset(0);
        if (found == false)
            std::cout << "Cannot partiotion the original set\n";
    }

}   // namespace equal_partition


namespace balanced_partition
{
    // Cel: Podziel zbior collection na dwie grupy tak żeby różnica ich sum była jak najmniejsza

    const std::vector<int> collection = {3, 1, 4, 2, 5};
    const int N = collection.size();
    const int TOTAL = std::accumulate(collection.begin(), collection.end(), 0);

    std::vector<int> current;
    int currentSum = 0;

    std::vector<int> bestSubset;
    int bestSum = INT_MIN;

    void genSubset(int index)
    {
        if (N == index)
        {
            if (abs((TOTAL / 2) - currentSum) < abs((TOTAL / 2) - bestSum))
            {
                bestSum = currentSum;
                bestSubset = current;
            }
            return;
        }

        current.push_back(index);
        currentSum += collection[index];
        genSubset(index + 1);
        current.pop_back();
        currentSum -= collection[index];

        genSubset(index + 1);
    }

    void test_balanced_partition()
    {
        std::cout << "Original set: [ ";
        for (auto x : collection)
            std::cout << x << " ";
        std::cout << "]\n";

        genSubset(0);

        std::cout << "Balanced Partition with TOTAL / 2 = " << (TOTAL / 2) << "\n" << "First subset: [ ";
        for (auto x : bestSubset)
            std::cout << collection[x] << " ";
        std::cout << "]\n";

        std::cout << "Second subset: [ ";
        for (int i = 0; i < N; ++i)
        {
            if (std::find(bestSubset.begin(), bestSubset.end(), i) == bestSubset.end())
                std::cout << collection[i] << " ";
        }
        std::cout << "]\n";
    }

}   // namespace balanced_partition


int main()
{
    equal_partition::test_partition();
    balanced_partition::test_balanced_partition();
    return 0;
}
