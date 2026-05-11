#include <iostream>
#include <vector>

namespace counting_subsets_with_sum_equal_to_target
{
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
    const std::vector<int> collection = {1, 2, 3, 4};
    const int N = collection.size();
    int cnt = 0;
}   // namespace counting_subsets_with_non_adjacent_elements

int main()
{
    //counting_subsets_with_sum_equal_to_target::test_subset_count_with_target_sum();
    counting_subsets_with_even_number_of_elements::test_subset_count_number_of_even_elements();

    return 0;
}

