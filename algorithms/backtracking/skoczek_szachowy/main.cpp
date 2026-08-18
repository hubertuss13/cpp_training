#include <iostream>

// ─────────────────────────────────────────────────────────────────────────────
// KONFIGURACJA
// N = rozmiar szachownicy (N×N)
// board[r][c] = 0 oznacza pole nieodwiedzone
// board[r][c] = k oznacza że skoczek odwiedził to pole jako k-ty ruch
// ─────────────────────────────────────────────────────────────────────────────
const int N = 5;
int board[N][N] = {};

// ─────────────────────────────────────────────────────────────────────────────
// 8 MOŻLIWYCH SKOKÓW SKOCZKA
// Ruch skoczka to zawsze kombinacja (±1, ±2) lub (±2, ±1) – kształt litery L.
// DR[d] i DC[d] to zmiana wiersza i kolumny dla kierunku d.
// ─────────────────────────────────────────────────────────────────────────────
const int DR[] = {-1, -2, -1, -2,  1,  1,  2,  2};
const int DC[] = {-2, -1,  2,  1, -2,  2, -1,  1};

// ─────────────────────────────────────────────────────────────────────────────
// IS_VALID – sprawdza czy skok na pole (row, col) jest legalny:
//   1. Pole mieści się w granicach szachownicy
//   2. Pole nie było jeszcze odwiedzone (board[row][col] == 0)
// ─────────────────────────────────────────────────────────────────────────────
bool isValid(int row, int col)
{
    if (row < 0 || row >= N || col < 0 || col >= N) return false;
    if (board[row][col] != 0) return false;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// PRINT_BOARD – wypisuje szachownicę z numerami kroków
// ─────────────────────────────────────────────────────────────────────────────
void printBoard()
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
            printf("%3d", board[r][c]);  // wyrównanie do 3 znaków
        std::cout << "\n";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// SOLVE – backtracking dla Knight's Tour.
//
// Parametry:
//   row, col – aktualna pozycja skoczka
//   step     – numer bieżącego kroku (zaczyna od 1)
//
// Zwraca true  gdy wszystkie N*N pól zostały odwiedzone.
// Zwraca false gdy skoczek utknął i musi się cofnąć.
//
// Kluczowa różnica względem myszy:
//   - zamiast bool visited[][] trzymamy int board[][] z numerem kroku
//   - cofanie: board[row][col] = 0 (zamiast visited = false)
// ─────────────────────────────────────────────────────────────────────────────
bool solve(int row, int col, int step)
{
    // WARUNEK STOPU: odwiedziliśmy wszystkie N*N pól – sukces!
    if (step > N * N) return true;

    // Próbujemy wszystkie 8 możliwych skoków skoczka
    for (int d = 0; d < 8; d++)
    {
        int newRow = row + DR[d];
        int newCol = col + DC[d];

        if (!isValid(newRow, newCol)) continue;  // skok nielegalny – pomijamy

        // ZRÓB KROK: wpisz numer kroku na nowe pole
        board[newRow][newCol] = step;

        // IDŹ GŁĘBIEJ: skocz na nowe pole i próbuj dalej
        if (solve(newRow, newCol, step + 1)) return true;

        // COFNIJ KROK: to pole nie doprowadziło do rozwiązania
        // Resetujemy do 0 – pole znów jest "nieodwiedzone"
        board[newRow][newCol] = 0;
    }

    // Żaden z 8 skoków nie doprowadził do rozwiązania – cofamy się
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main()
{
    std::cout << "===== Knight's Tour " << N << "x" << N << " =====\n\n";

    // Skoczek startuje z pozycji (0,0) jako krok numer 1
    board[0][0] = 1;

    if (solve(0, 0, 2))  // szukamy od kroku 2 bo krok 1 już ustawiony
    {
        std::cout << "Rozwiazanie znalezione!\n\n";
        printBoard();

        // Weryfikacja – sprawdzamy czy każda liczba od 1 do N*N wystąpiła
        std::cout << "\nWeryfikacja trasy:\n";
        for (int step = 1; step <= N * N; step++)
        {
            for (int r = 0; r < N; r++)
                for (int c = 0; c < N; c++)
                    if (board[r][c] == step)
                        printf("  krok %2d: (%d,%d)\n", step, r, c);
        }
    }
    else
    {
        std::cout << "Brak rozwiazania dla planszy " << N << "x" << N << "\n";
    }

    return 0;
}
