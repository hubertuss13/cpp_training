#include <iostream>
#include <vector>

namespace basic
{
    const std::vector<int> collection = {1, 2, 3};  // globalny zbiór niezmienny!
    const int N = collection.size();
    std::vector<int> current;                       // globalny kontekst (aktualnie budowany subset)
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
        // WARUNEK STOPU: rozpatrzyliśmy wszystkie elementy
        // current zawiera gotowy subset – wypisujemy go
        if (index == N)
        {
            cnt++;
            printReadySubset();
            return;
        }

        // DECYZJA 1: bierzemy element collection[index] do subsetu
        current.push_back(collection[index]);
        genSubset(index + 1);   // idziemy głębiej z tym elementem
        current.pop_back();     // cofamy – usuwamy element

        // DECYZJA 2: pomijamy element collection[index]
        // (nie dodajemy nic do current)
        genSubset(index + 1);
    }
}


int main()
{
    basic::genSubset(0);    // zaczynamy od pierwszego elementu (index 0)
    std::cout << "Number of subsets: " << basic::cnt << std::endl;
    return 0;
}
