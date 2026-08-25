#include <iostream>
#include <cmath>

// ─────────────────────────────────────────────────────────────────────────────
// KONFIGURACJA
// N = rozmiar szachownicy i liczba hetmanów do ustawienia.
// queens[r] = kolumna w której stoi hetman w wierszu r.
// Wartość -1 oznacza że w danym wierszu nie ma jeszcze hetmana.
// ─────────────────────────────────────────────────────────────────────────────
const int N = 8;
int queens[N];
int solutionCount = 0;

// ─────────────────────────────────────────────────────────────────────────────
// PRINT_BOARD – wypisuje szachownicę dla bieżącego ustawienia hetmanów.
// Q = hetman, . = puste pole
// ─────────────────────────────────────────────────────────────────────────────
void printBoard()
{
    std::cout << "Rozwiazanie " << solutionCount << ":\n";
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
            std::cout << (queens[r] == c ? "Q " : ". ");
        std::cout << "\n";
    }
    std::cout << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
// IS_SAFE – sprawdza czy można postawić hetmana w wierszu 'row', kolumnie 'col'.
// Sprawdzamy tylko wiersze POWYŻEJ (0..row-1) bo poniżej jeszcze nic nie stoi.
//
// Dwa warunki:
//   1. Kolumna – czy żaden poprzedni hetman nie stoi w tej samej kolumnie
//   2. Przekątna – czy żaden poprzedni hetman nie stoi na tej samej przekątnej
//      Warunek przekątnej: abs(row_i - row) == abs(col_i - col)
//      Jeśli różnica wierszy == różnicy kolumn → ta sama przekątna
// ─────────────────────────────────────────────────────────────────────────────
bool isSafe(int row, int col)
{
    for (int r = 0; r < row; r++)
    {
        // Warunek 1: ta sama kolumna
        if (queens[r] == col) return false;

        // Warunek 2: ta sama przekątna (lewa lub prawa)
        if (std::abs(r - row) == std::abs(queens[r] - col)) return false;
    }
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// SOLVE – backtracking ustawiający hetmanów wiersz po wierszu.
//
// Parametr:
//   row – aktualnie rozpatrywany wiersz (zaczynamy od 0)
//
// Dla każdego wiersza próbujemy każdą kolumnę (0..N-1).
// Jeśli kolumna jest bezpieczna – stawiamy hetmana i przechodzimy do
// następnego wiersza. Jeśli żadna kolumna nie pasuje – cofamy się.
//
// Kluczowa różnica względem poprzednich zadań:
//   - NIE zwracamy true przy pierwszym rozwiązaniu
//   - kontynuujemy żeby znaleźć WSZYSTKIE rozwiązania
//   - zamiast return true → zliczamy i wypisujemy
// ─────────────────────────────────────────────────────────────────────────────
void solve(int row)
{
    // WARUNEK STOPU: ustawiliśmy hetmana w każdym wierszu – znaleziono rozwiązanie!
    if (row == N)
    {
        solutionCount++;
        printBoard();
        return;  // wracamy żeby szukać kolejnych rozwiązań
    }

    // Próbujemy każdą kolumnę w bieżącym wierszu
    for (int col = 0; col < N; col++)
    {
        // PRUNING: ta kolumna jest atakowana – pomijamy
        if (!isSafe(row, col)) continue;

        // ZRÓB KROK: postaw hetmana w (row, col)
        queens[row] = col;

        // IDŹ GŁĘBIEJ: ustaw hetmana w następnym wierszu
        solve(row + 1);

        // COFNIJ KROK: usuń hetmana (wróć do "brak hetmana")
        // Tutaj cofanie jest niejawne – queens[row] zostanie nadpisane
        // przez następną iterację pętli lub pozostanie bez znaczenia
        // gdy wrócimy wyżej (row-1 nadpisze queens[row-1])
        queens[row] = -1;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    std::cout << "===== N-Queens - Hetmani na Szachownicy (N=" << N << ") =====\n\n";

    // Inicjalizujemy wszystkie wiersze jako puste
    for (int r = 0; r < N; r++) queens[r] = -1;

    solve(0);  // zaczynamy od wiersza 0

    std::cout << "Liczba rozwiazań dla N=" << N << ": " << solutionCount << "\n";
    return 0;
}
