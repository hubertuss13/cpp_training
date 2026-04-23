#include "genPermGlobalContext.h"


int main()
{
    PermutationGlobalContext p1({1, 2, 3, 4});
    p1.generatePerm(0);     // startujemy z głębokości 0 – current jest pusty
    std::cout << "\nLiczba permutacji: " << p1.getResultCnt() << std::endl; // powinno być 4! = 24
    return 0;
}
