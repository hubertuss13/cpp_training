#include <iostream>
#include <string>

#include "quicksort.h"

constexpr int N = 8;

void printTab(int * tab, int rozmiar, std::string text)
{
    std::cout << text;
    std::cout << ": [ ";
    for (int i = 0; i < rozmiar; ++i)
        std::cout << tab[i] << " ";
    std::cout << "]\n";
}

int main()
{
    int tab[N] = {8, 6, 3, 0, 10, 4, 2, 9};
    printTab(tab, N, "Tablica nieposortowana");

    quicksort(tab, 0, N - 1);

    printTab(tab, N, "Tablica posortowana");
    return 0;
}
