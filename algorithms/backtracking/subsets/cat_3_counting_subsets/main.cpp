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
}

int main()
{
    counting_subsets_with_sum_equal_to_target::test_subset_count_with_target_sum();

    return 0;
}

