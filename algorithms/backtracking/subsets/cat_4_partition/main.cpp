#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

namespace equal_partition
{
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
        if (TOTAL % 2 != 0) return;
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

        genSubset(0);
        if (found == false)
            std::cout << "Cannot partiotion the original set\n";

    }

}   // namespace equal_partition

int main()
{
    equal_partition::test_partition();
    return 0;
}
