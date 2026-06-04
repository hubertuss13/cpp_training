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
        std::cout << "CNT:" << cnt << std::endl << std::endl;
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
        std::cout << "CNT=" << cnt << std::endl << std::endl;
    }

}  // namespace powerset


namespace subsets_with_no_duplicates
{
    // Cel: Ze zbioru collection zawierajacego powtorzenia wygeneruj wszystkie unikalne subsety

    // Zasada: Jeśli NUMS[index] == NUMS[index-1] i poprzedni element został pominięty – wzięcie bieżącego elementu da duplikat. Odcinamy gałąź wzięcia.
    // Ścieżka A: BIERZEMY  pierwsze 2, pomijamy drugie 2 → { 1, 2 }
    // Ścieżka B: POMIJAMY  pierwsze 2, BIERZEMY drugie 2 → { 1, 2 }  ← duplikat!

    // W kodzie potrzebujesz wiedzieć czy poprzedni element był wzięty czy pominięty. Jak to śledzić? Masz dwie opcje:
    // Opcja A: dodać parametr bool prevTaken do funkcji rekurencyjnej.
    // Opcja B: użyć wektora used[] podobnie jak przy permutacjach.

    std::vector<int> collection = {2, 1, 2};
    const int N = collection.size();
    int cnt = 0;
    std::vector<int> current;

    void print(std::vector<int> & arr, std::string label = "")
    {
        std::cout << label << " [ ";
        for (int x : arr)
            std::cout << x << " ";
        std::cout << "]\n";
    }


    int partition(int left, int right)
    {
        int pivot = collection[right];
        int border = left - 1;

        for (int i = left; i < right; ++i)
        {
            if (collection[i] <= pivot)
            {
                border++;
                std::swap(collection[border], collection[i]);
            }
        }
        std::swap(collection[border + 1], collection[right]);
        return (border + 1);
    }

    void quicksort(int left, int right)
    {
        if (left >= right) return;

        int pivotIdx = partition(left, right);
        quicksort(left, pivotIdx - 1);
        quicksort(pivotIdx + 1, right);
    }

    void genSubset(int index, bool prevTaken)
    {
        if (index == N)
        {
            cnt++;
            print(current);
            return;
        }

        if (index == 0 || collection[index] != collection[index - 1] || prevTaken == true)
        {
            // DECYZJA 1: bierzemy collection[index] – ale tylko gdy nie jest duplikatem pominiętego
            current.push_back(collection[index]);
            genSubset(index + 1, true);
            current.pop_back();
        }

        // DECYZJA 2: pomijamy collection[index] – zawsze legalne
        genSubset(index + 1, false);
    }

    void test_no_duplicated_subsets()
    {
        print(collection, "Test unique subsets from original duplicated set:");
        quicksort(0, N - 1);
        print(collection, "Sorted set:");
        genSubset(0, false);
        std::cout << "CNT: " << cnt << std::endl << std::endl;
    }

} // namespace subsets_with_no_duplicates

int main()
{
    k_element_combination::test_combination();
    powerset::test_powerset();
    subsets_with_no_duplicates::test_no_duplicated_subsets();
    return 0;
}
