#include <iostream>

// ─────────────────────────────────────────────────────────────────────────────
// REPREZENTACJA PLANSZY
// Plansza 9x9 gdzie 0 oznacza pustą komórkę.
// Indeksowanie: board[row][col], row i col w zakresie [0, 8].
// ─────────────────────────────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────────────────────────────
// IS_SAFE – sprawdza czy można wstawić 'num' do komórki (row, col).
// Sprawdza trzy niezależne warunki Sudoku:
//   1. Wiersz    – num nie może wystąpić w tym samym wierszu
//   2. Kolumna   – num nie może wystąpić w tej samej kolumnie
//   3. Kwadrat   – num nie może wystąpić w tym samym kwadracie 3x3
// ─────────────────────────────────────────────────────────────────────────────
bool isSafe(int board[9][9], int row, int col, int num)
{
    // Lewy górny róg kwadratu 3x3 do którego należy (row, col).
    // Dzielenie całkowite "obcina" resztę, mnożenie przywraca skalę.
    // Przykład: row=4 → (4/3)*3 = 3 → górny róg kwadratu środkowego pasa.
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;

    // Warunek 1: sprawdź cały wiersz 'row'
    for (int c = 0; c < 9; c++)
        if (board[row][c] == num) return false;

    // Warunek 2: sprawdź całą kolumnę 'col'
    for (int r = 0; r < 9; r++)
        if (board[r][col] == num) return false;

    // Warunek 3: sprawdź kwadrat 3x3
    // Iterujemy po 9 komórkach kwadratu zaczynając od lewego górnego rogu
    for (int r = boxRow; r < boxRow + 3; r++)
        for (int c = boxCol; c < boxCol + 3; c++)
            if (board[r][c] == num) return false;

    // Żaden warunek nie został naruszony – num jest legalny w (row, col)
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// SOLVE – backtracking na planszy Sudoku.
// Zwraca true  gdy plansza jest rozwiązana.
// Zwraca false gdy żadna cyfra nie pasuje – sygnał do cofnięcia się.
//
// Kluczowa różnica względem subsetów: funkcja zwraca bool i natychmiast
// propaguje true w górę przez wszystkie poziomy rekurencji.
// Przy subsetach zawsze przechodziłeś całe drzewo – tutaj zatrzymujesz się
// przy pierwszym rozwiązaniu.
// ─────────────────────────────────────────────────────────────────────────────
bool solve(int board[9][9])
{
    // KROK 1: znajdź pierwszą pustą komórkę (oznaczoną jako 0)
    int emptyRow = -1;
    int emptyCol = -1;
    bool foundEmpty = false;

    for (int r = 0; r < 9 && !foundEmpty; r++)
    {
        for (int c = 0; c < 9 && !foundEmpty; c++)
        {
            if (board[r][c] == 0)
            {
                emptyRow   = r;
                emptyCol   = c;
                foundEmpty = true;
            }
        }
    }

    // WARUNEK STOPU: brak pustych komórek → plansza wypełniona → sukces!
    // Skoro każda wstawiona cyfra przechodziła przez isSafe(),
    // wypełniona plansza musi być poprawnym rozwiązaniem.
    if (!foundEmpty) return true;

    // KROK 2: próbuj wstawić cyfry 1-9 do pustej komórki
    for (int num = 1; num <= 9; num++)
    {
        // PRUNING: cyfra nie spełnia zasad Sudoku – pomijamy
        if (!isSafe(board, emptyRow, emptyCol, num)) continue;

        // ZRÓB KROK: wstaw cyfrę
        board[emptyRow][emptyCol] = num;

        // IDŹ GŁĘBIEJ: spróbuj rozwiązać resztę planszy
        if (solve(board)) return true;  // rozwiązanie znalezione – propaguj true w górę!

        // COFNIJ KROK: ta cyfra nie doprowadziła do rozwiązania
        // Resetujemy komórkę i próbujemy następną cyfrę
        board[emptyRow][emptyCol] = 0;
    }

    // Żadna cyfra (1-9) nie pasuje do tej komórki →
    // błąd we wcześniejszych decyzjach → sygnał do cofnięcia
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// PRINT_BOARD – wypisuje planszę z separatorami co 3 wiersze i kolumny
// ─────────────────────────────────────────────────────────────────────────────
void printBoard(int board[9][9])
{
    for (int r = 0; r < 9; r++)
    {
        // Separator poziomy między blokami 3x3
        if (r != 0 && r % 3 == 0)
            std::cout << "------+-------+------\n";

        for (int c = 0; c < 9; c++)
        {
            // Separator pionowy między blokami 3x3
            if (c != 0 && c % 3 == 0)
                std::cout << "| ";

            // Pusta komórka jako kropka – czytelniejsze niż 0
            if (board[r][c] == 0)
                std::cout << ". ";
            else
                std::cout << board[r][c] << " ";
        }
        std::cout << "\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    // Klasyczna plansza Sudoku – 0 oznacza pustą komórkę
    int board[9][9] = {
        {5, 3, 0,  0, 7, 0,  0, 0, 0},
        {6, 0, 0,  1, 9, 5,  0, 0, 0},
        {0, 9, 8,  0, 0, 0,  0, 6, 0},

        {8, 0, 0,  0, 6, 0,  0, 0, 3},
        {4, 0, 0,  8, 0, 3,  0, 0, 1},
        {7, 0, 0,  0, 2, 0,  0, 0, 6},

        {0, 6, 0,  0, 0, 0,  2, 8, 0},
        {0, 0, 0,  4, 1, 9,  0, 0, 5},
        {0, 0, 0,  0, 8, 0,  0, 7, 9},
    };

    std::cout << "===== Sudoku Solver =====\n\n";

    std::cout << "Plansza przed rozwiazaniem:\n";
    printBoard(board);
    std::cout << "\n";

    if (solve(board))
    {
        std::cout << "Rozwiazanie znalezione:\n";
        printBoard(board);
    }
    else
    {
        std::cout << "Brak rozwiazania dla podanej planszy!\n";
    }

    return 0;
}
