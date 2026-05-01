#include <iostream>
#include <vector>

namespace basic
{
    const std::vector<int> collection = {1, 2, 3};
    const int N = collection.size();
    std::vector<int> current;
    int cnt;

    void printReadySubset()
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
            printReadySubset();
            return;
        }

        current.push_back(collection[index]);
        genSubset(index + 1);
        current.pop_back();


        genSubset(index + 1);
    }
}


int main()
{
    basic::genSubset(0);
    std::cout << "Number of subsets: " << basic::cnt << std::endl;
    return 0;
}
