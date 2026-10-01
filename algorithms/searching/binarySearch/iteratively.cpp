#include <iostream>
#include "iteratively.h"


// -------------------------------------------------------
// WERSJA ITERACYJNA – pętla while zawęża przedział [low, high]
// aż do znalezienia elementu lub wyczerpania przedziału
// --
int binarySearchIterative(const std::vector<int> & arr, int target)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // piszemy low + (high-low)/2 zamiast (low+high)/2
        // żeby uniknąć overflow przy bardzo dużych indeksach

        if (arr[mid] == target) {
            // znalezlismy szukany element - zwracamy index tablicy
            return mid;
        } else if (arr[mid] < target) {
            // element srodkowy mniejszy niz target, szukamy dalej w prawej połówce
            left = mid + 1;
        } else {
            // element środkowy większy niż target, szukamy dalek w lewej połówce
            right = mid - 1;
        }
    }

    // nie znaleziono elementu, zwróć -1
    return -1;
}
