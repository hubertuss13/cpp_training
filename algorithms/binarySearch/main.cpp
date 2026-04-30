#include <iostream>
#include <vector>

#include "recursively.h"
#include "iteratively.h"

std::vector<int> genArr(int elements)
{
    std::vector<int> vec;
    vec.reserve(elements);
    for (int i = 0; i < elements; ++i)
    {
        vec.push_back(i * 2);
    }

    return vec;
}

namespace search
{

void iterativeSearch(std::vector<int> & arr, int target)
{
    int result = binarySearchIterative(arr, target);
    if (-1 == result) {
        std::cout << "Iterative search: nie znaleziono elementu " << target << std::endl;
    } else {
        std::cout << "Iterative search: znaleziono element: " << target << " na idx=" << result << std::endl;
    }
}

void recursiveSearch(std::vector<int> & arr, int target)
{
    int result = binarySearchRecursive(arr, target, 0, arr.size() - 1);
    if (-1 == result) {
        std::cout << "Recursive search: nie znaleziono elementu " << target << std::endl;
    } else {
        std::cout << "Recursive search: znaleziono element: " << target << " na idx=" << result << std::endl;
    }
}

}   // namespace search


int main()
{
    //std::vector<int> arr = genArr(7);
    std::vector<int> arr = {-4, 0, 1, 2, 3, 11, 13};
    //int target = -4;
    for (auto i : arr) std::cout << i << " ";
    std::cout << std::endl;
    search::iterativeSearch(arr, -4);
    search::iterativeSearch(arr, 0);
    search::iterativeSearch(arr, 1);
    search::iterativeSearch(arr, 2);
    search::iterativeSearch(arr, 3);
    search::iterativeSearch(arr, 11);
    search::iterativeSearch(arr, 13);


    std::cout << std::endl;
    search::recursiveSearch(arr, -4);
    search::recursiveSearch(arr, 0);
    search::recursiveSearch(arr, 1);
    search::recursiveSearch(arr, 2);
    search::recursiveSearch(arr, 3);
    search::recursiveSearch(arr, 11);
    search::recursiveSearch(arr, 13);
    return 0;
}
