#include <iostream>
#include <vector>


// Zadania - Kategoria 5 – Zadania kombinatoryczne
// 1. Kombinacje k elementów z n - wygeneruj wszystkie subsety dokładnie k-elementowe
// 2. Power set – wygeneruj absolutnie wszystkie subsety
// 3. Subsety bez duplikatów – gdy zbiór wejściowy zawiera powtórzenia

namespace k_element_combination
{
    // Cel: Wygeneruj wszystkie możliwe kombinacje k elementów z podanego zbioru collection

    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    const int K = 2;
    int cnt = 0;

    std::vector<int> current;

    void printSubset()
    {
        std::cout << "[ ";
        for (int x : current)
            std::cout << x << " ";
        std::cout << "]\n";
    }

    void genSubset(int index)
    {
        if (current.size() > K) return;
        if (current.size() == K)
        {
            cnt++;
            printSubset();
            return;
        }
        if (index == N)
        {
            return;
        }

        current.push_back(collection[index]);
        genSubset(index + 1);
        current.pop_back();

        genSubset(index + 1);
    }

    void test_combination()
    {
        std::cout << "Test k= " << K << " element combination from set: [1, 2, 3, 4]\n";
        genSubset(0);
        std::cout << "CNT:" << cnt << std::endl;
    }

} // namespace k_element_combination


namespace powerset
{
    // Cel: Wygeneruj wszystkie możliwe subsety ze zbioru collection
    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    int cnt = 0;
    std::vector<int> current;

    void printSubset()
    {
        std::cout << "[ ";
        for (int x : current)
            std::cout << x << " ";
        std::cout << "]\n";
    }

    void genSubset(int index)
    {
        if (index == N)
        {
            cnt++;
            printSubset();
            return;
        }

        current.push_back(collection[index]);
        genSubset(index + 1);
        current.pop_back();

        genSubset(index + 1);
    }

    void test_powerset()
    {
        std::cout << "Test powerset of original set: [1, 2, 3, 4]\n";
        genSubset(0);
        std::cout << "CNT=" << cnt << std::endl;
    }

}  // namespace powerset


namespace subsets_with_no_duplicates
{
    // Cel: Ze zbioru collection zawierajacego powtorzenia wygeneruj wszystkie unikalne subsety


} // namespace subsets_with_no_duplicates

int main()
{
    k_element_combination::test_combination();
    powerset::test_powerset();
    return 0;
}
