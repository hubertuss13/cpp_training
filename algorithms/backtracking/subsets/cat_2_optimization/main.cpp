#include <iostream>
#include <vector>
#include <climits>   // INT_MAX, INT_MIN
#include <iterator>
//#include <cstdlib>   // abs() dla int

namespace sum_closest_to_target
{

    const std::vector<int> collection = {3, 4, 5, 7};
    const int N = collection.size();
    const int target = 11;

    std::vector<int> current;
    std::vector<int> bestSubset;
    int currentSum;
    int bestSum = INT_MAX;

    void genSubset(int index)
    {
        if (index == N)
        {
            if (abs(target - currentSum) < abs(target - bestSum))
            {
                bestSum = currentSum;
                bestSubset = current;
            }
            return;
        }

        current.push_back(collection[index]);
        currentSum += collection[index];
        genSubset(index + 1);
        current.pop_back();
        currentSum -= collection[index];

        genSubset(index + 1);
    }

    void test_subset_sum_closest_to_target()
    {
        genSubset(0);
        std::cout << "Best subset with target=" << target << " from original set [ ";
        std::copy(collection.begin(), collection.end(), std::ostream_iterator<int>(std::cout, " ")); 
        std::cout << "] is: \n[ ";
        std::copy(bestSubset.begin(), bestSubset.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "] and bestSum is:" << bestSum << std::endl;
    }

}


int main()
{
    sum_closest_to_target::test_subset_sum_closest_to_target();

    return 0;
}
