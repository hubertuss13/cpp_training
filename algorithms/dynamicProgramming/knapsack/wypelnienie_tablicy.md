Dane:

Przedmiot A: weight=2, value=3
Przedmiot B: weight=3, value=4
Przedmiot C: weight=4, value=5
Pojemność W=5

Przedmioty:
┌───────────┬──────┬────────┐
│ Przedmiot │ Waga │ Wartość│
├───────────┼──────┼────────┤
│ A         │  2   │   3    │
│ B         │  3   │   4    │
│ C         │  4   │   5    │
└───────────┴──────┴────────┘
Limit wagi plecaka: W = 5
Cel: wybierz zestaw przedmiotów o maksymalnej wartości nie przekraczając limitu wagi plecaka W

Zaczynam od pustej tablicy, wypełnionej zerami:

        w=0  w=1  w=2  w=3  w=4  w=5
i=0      0    0    0    0    0    0
i=1      0    ?    ?    ?    ?    ?
i=2      0    ?    ?    ?    ?    ?
i=3      0    ?    ?    ?    ?    ?

Kolumna w=0 i wiersz i=0 to zawsze zera — pojemność 0 albo zero przedmiotów daje wartość 0. To punkt startowy.

Wiersz i=1 — rozpatruję tylko przedmiot A (weight=2, value=3)

dp[1][1]: Plecak ma pojemność 1. Przedmiot A waży 2. Nie mieści się.

Jedyny wybór: NIE biorę A → dp[0][1] = 0
dp[1][1] = 0

dp[1][2]: Plecak ma pojemność 2. Przedmiot A waży 2. Mieści się!

Wybór 1 (nie biorę): dp[0][2] = 0
Wybór 2 (biorę): value[A] + dp[0][2 - weight[A]] = 3 + dp[0][0] = 3 + 0 = 3
max(0, 3) = dp[1][2] = 3

dp[1][3]: Plecak ma pojemność 3. Przedmiot A waży 2. Mieści się!

Wybór 1 (nie biorę): dp[0][3] = 0
Wybór 2 (biorę): 3 + dp[0][3-2] = 3 + dp[0][1] = 3 + 0 = 3
max(0, 3) = dp[1][3] = 3

Uwaga: mógłbym wziąć A dwa razy i zapełnić plecak o pojemności 3, ale to jest knapsack 0/1 — każdy przedmiot można wziąć co najwyżej raz.

dp[1][4]: Plecak ma pojemność 4. Mieści się A.

Wybór 1 (nie biorę): dp[0][4] = 0
Wybór 2 (biorę): 3 + dp[0][4-2] = 3 + dp[0][2] = 3 + 0 = 3
max(0, 3) = dp[1][4] = 3

dp[1][5]: Plecak ma pojemność 5. Mieści się A.

Wybór 1 (nie biorę): dp[0][5] = 0
Wybór 2 (biorę): 3 + dp[0][5-2] = 3 + dp[0][3] = 3 + 0 = 3
max(0, 3) = dp[1][5] = 3

Stan tablicy:

        w=0  w=1  w=2  w=3  w=4  w=5
i=0      0    0    0    0    0    0
i=1      0    0    3    3    3    3
i=2      0    ?    ?    ?    ?    ?
i=3      0    ?    ?    ?    ?    ?
Wiersz i=2 — rozpatruję przedmioty A i B (teraz dochodzi B: weight=3, value=4)

Kluczowe: dp[i-1][w] to teraz wiersz i=1, który już obliczony. Każde “nie biorę B” sięga do niego.

dp[2][1]: Pojemność 1. B waży 3 — nie mieści się.

Jedyny wybór: dp[1][1] = 0
dp[2][1] = 0

dp[2][2]: Pojemność 2. B waży 3 — nie mieści się.

Jedyny wybór: dp[1][2] = 3
dp[2][2] = 3

dp[2][3]: Pojemność 3. B waży 3 — mieści się!

Wybór 1 (nie biorę B): dp[1][3] = 3
Wybór 2 (biorę B): value[B] + dp[1][3 - weight[B]] = 4 + dp[1][3-3] = 4 + dp[1][0] = 4 + 0 = 4
max(3, 4) = dp[2][3] = 4

dp[2][4]: Pojemność 4. B waży 3 — mieści się!

Wybór 1 (nie biorę B): dp[1][4] = 3
Wybór 2 (biorę B): 4 + dp[1][4-3] = 4 + dp[1][1] = 4 + 0 = 4
max(3, 4) = dp[2][4] = 4

Dlaczego nie 7? Bo przy pojemności 4 biorę B (waga 3) i zostaje mi 1. Ale A waży 2 — nie mieści się w tym co zostało.

dp[2][5]: Pojemność 5. B waży 3 — mieści się!

Wybór 1 (nie biorę B): dp[1][5] = 3
Wybór 2 (biorę B): 4 + dp[1][5-3] = 4 + dp[1][2] = 4 + 3 = 7

Zauważ co się stało w Wyborze 2: wziąłem B (wartość 4), zostało mi 5-3=2 miejsca, i pytam dp[1][2] — czyli “jaka jest najlepsza wartość z samego A przy pojemności 2?” A odpowiedź to 3 (A waży dokładnie 2). Więc A też wchodzi!

max(3, 7) = dp[2][5] = 7

Stan tablicy:

        w=0  w=1  w=2  w=3  w=4  w=5
i=0      0    0    0    0    0    0
i=1      0    0    3    3    3    3
i=2      0    0    3    4    4    7
i=3      0    ?    ?    ?    ?    ?
Wiersz i=3 — dochodzi C (weight=4, value=5)

dp[3][1], dp[3][2], dp[3][3]: C waży 4 — nie mieści się przy pojemnościach 1, 2, 3.

Przepisujemy z wiersza wyżej: 0, 3, 4

dp[3][4]: Pojemność 4. C waży 4 — mieści się!

Wybór 1 (nie biorę C): dp[2][4] = 4
Wybór 2 (biorę C): 5 + dp[2][4-4] = 5 + dp[2][0] = 5 + 0 = 5
max(4, 5) = dp[3][4] = 5

dp[3][5]: Pojemność 5. C waży 4 — mieści się!

Wybór 1 (nie biorę C): dp[2][5] = 7
Wybór 2 (biorę C): 5 + dp[2][5-4] = 5 + dp[2][1] = 5 + 0 = 5
max(7, 5) = dp[3][5] = 7

Tutaj C przegrywa — dp[2][5]=7 (kombinacja A+B) jest lepsza niż wzięcie C i resztka o pojemności 1 (która nic nie pomieści).

Gotowa tablica:

        w=0  w=1  w=2  w=3  w=4  w=5
i=0      0    0    0    0    0    0
i=1      0    0    3    3    3    3
i=2      0    0    3    4    4    7
i=3      0    0    3    4    5    7

Odpowiedź: dp[3][5] = 7
