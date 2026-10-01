#include <iostream>
#include "quicksort.h"

// -------------------------------------------------------
// QUICKSORT – wywołuje się rekurencyjnie na dwóch połówkach
// low  = indeks początku aktualnego fragmentu tablicy
// high = indeks końca aktualnego fragmentu tablicy
// -------------------------------------------------------
void quicksort(int * arr, int low, int high)
{
    // warunek wyjścia z rekurencji: fragment tablicy ma 0 lub 1 element – już posortowany
    if (low >= high)
        return;

    int pivotIndex = partition(arr, low, high);     // podziel tablicę względem pivota (na lewo mniejsze, na prawo większe)
    quicksort(arr, low, pivotIndex - 1);            // sortuj lewą część (mniejsze od pivota)
    quicksort(arr, pivotIndex + 1, high);           // sortuj prawą część (większe od pivota)
}


// -------------------------------------------------------
// PARTITION – serce algorytmu
// Przesuwa elementy tak, żeby:
//   - po lewej stronie pivota były elementy mniejsze
//   - po prawej stronie pivota były elementy większe
// Zwraca INDEKS gdzie wylądował pivot po przesunięciu
// -------------------------------------------------------
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];  // ostatni element jako pivot
    int i = low - 1;  // granica/marker swap - granica między mniejszymi a resztą
    
    for (int j = low; j < high; j++)
    {
        // Jeśli bieżący element jest mniejszy lub równy pivotowi...
        if (arr[j] <= pivot)
        {
            ++i;                            // przesuń granicę w prawo
            std::swap(arr[i], arr[j]);      // wrzuć element za granicę
        }
    }

    // Na końcu wstaw pivot na właściwe miejsce (tuż za granicą)
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);     // zwróć pozycję pivota
}
