#include <iostream>
#include <vector>

void printArr(const std::vector<int> & arr, std::string label = "Array = ")
{
    std::cout << label << std::endl;
    std::cout << "[ ";
    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
}

int main()
{
    std::vector<int> arr = {39, 1, 14, 4, 7, 3, 10, 0, 19};
    printArr(arr, "Array before sort:");

    return 0;
}
