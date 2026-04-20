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

int main()
{
    std::vector<int> arr = genArr(7);
    int result = -1, target = 10;
    for (auto i : arr) std::cout << i << " ";
    std::cout << std::endl;
    result = binarySearchIterative(arr, target);
    if (-1 == result) {
        std::cout << "Iterative search: nie znaleziono elementu " << target << std::endl;
    } else {
        std::cout << "Iterative search: znaleziono element " << target << " idx=" << result << std::endl;
    }

    result = binarySearchRecursive(arr, target, 0, arr.size() - 1);
    if (-1 == result) {
        std::cout << "Recursive search: nie znaleziono elementu " << target << std::endl;
    } else {
        std::cout << "Recursive search: znaleziono element " << target << " idx=" << result << std::endl;
    }

    return 0;
}
