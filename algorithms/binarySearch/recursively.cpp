#include <iostream>
#include "recursively.h"

int binarySearchRecursive(std::vector<int> & arr, int target, int left, int right)
{
    // przedział pusty -> nie znaleziono
    if (left > right) return -1;

    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        // srodkowy element mniejszy niz target -> szukaj w prawej połówce
        return binarySearchRecursive(arr, target, mid + 1, right);
    } else {
        // srodkowy element wiekszy niz target -> szukaj w lewej połówce
        return binarySearchRecursive(arr, target, left, mid -1);
    }
}
