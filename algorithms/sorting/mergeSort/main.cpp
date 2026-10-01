#include <iostream>
#include <vector>

// [8, 3, 5, 1, 6, 2, 7, 4]
//          ↓ dziel na pół
// [8, 3, 5, 1]    [6, 2, 7, 4]
//      ↓ dziel          ↓ dziel
// [8, 3] [5, 1]   [6, 2] [7, 4]
//   ↓        ↓      ↓        ↓
// [8][3]  [5][1]  [6][2]  [7][4]   ← tablice 1-elementowe, już posortowane!
//   ↓ merge  ↓ merge  ↓ merge  ↓ merge
//  [3,8]  [1,5]   [2,6]   [4,7]
//       ↓ merge        ↓ merge
//    [1,3,5,8]      [2,4,6,7]
//             ↓ merge
//       [1,2,3,4,5,6,7,8] ✅


// ─────────────────────────────────────────────────────────────
// MERGE – serce algorytmu. Scala dwie posortowane połówki:
// lewą  [left  ... mid]
// prawą [mid+1 ... right]
// w jedną posortowaną całość.
// Potrzebuje pomocniczej tablicy 'temp' – tu jest koszt O(n) pamięci.
void merge(std::vector<int> & arr, int left, int mid, int right)
{
    std::vector<int> tmp;   // pomocnicza tablica na scalony wynik

    int i = left;           // iterator lewej polowki
    int j = mid + 1;        // iterator prawej polowki

    // Porównujemy elementy z obu połówek i wstawiamy mniejszy do temp.
    // Gdy jeden z iteratorów wyjdzie poza swoją połówkę – przerywamy pętlę.
    while (i <= mid && j <=right)
    {
        if (arr[i] <= arr[j])
        {
            tmp.push_back(arr[i]);
            // lewa połówka dała mniejszy element – przesuwamy jej iterator
            i++;
        }
        else
        {
            tmp.push_back(arr[j]);
            // prawa połówka dała mniejszy element – przesuwamy jej iterator
            j++;
        }
    }

    // Jedna z połówek mogła mieć jeszcze elementy – dopisujemy resztę.
    // Tylko jedna z tych pętli faktycznie wykona iteracje.
    while (i <= mid)
    {
        tmp.push_back(arr[i]);
        i++;
    }
    while (j <= right)
    {
        tmp.push_back(arr[j]);
        j++;
    }

    // Przepisujemy posortowane elementy z temp z powrotem do arr.
    // To jest moment gdzie "zapłaciliśmy" za dodatkową pamięć.
    for (int k = 0; k < (int)tmp.size(); ++k)
    {
        arr[left + k] = tmp[k];
    }
}

// ─────────────────────────────────────────────────────────────
// MERGE SORT – rekurencyjnie dzieli tablicę na pół
// aż do tablic jednoelementowych, a potem scala je przez merge().
// Faza dzielenia nie robi żadnego sortowania – tylko wyznacza granice.
// ─────────────────────────────────────────────────────────────
void mergesort(std::vector<int> & arr, int left, int right)
{
    // WARUNEK STOPU: tablica jednoelementowa jest już posortowana
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    mergesort(arr, left, mid);          // sortuj lewą połówkę
    mergesort(arr, mid + 1, right);     // sortuj prawą połówkę

    merge(arr, left, mid, right);       // scal obie posortowane połówki
}


void printArr(const std::vector<int> & arr, std::string label = "Array = ")
{
    std::cout << label << std::endl;
    std::cout << "[ ";
    for (auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl << std::endl;
}

int main()
{
    std::vector<int> arr = {39, 1, 14, 4, 7, 3, 10, 0, 19};
    printArr(arr, "Array before sort:");
    mergesort(arr, 0, arr.size() - 1);
    printArr(arr, "Array after sort:");

    return 0;
}
