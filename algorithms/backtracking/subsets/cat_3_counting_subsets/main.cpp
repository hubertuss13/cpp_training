#include <iostream>
#include <vector>


// Zadania - Kategoria 3 – Zliczanie (ile subsetów spełnia warunek?)
// 1. Ile subsetów ma sumę równą TARGET?
// 2. Ile subsetów ma parzystą liczbę elementów?
// 3. Ile subsetów nie zawiera dwóch kolejnych liczb (bez sasiadow)?


namespace counting_subsets_with_sum_equal_to_target
{
    // Cel: Ze zbioru collection policz ile subsetów ma sumę równą TARGET?

    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    const int TARGET = 5;

    int cnt = 0;
    int currentSum = 0;

    void genSubset(int index)
    {
        if (currentSum > TARGET) return;

        if (index == N)
        {
            if (currentSum == TARGET)
            {
                cnt++;
            }
            return;
        }

        currentSum += collection[index];
        genSubset(index + 1);
        currentSum -= collection[index];


        genSubset(index + 1);
    }

    void test_subset_count_with_target_sum()
    {
        genSubset(0);
        std::cout << "Original subset: [ ";
        for (auto x : collection)
            std::cout << x << " ";
        std::cout << "]\n";
        std::cout << "Number of subsets with TARGET sum = " << TARGET << " is: " << cnt << std::endl;
    }

}   // namespace counting_subsets_with_sum_equal_to_target


namespace counting_subsets_with_even_number_of_elements
{
    // Cel: Ze zbioru collection policz ile subsetów ma parzystą liczbę elementów?

    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    std::vector<int> current;
    int cnt = 0;

    void genSubset(int index)
    {
        if (index == N)
        {
            if (int(current.size()) % 2 == 0)
            {
                cnt++;
            }
            return;
        }

        current.push_back(collection[index]);
        genSubset(index + 1);
        current.pop_back();

        genSubset(index + 1);
    }

    // Alternatywna implementacja bez uzycia current
    // depth -> licznik głębokości
    //
    // void genSubset(int index, int depth)
    // {
    //     if (index == N)
    //     {
    //         if (depth % 2 == 0) cnt++;
    //         return;
    //     }
    //     genSubset(index + 1, depth + 1);  // bierzemy
    //     genSubset(index + 1, depth);      // pomijamy
    // }

    void test_subset_count_number_of_even_elements()
    {
        genSubset(0);
        std::cout << "Original subset: [ ";
        for (auto x : collection)
            std::cout << x << " ";
        std::cout << "]\n";
        std::cout << "Number of subsets with even elements is: " << cnt << std::endl;
    }

}   // namespace counting_subsets_with_even_number_of_elements


namespace counting_subsets_with_non_adjacent_elements
{
    // Cel: Ze zbioru collection policz ile subsetów nie zawiera dwóch sąsiadujących elementów?

    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    int cnt = 0;
    std::vector<int> current;


    void genSubset(int index, int lastIndex)
    {
        if (N == index)
        {
            cnt++;
            return;
        }

        if (current.size() == 0 || index - lastIndex != 1)
        {
            current.push_back(collection[index]);
            genSubset(index + 1, index);
            current.pop_back();
        }

        genSubset(index + 1, lastIndex);
    }

    // Alternatywna implementacja bez uzycia current
    // void genSubset(int index, int lastIndex)
    // {
    //     if (N == index)
    //     {
    //         cnt++;
    //         return;
    //     }

    //     if (lastIndex == -1 || index - lastIndex != 1)
    //     {
    //         genSubset(index + 1, index);  // bierzemy
    //     }
    //     genSubset(index + 1, lastIndex);  // pomijamy
    // }


    void test_subset_count_with_non_adjacent_elements()
    {
        genSubset(0, -1);
        std::cout << "Original subset: [ ";
        for (auto x : collection)
            std::cout << x << " ";
        std::cout << "]\n";
        std::cout << "Number of subsets with non adjacent elements is: " << cnt << std::endl;
    }

}   // namespace counting_subsets_with_non_adjacent_elements


int main()
{
    counting_subsets_with_sum_equal_to_target::test_subset_count_with_target_sum();
    counting_subsets_with_even_number_of_elements::test_subset_count_number_of_even_elements();
    counting_subsets_with_non_adjacent_elements::test_subset_count_with_non_adjacent_elements();

    return 0;
}
