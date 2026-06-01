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

    void test_equal_partition()
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

namespace k_groups_with_equal_sum
{
    // Cel: podziel zbior collection na k grup o rownej sumie
    const std::vector<int> collection = {4, 3, 2, 3, 5, 2, 1};
    const int N = collection.size();
    const int K = 4;
    const int TOTAL = std::accumulate(collection.begin(), collection.end(), 0);
    const int TARGET = TOTAL / K;  // suma, ktora musi osiagnac kazda z k grup

    std::vector<int> groupsCurrentSum(K, 0);      // K grup - kazda trzyma swoja biezaca sume
    std::vector<std::vector<int>> groupItems(K);  // Trzymamy które elementy (indeksy) trafiły do której grupy
    std::vector<std::vector<int>> bestGroupItems; // Najlepszy znaleziony podział – zapisujemy w momencie znalezienia
    bool found = false;

    // ─────────────────────────────────────────────────────────────
    // Dla każdego elementu collection[index] próbujemy wrzucić go
    // do jednej z K grup. Pętla for zastępuje dwie gałęzie weź/pomiń
    // z poprzednich zadań – tutaj mamy K gałęzi zamiast dwóch.
    // ─────────────────────────────────────────────────────────────
    void genSubset(int index)
    {
        // Już znaleźliśmy rozwiązanie – przerywamy całe przeszukiwanie
        if (true == found) return;

        // WARUNEK STOPU: wszystkie elementy przypisane do jakiejś grupy.
        // Skoro żadna grupa nie przekroczyła TARGET podczas przypisywania
        // i suma wszystkich grup == TOTAL == K * TARGET,
        // to każda grupa musi mieć dokładnie TARGET.
        if (index == N)
        {
            found = true;
            // Zapisujemy stan grup w momencie znalezienia rozwiązania –
            // po powrocie z rekurencji groups[] zostanie cofnięte do zera
            bestGroupItems = groupItems;
            return;
        }

        // PĘTLA DECYZYJNA: próbujemy wrzucić collection[index] do każdej grupy
        for (int i = 0; i < K; ++i)
        {
            // PRUNING 1: element nie mieści się w tej grupie – suma przekroczyłaby TARGET
            if (groupsCurrentSum[i] + collection[index] > TARGET) continue;

            // PRUNING 2: ta grupa ma taką samą sumę co poprzednia.
            // Wrzucenie elementu da identyczny wynik jak do poprzedniej grupy
            // – pomijamy żeby uniknąć duplikatów i niepotrzebnej pracy.
            if (i > 0 && groupsCurrentSum[i] == groupsCurrentSum[i - 1]) continue;

            // ZRÓB KROK: wrzuć element do grupy i
            groupsCurrentSum[i] += collection[index];
            groupItems[i].push_back(index);

            // IDŹ GŁĘBIEJ: przypisz następny element
            genSubset(index + 1);

            // CONFNIJ KROK
            groupsCurrentSum[i] -= collection[index];
            groupItems[i].pop_back();

            // Jeśli znaleźliśmy rozwiązanie podczas rekurencji – przerywamy pętlę
            if (found) return;
        }
    }

    void test_partition()
    {
        std::cout << "Zbior:  [ ";
        for (auto x : collection) std::cout << x << " ";
        std::cout << "]\n";
        std::cout << "TOTAL=" << TOTAL << "  K=" << K << "  TARGET=" << TARGET << "\n\n";

        // Sprawdzamy niemozliwy przypadek zanim odpalimy backtracking
        if (TOTAL % K != 0)
        {
            std::cout << "Niemozliwe – TOTAL=" << TOTAL
                      << " nie dzieli sie przez K=" << K << "\n";
            return;
        }

        genSubset(0);

        if (found)
        {
            std::cout << "Mozliwy podzial na " << K << " grupy po " << TARGET << ":\n";
            for (int i = 0; i < K; i++)
            {
                int sum = 0;
                std::cout << "  Grupa " << i + 1 << ": [ ";
                for (int idx : bestGroupItems[i])
                {
                    std::cout << collection[idx] << " ";
                    sum += collection[idx];
                }
                std::cout << "]  suma = " << sum << "\n";
            }
        }
        else
        {
            std::cout << "Niemozliwe – nie da sie podzielic na "
                      << K << " rowne grupy\n";
        }
    }

}  // namespace k_groups_with_equal_sum


int main()
{
    //equal_partition::test_equal_partition();
    //balanced_partition::test_balanced_partition();
    k_groups_with_equal_sum::test_partition();
    return 0;
}
