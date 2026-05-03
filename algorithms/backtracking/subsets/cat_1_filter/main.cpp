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

        // DECYZJA 2: pomijamy collection[index]
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

namespace target_length
{
    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    const int K = 2;    // szukamy subsetów o długości dokładnie K

    std::vector<int> current;
    int cnt;


    void printTargetSubset()
    {
        cnt++;
        std::cout << "[ ";
        for (int x : current)
            std::cout << x << " ";
        std::cout << "]\n";
    }
    // Przypadek A: mamy już w current za dużo elementów – więcej niż K. Czy ma sens schodzić głębiej?
    // Przypadek B: mamy już dokładnie K elementów w current, ale index != N. Czy ma sens schodzić głębiej?
    // Przypadek C (trudniejszy): zostało nam do rozpatrzenia bardzo mało elementów – 
    //             tak mało, że nawet gdybyśmy wzięli wszystkie pozostałe, nadal nie dobilibyśmy do K elementów. Czy ma sens schodzić głębiej?
    void genSubset(int index)
    {
        // PRUNING A: mamy już za dużo elementów – ta gałąź nie ma sensu
        // USUNIĘTY->zakomentowany, bo nigdy nie był osiągany w tej implementacji
        // tzn. Warunek stopu działa jak "sufit" – gdy current.size() == K zawsze wracamy, więc current.size() nigdy nie ma szansy przekroczyć K
        // if (static_cast<int>(current.size()) > K) return;

        // PRUNING C: zostało za mało elementów żeby dobić do K
        if ((N - index) < (K - static_cast<int>(current.size()))) return;

        // WARUNEK STOPU B: mamy dokładnie K elementów – znaleźliśmy subset
        if (static_cast<int>(current.size()) == K)
        {
            printTargetSubset();
            return;
        }

        // DECYZJA 1: bierzemy collection[index]
        current.push_back(collection[index]);
        genSubset(index + 1);   // idz głębiej
        current.pop_back();     // powrót-cofamy

        // DECYZJA 2: pomijamy collection[index]
        genSubset(index + 1);
    }

    void test_gen_subset_with_given_K_length()
    {
        std::cout << "Initial set: [ ";
        for (int i : target_length::collection) std::cout << i << " ";
        std::cout << "]\n";
        std::cout << "Subsets with target length equal to " << K << ":\n";
        target_length::genSubset(0);
        std::cout << "Cnt: " << target_length::cnt << std::endl;
    }
}

namespace even_sum
{
    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    std::vector<int> current;
    int currentSubsetSum = 0;   // śledzimy sumę na bieżąco – tak jak przy sumie TARGET
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
        // WARUNEK STOPU: rozpatrzyliśmy wszystkie elementy.
        // Sprawdzamy parzystość sumy – wypisujemy tylko gdy parzysta.
        // Nie ma tu żadnego pruningu – musimy zawsze dojść do liścia drzewa.
        if (index == N)
        {
            if (currentSubsetSum % 2 == 0)
            {
                printTargetSubset();
            }
            return;
        }

        // DECYZJA 1: bierzemy collection[index]x]
        current.push_back(collection[index]);
        currentSubsetSum += collection[index];
        genSubset(index + 1);                   // idziemy glebiej
        current.pop_back();                     // cofamy element
        currentSubsetSum -= collection[index];  // cofamy sumę

        // DECYZJA 2: pomijamy collection[index]
        genSubset(index + 1);
    }

    void test_gen_subset_with_even_sum()
    {
        std::cout << "Initial set: [ ";
        for (int i : even_sum::collection) std::cout << i << " ";
        std::cout << "]\n";
        std::cout << "Subsets with even sum:\n";
        even_sum::genSubset(0);
        std::cout << "Cnt: " << even_sum::cnt << std::endl;
    }
}

int main()
{
    target_sum::test_gen_subset_with_target_sum_equal_to_target();
    target_length::test_gen_subset_with_given_K_length();
    even_sum::test_gen_subset_with_even_sum();
    return 0;
}
