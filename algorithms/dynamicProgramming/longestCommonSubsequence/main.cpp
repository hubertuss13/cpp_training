#include <iostream>

// Dlaczego tablica 2D?
// Bo każdy podproblem jest opisany dwoma parametrami: długością fragmentu X i długością fragmentu Y.
// dp[i][j] = długość LCS dla: pierwszych i znaków X oraz pierwszych j znaków Y

// Jak określić rozmiar tablicy?
// Dla słów X o długości n i Y o długości m:
// tablica ma rozmiar (n+1) × (m+1)
// +1 bo potrzebujesz wiersza i kolumny dla pustego słowa (indeks 0). 
// Pusty fragment X z dowolnym fragmentem Y daje LCS = 0
// Dla X = "ABC" (n=3) i Y = "AC" (m=2): tablica ma rozmiar 4 × 3 (indeksy 0..3 i 0..2)

// Pełne wypełnienie tablicy krok po kroku dla wyrazow X i Y
// X = "ABC"   (indeksy 1, 2, 3 → znaki A, B, C)
// Y = "AC"    (indeksy 1, 2   → znaki A, C)
//
//            j=0  j=1  j=2
//            ""    A    C
//    i=0 ""   0    0    0
//    i=1 A    0    ?    ?
//    i=2 B    0    ?    ?
//    i=3 C    0    ?    ?

// Wypełnianie – reguła:
// Jeśli X[i] == Y[j]:  dp[i][j] = 1 + dp[i-1][j-1]
// Jeśli X[i] != Y[j]:  dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

// Dlaczego dp[i - 1][j - 1] gdy znaki są takie same ? 
// Bo bierzesz ten znak do LCS i cofasz oba palce o jeden – pytasz "jaki był LCS przed tym znakiem?".

// Dlaczego max(dp[i-1][j], dp[i][j-1]) gdy znaki są różne? 
// Bo pomijasz jeden znak – albo cofasz palec w X (dp[i-1][j]) albo cofasz palec w Y (dp[i][j-1]) i bierzesz lepszy wynik.

// Do obliczenia w tablicy wynikowej:
// dp[1][1]     dp[1][2]
// dp[2][1]     dp[2][2]
// dp[3][1]     dp[3][2]

// X=ABC, Y=AC
// 
// 1. Obliczam dp[1][1]: X[1] = A, Y[1] = A
// A == A → takie same!
// dp[1][1] = 1 + dp[0][0] = 1 + 0 = 1

// 2. Obliczam dp[1][2]: X[1] = A, Y[2] = C
// A != C -> różne!
// dp[1][2] = max(dp[0][2], dp[1][1]) = max(0, 1) = 1

// 3. Obliczam dp[2][1]: X[2] = B, Y[1] = A
// B != A -> rozne!
// dp[2][1] = max(dp[1][1], dp[2][0]) = max(1, 0) = 1

// 4. Obliczam dp[2][2]: X[2] = B, Y[2] = C
// B != C -> rozne!
// dp[2][2] = max(dp[1][2], dp[2][1]) = max(1, 1) = 1

// 5. Obliczam dp[3][1]: X[3] = C, Y[1] = A
// C != A -> rozne
// dp[3][1] = max(dp[2][1], dp[3][0]) = max(1, 0) = 1

// 6. Obliczam dp[3][2]: X[3] = C, Y[2] = C
// C == C -> takie same
// dp[3][2] = 1 + dp[2][1] = 1 + 1 = 2

// Gotowa tablica wynikowa:
//            j=0  j=1  j=2
//            ""    A    C
//    i=0 ""   0    0    0
//    i=1 A    0    1    1
//    i=2 B    0    1    1
//    i=3 C    0    1    2

// ODPOWIEDZ zawsze siedzi w prawym dolnym rogu tablicy – dp[n][m].
// Dlaczego? Bo dp[i][j] to LCS dla pierwszych i znaków X i pierwszych j znaków Y.
// Gdy i = n i j = m – masz LCS dla całego X i całego Y.Tego właśnie szukasz.



int main()
{
    std::cout << "===== Dynamic Programming: Longest Common Subsequence (LCS) =====" << std::endl;


    return 0;
}
